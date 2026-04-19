#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<sstream>
#include <string>
using namespace std;

class Date {
    int day, month, year;
};
class Activity
{
	int type;
	char* value;
public:
    int getType() { return type; }
    char* getValue() { return value; }
	Activity(int t=0,char* v=nullptr)
	{
		type=t;
        if (v != nullptr) {
            value = new char[strlen(v) + 1];
            strcpy(value, v);
        }
        else {
            value = nullptr;
        }
	}
    void diplayActivity()
    {
        switch (type) {
        case 1: cout << "is feeling " << value;        break;
        case 2: cout << "is thinking about " << value; break;
        case 3: cout << "is making " << value;         break;
        case 4: cout << "is celebrating " << value;    break;
        }
     }
	 ~Activity()
	 {
		 delete[] value;
}

};
class Comment
{
private:
   
   char *commentId;
   char *postId;
   char *postedBy;
   char *txt;
public:
   Comment(char*a=nullptr, char* b = nullptr, char* c = nullptr, char* d = nullptr)
   {
       commentId = new char[strlen(a)+1];
       strcpy(commentId, a);
       postId = new char[strlen(b) + 1];
       strcpy(postId, b);
       postedBy = new char[strlen(c) + 1];
       strcpy(postedBy, c);
       txt = new char[strlen(d) + 1];
       strcpy(txt, d);
   }
   char* getcommentId()
   {
       return commentId;
   }
   char* getpostId()
   {
       return postId;
   }
   char* getpostedBy()
   {
       return postedBy;
   }
   char* gettxt()
   {
       return txt;
   }
   void displayComment()
   {
       
       cout <<postedBy << " wrote : \"" << txt <<"\""<< endl;
   }
   ~Comment()
   {
       delete[] commentId;
       delete[] postId;
       delete[] postedBy;
       delete[] txt;
   }
};

class Post {
public:
    
    char* id;
    char* text;
    int day, month, year;
    int postType;//1,2
    Activity* activity;
    char* postedBy;
    char* likedBy[10];       // max 10
    int likedCount;
    Comment* comments[10];   // max 10
    int commentCount;

    
    Post(char* pid, char* ptext, int pday, int pmonth, int pyear,
        int ptype, char* ppostedBy, Activity* pact = nullptr)
    {
        id = new char[strlen(pid) + 1];
        strcpy(id, pid);

        text = new char[strlen(ptext) + 1];
        strcpy(text, ptext);

        day = pday;
        month = pmonth;
        year = pyear;
        postType = ptype;

        postedBy = new char[strlen(ppostedBy) + 1];
        strcpy(postedBy, ppostedBy);

        activity = pact;   

        likedCount = 0;
        commentCount = 0;

        for (int i = 0; i < 10; i++) {
            likedBy[i] = nullptr;
            comments[i] = nullptr;
        }
    }
    char* getId()
    {
        return id;
    }
    char* gettext()
    {
        return text;
    }
    int getday()
    {
        return day;
    }
    int getmonth()
    {
        return month;
    }
    int getyear()
    {
        return year;
    }
    int getpostType()
    {
        return postType;
    }
    char* getpostedBy()
    {
        return postedBy;
    }
    char* getlikedBy(int i)
    {
        return likedBy[i];
    }
    Activity *getactivity()
    {
        return activity;
    }
    int getlikedCount() { return likedCount; }
    int getcommentCount() { return commentCount; }
   
    Comment* getcomment(int i) { return comments[i]; }
     
    void addLike(char* entityId)
    {
        if (likedCount < 10) {
            likedBy[likedCount] = new char[strlen(entityId) + 1];
            strcpy(likedBy[likedCount], entityId);
            likedCount++;
        }
    }
    void addComment(Comment* c)
    {
        if (commentCount < 10)
            comments[commentCount++] = c;
    }

