
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
public:
   char commentId[20];
   char postId[20];
   char postedBy[20];
   char txt[300];
};

class Post {
public:
    int   postType;//1 or 2
    char  id[20];
    int   day, month, year;
    char  text[300];
    int   activityType;        
    char  activityValue[100];  
    char  postedby[20];
    char  likedby[10][20];   
    int   likedCount;
};
class Memory {};
class Page {};
int main() {
    //SocialNetworkApp::Run() 
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
        posts[i] = new Post();
        fin >> posts[i]->postType >> posts[i]->id;
        fin >> posts[i]->day >> posts[i]->month>> posts[i]->year;
        fin.ignore();
        fin.getline(posts[i]->text,sizeof(posts[i]->text));
        if (posts[i]->postType == 2)
        {
            fin >> posts[i]->activityType;
            fin.ignore();
            fin.getline(posts[i]->activityValue, sizeof(posts[i]->activityValue));
        }
        else
        {
            posts[i]->activityType = 0;
            posts[i]->activityValue[0] = '\0';

        }
        fin >> posts[i]->postedby;
        
        posts[i]->likedCount = 0;
        char temp[20];
        while (fin >> temp) {
            if (strcmp(temp, "-1") == 0) break;
            strcpy(posts[i]->likedby[posts[i]->likedCount], temp);
            posts[i]->likedCount++;
        }
    }
    fin.close();
    for (int i = 0; i < postCount; i++) 
    {
        cout << "Post " << posts[i]->id << " ("
            << posts[i]->day << "/" << posts[i]->month << "/" << posts[i]->year
            << "): " << posts[i]->text << endl;
        cout << "Tag: " << posts[i]->activityValue << endl;
        cout << "Posted by: " << posts[i]->postedby << endl;
        cout << "Liked by: ";
        for (int j = 0; j < posts[i]->likedCount; j++)
        {
            cout << posts[i]->likedby[j] << " ";
        }
        cout << "\n\n";
    }

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
    for (int i = 0; i < commentCount; i++)
    {
        comments[i] = new Comment();
        
        in>>comments[i]->commentId;
        in >> comments[i]->postId;
        in >> comments[i]->postedBy;
        in.ignore();
        in.getline(comments[i]->txt, sizeof(comments[i]->txt));
    }
   
    in.close();
    for (int i = 0; i < commentCount; i++)
    {
        cout << comments[i]->commentId << " | "
            << comments[i]->postId << " | "
            << comments[i]->postedBy << " | "
            << comments[i]->txt << endl;
    }
    return 0;
}