    ~Post()
    {
        delete[] id;
        delete[] text;
        delete[] postedBy;
        delete activity;

        for (int i = 0; i < likedCount; i++)
            delete[] likedBy[i];

        for (int i = 0; i < commentCount; i++)
            delete comments[i];
    }
};




class Memory {};
class Page {};
int main() {
    //SocialNetworkApp::Run() 
	 //Reading data from Posts.txt
    ifstream fin("Posts.txt");
    if (!fin) {
        cout << "Error! File not found!" << endl;
        return 1;
    }
    else 
        cout << "File Found!" << endl;
    
    int postCount;
    fin >> postCount;
    cout << postCount<<endl;
    Post **posts;
    posts = new Post * [postCount];
    for (int i = 0; i < postCount; i++)
 {
     char tempId[20], temptext[300], tempPostedBy[20];
     int tempDay, tempMonth, tempYear, tempPostType;
     
     fin >> tempPostType >> tempId;
     fin >> tempDay >> tempMonth >> tempYear;
     fin.ignore();
     fin.getline(temptext, 300);
    
     
     Activity* act = nullptr;
     if (tempPostType == 2) {
         char tempActValue[100];
         int tempActType;

         fin >> tempActType;
         fin.ignore();
         fin.getline(tempActValue, 100);

         act = new Activity(tempActType, tempActValue);
     }
     
   
     fin >> tempPostedBy;
     posts[i] = new Post(tempId, temptext, tempDay, tempMonth,
         tempYear, tempPostType, tempPostedBy, act);
     
     char temp[20];
     while (fin >> temp) {
         if (strcmp(temp, "-1") == 0) break;
         posts[i]->addLike(temp);
     }
     
     
    
  
 }
    fin.close();
    
    for (int i = 0; i < postCount; i++)
 {
     cout << posts[i]->getId() << " | "
         << posts[i]->getday() << "/" << posts[i]->getmonth() << "/" << posts[i]->getyear() << " | "
         << posts[i]->gettext() << " | ";

     if (posts[i]->getactivity() != nullptr)
         posts[i]->getactivity()->diplayActivity();

     cout << " | By: " << posts[i]->getpostedBy() << " | Likes: ";

     for (int j = 0; j < posts[i]->getlikedCount(); j++)
         cout << posts[i]->getlikedBy(j) << " ";

     cout << endl;
 }

 //Reading data from Comments.txt

    ifstream in("Comments.txt");
    if (!in) {
        cout << "Error! File not found!" << endl;
        return 1;
    }
    else
        cout << "File Found!" << endl;
    int commentCount;
    in >> commentCount;
    cout << commentCount<<endl;
    Comment** comments;
    comments = new Comment*[commentCount];
    for (int i = 0; i < commentCount; i++) {
     char tempCommentId[20];
     char tempPostId[20];
     char tempPostedBy[20];
     char tempTxt[300];
    
     in >> tempCommentId;
     in >> tempPostId;
     in >> tempPostedBy;
     in.ignore();
     in.getline(tempTxt, sizeof(tempTxt));

    
     comments[i] = new Comment(tempCommentId, tempPostId, tempPostedBy, tempTxt);
 }

   
    in.close();
    for (int i = 0; i < commentCount; i++)
    {
        cout << comments[i]->getcommentId() << " | "
     << comments[i]->getpostId() << " | "
     << comments[i]->getpostedBy() << " | "
     << comments[i]->gettxt() << endl;
    }
	//linking the comment and the post class
for (int i = 0; i < commentCount; i++)
{
    
    for (int j = 0; j < postCount; j++)
    {
        if (strcmp(comments[i]->getpostId(), posts[j]->getId()) == 0)
        {
            posts[j]->addComment(comments[i]);
            break;
        }
    }
}

//Verifyingg
cout << "post1 comments:" << endl;
for (int i = 0; i < posts[0]->getcommentCount(); i++)
    posts[0]->getcomment(i)->displayComment();
    return 0;
}
