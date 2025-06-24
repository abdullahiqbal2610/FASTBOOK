#include <iostream>
#include <fstream>
using namespace std;


class helper {

public:
	static int StringLength(char* str)
	{
		int stringLen = 0;
		for (char* temp = str; *temp != '\0'; temp++)
			stringLen++;

		return stringLen;
	}
	static char* GetStringFromBuffer(char* buffer)
	{
		int strLen = StringLength(buffer);
		char* str = 0;
		if (strLen > 0)
		{
			str = new char[strLen + 1];
			for (int i = 0; i < strLen; i++)
			{
				str[i] = buffer[i];
			}
			str[strLen] = '\0';
		}
		return str;
	}
};


class date {
private:
	int day;
	int month;
	int year;
	
public:
	date( int d = 1,  int m = 1, int y = 2010)
	{
		day = d;
		month = m;
		year = y;
	}
	

	void ReadDateFromFile(ifstream& fin)
	{
		int temp;
		fin >> temp;
		day = temp;

		fin >> temp;
		month = temp;

		fin >> temp;
		year = temp;
		
	}

	void SetDate(int i, int j, int k)
	{
		day = i;
		month = j;
		year = k;
	}

	
	void PrintDate()
	{
		cout << day << "/" << month << "/" << year << endl;
	}


	void CompareDate(const  date& currentdate)
	{
		if (year == currentdate.year && month == currentdate.month && day == currentdate.day)
		{
			cout << "(1h)" << endl;
		}
		else
		{
			this->PrintDate();
		}
	}

	int GetYearDifference(const date& current)
	{
		if (year > current.year)
		{
			return year - current.year;
		}
		else
		{
			return current.year- year;
		}
	}
	bool CheckDateforMemory(const date& currentDate)
	{
		if ((day == currentDate.day) && (month == currentDate.month) && (year != currentDate.year))
		{
			return true;
		}
		else
		{
			return false;
		}
	}



	bool CheckDate(const date& rhs)
	{
		if (year == rhs.year && month == rhs.month && (day>=rhs.day-2))
		{
			return true;
		}

		return false;
	}

	static date CurrentDate;



};

date date::CurrentDate(17,4,2024);

class posts;

class object;

class Comments;



class object {
private:
	char* Id;

protected:
	posts** Timeline;

public:
	object()
	{
		Id = NULL;
		
		Timeline = new posts * [10];
		for (int i = 0; i < 10; i++)
		{
			Timeline[i] = NULL;

		}
	}

	char* getId()
	{
		return Id;
	}

	void setId(char* buffer)
	{
		Id = helper::GetStringFromBuffer(buffer);
	}

	void DisplaySharedBy()
	{
		cout << Id << endl;
	}

	void AddToTimeline(posts* ptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] == NULL)
			{
				Timeline[i] = ptr;
				return;
			}
		}
	}

	
	virtual void DisplayLikedBy() = 0;
	

	virtual void PrintName() = 0;
	




	virtual ~object()
	{
		delete[] Id;

		delete[] Timeline;
	}



};







class Comments {
private:
	char* CommentId;
	posts* CommentedOn;
	object* CommentedBy;
	char* CommentText;

public:
	Comments()
	{
		CommentId = NULL;
		CommentedOn = NULL;
		CommentedBy = NULL;
		CommentText = NULL;
	}
	Comments(char* id, posts* CO, object* CB, char* text)
	{
		CommentId = helper::GetStringFromBuffer(id);
		CommentedOn = CO;
		CommentedBy = CB;
		CommentText = helper::GetStringFromBuffer(text);
	}

	Comments& operator=(const Comments& rhs)
	{
		CommentId = helper::GetStringFromBuffer(rhs.CommentId);
		CommentedOn = rhs.CommentedOn;
		CommentedBy = rhs.CommentedBy;
		CommentText = helper::GetStringFromBuffer(rhs.CommentText);

		return *this;
	}

	void displayComment()
	{
		CommentedBy->PrintName();
		cout << ":\t" << "'" << CommentText << "'" << endl;
	}


	char* getCommentId()
	{
		return CommentId;
	}
	
	~Comments()
	{
		delete[] CommentId;
		delete[] CommentText;
	}

};



class Postcontent
{


public:
	virtual void DisplayActivity() = 0;
	
};


class activity : public Postcontent
{
private:
	int activityType;
	char* text;

public:
	activity()
	{
		activityType = 0;
		text = NULL;
	}

	void ReadDataFromFile(ifstream& fin)
	{

		char buffer[100];

		fin >> activityType;
		fin.ignore();

		fin.getline(buffer, 99);
		text = helper::GetStringFromBuffer(buffer);
		


	}


	void DisplayActivity()
	{
		if (activityType == 1)
		{
			cout << "is feeling";
		}
		else if (activityType == 2)
		{
			cout << "is thinking about";
		}
		else if (activityType == 3)
		{
			cout << "is making";
		}
		else if (activityType == 4)
		{
			cout << "is celebrating";
		}
		cout << " " << text ;
	}

	~activity()
	{
		text = NULL;
	}
};



class posts {
private:
	char* PostId;
	char* PostText;
	object* Sharedby;
	object** Likedby;
	date SharedDate;
	Comments* Allcomments;
	Postcontent* content;
	
public:


	posts()
	{
		PostId = NULL;
		PostText = NULL;

		Sharedby = NULL;
		Likedby = new object * [10];
		for (int i = 0; i < 10; i++)
		{
			Likedby[i] = NULL;
		}

		content = NULL;

		Allcomments = new Comments[10];
	
	}

	void ReadDataFromFile(ifstream& fin)
	{
		char buffer[100];
		fin >> buffer;
		PostId = helper::GetStringFromBuffer(buffer);

		SharedDate.ReadDateFromFile(fin);
		fin.ignore();
		fin.getline(buffer, 99);
		PostText = helper::GetStringFromBuffer(buffer);

	}


	void AddContent(Postcontent* ptr)
	{
	
		content = ptr;
	}

	void AddComment(Comments& ptr)
	{

		for (int i = 0; i < 10; i++)
		{
			if (Allcomments[i].getCommentId() == NULL)
			{
				Allcomments[i] = ptr;
				return;
			}
		}

	}


	void SetSharedDate(const date current)
	{
		SharedDate = current;
	}
	void SetSharedBy(object* rhs)
	{
		if (rhs != NULL)
		{
			Sharedby = rhs;
		}
	}
	void SetText(char* Text)
	{
		PostText = helper::GetStringFromBuffer(Text);
	}
	char* GetText()
	{
		return PostText;
	}

	virtual void Displaypost(const date& currentDate)
	{
		
		if (content != NULL)
		{
			content->DisplayActivity();
		}


		cout << endl << endl;
		SharedDate.CompareDate(date::CurrentDate);
		cout << "\"" << PostText << "\"" << endl << endl;


	}
	void SetSharedby(object* ptr)
	{
		if (ptr != NULL) {
			Sharedby = ptr;
		}
	}

	void SetLikedby(object* ptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (Likedby[i] == NULL)
			{
				Likedby[i] = ptr;
				return;
			}
		}
	}


	bool SearchID(char* id)
	{
		if (helper::StringLength(PostId) != helper::StringLength(id))
		{
			return false;
		}
		else
		{
			for (int i = 0; i < helper::StringLength(id); i++)
			{
				if (PostId[i] != id[i])
				{
					return false;
				}
			}
			return true;
		}
	}

	void DisplayLikedBy()
	{
		for (int i = 0; i < 10; i++)
		{
			if (Likedby[i] != NULL)
			{
				Likedby[i]->DisplayLikedBy();
			}
			else
			{
				return;
			}
		}
	}


	void ShowComments()
	{
		for (int i = 0; i < 10; i++)
		{
			if (Allcomments[i].getCommentId() == NULL)
			{
				break;
			}
			Allcomments[i].displayComment();

		}
		cout << endl;
	}

	char* GetPostId()
	{
		return PostId;
	}
	object* GetSharedBy()
	{
		return Sharedby;
	}
	date GetSharedDate()
	{
		return SharedDate;
	}
	void SeeYourMemories()
	{
		if (GetSharedDate().CheckDateforMemory(date::CurrentDate) == true)
		{
			cout << GetSharedDate().GetYearDifference(date::CurrentDate) << " years ago \n";
			
			GetSharedBy()->PrintName();
			cout << "\t";
			Displaypost(date::CurrentDate);
			ShowComments();
			cout << endl;
		}
	}


	virtual ~posts()
	{
		if (PostId)
		{
			delete[] PostId;
		}
		if (PostText)
		{
			delete[]PostText;
		}

		if (content) {
			delete content;
		}


		delete[] Likedby;

		delete[] Allcomments;

	}
};



class Memory :public posts
{
private:
	posts* OriginalPost;

public:
	Memory() :posts()
	{
		OriginalPost = NULL;
	}
	void SetMemory(posts* ptr, char* text)
	{
		OriginalPost = ptr;
		SetText(text);
		SetSharedDate(date::CurrentDate);
		SetSharedBy(ptr->GetSharedBy());

	}
	void Displaypost(const date& currentdate)
	{
		cout << "shared a memory ";
		GetSharedDate().CompareDate(currentdate);
		cout << "\n";
		cout << "\"" << GetText() << "\"" << endl;
		cout << OriginalPost->GetSharedDate().GetYearDifference(currentdate) << " years ago \n";
		cout << "\n";
		GetSharedBy()->PrintName();
		cout << " ";
		OriginalPost->Displaypost(currentdate);
		cout << "\n";
		this->ShowComments();
		cout << endl;

	}
	
};


class Pages:public object {

	
	char* Title;

public:
   Pages():object()
	{
		Title = NULL;
	}

	void ReadDataFromFile(ifstream& fin)
	{
		char buffer[80];

		fin >> buffer;
		
		setId(buffer);
		fin.ignore();

		fin.getline(buffer, 79);
		Title = helper::GetStringFromBuffer(buffer);

	}

	bool SearchID(char* Id)
	{
		if (helper::StringLength(getId()) != helper::StringLength(Id))
		{
			return false;
		}
		else
		{
			for (int i = 0; i < helper::StringLength(Id); i++)
			{
				if (getId()[i] != Id[i])
				{
					return false;
				}
			}
			return true;
		}

	}


	char* getTitle()
	{
		return Title;
	}
	void DisplayLikedBy()
	{
		cout << getId() << " - " << Title << endl;
	}

	void PrintRecent()
	{
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] == NULL)
			{
				break;
			}

			if (Timeline[i]->GetSharedDate().CheckDate(date::CurrentDate) == true)
			{
				this->PrintName();
				cout << "\t";
				Timeline[i]->Displaypost(date::CurrentDate);
				Timeline[i]->ShowComments();
				cout << endl;
			}


		}

	}

	void ViewTimeLine()
	{
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] != NULL)
			{
				cout << "\n\n" << Title << "\n\n"; 
				Timeline[i]->Displaypost(date::CurrentDate);
				cout << endl << endl << "Comments:\n";
				Timeline[i]->ShowComments();
			}
			else {
				break;
			}
		}
	}

	void PrintName()
	{
		cout << Title;
	}
	

	~Pages()
	{
		delete[] Title;
	}
};




class User: public object 
{
private:
	char* fname;
	char* lname;
	User** FriendList;
	Pages** LikedPages;

public:
	User()
	{
		fname = NULL;
		lname = NULL;
		FriendList = new User* [10];
		LikedPages = new Pages* [10];

		for (int i = 0; i < 10; i++)
		{
			FriendList[i] = NULL;
			LikedPages[i] = NULL;
		}

		
	}

	void ReadDataFromFile(ifstream& fin) {

		char buffer[30];
		fin >> buffer;
		setId(buffer);

		fin >> buffer;
		fname = helper::GetStringFromBuffer(buffer);

		fin >> buffer;
		lname = helper::GetStringFromBuffer(buffer);
	}


	void AddFriend(User* const& ptr)
	{
		if (ptr != NULL)
		{
			for (int i = 0; i < 10; i++)
			{
				if (FriendList[i] == NULL)
				{
					FriendList[i] = ptr;
					return;
				}
				
			}
		}
	}
	void PrintRecent()
	{
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] == NULL)
			{
				break;
			}

			if (Timeline[i]->GetSharedDate().CheckDate(date::CurrentDate) == true)
			{
				this->PrintName();
				cout << "\t";
				Timeline[i]->Displaypost(date::CurrentDate);
				Timeline[i]->ShowComments();
				cout << endl;
			}


		}

	}

	void LikePage(Pages* const& ptr)
	{
		if (ptr != NULL)
		{
			for (int i = 0; i < 10; i++)
			{
				if (LikedPages[i] == NULL)
				{
					LikedPages[i] = ptr;
					return;
				}
			
			}
		}
	}

	void PrintName()
	{
		cout << fname << " " << lname;
	}
	void ViewFriendList() 
	{
		cout << "\n\nCommand view friend list\n\n";
		for (int i = 0; i < 10; i++)
		{
			if (FriendList[i] == NULL)
			{
				break;
			}
			
			
				cout << FriendList[i]->getId() << "\t" << FriendList[i]->fname << "\t" << FriendList[i]->lname << endl;
			
		}

	}
	
	void ViewLikedPages()
	{
		cout << "\n\nCommand view liked page list\n\n";
		for (int i = 0; i < 10; i++)
		{
			if (LikedPages[i] == NULL)
			{
				break;
			}
			
				cout << LikedPages[i]->getId()<<"\t"<<  LikedPages[i]->getTitle() << endl;
			
		}

	}

	bool SearchID(char* Id)
	{
		if (helper::StringLength(getId()) != helper::StringLength(Id))
		{
			return false;
		}
		else
		{
			for (int i = 0; i < helper::StringLength(getId()); i++)
			{
				if (Id[i] != getId()[i])
				{
					return false;
				}
			}
			return true;
		}

	}


	void AddCommentByUser(posts* ptr, char* text)
	{
		char temp[] = "cXXX";
		Comments usercomment(temp, ptr, this, text);
		
		ptr->AddComment(usercomment);
		
	}


	void LikeAPost(posts* ptr)
	{
		ptr->SetLikedby(this);
	}
	void DisplayLikedBy()
	{
		cout << getId() << " - " << fname << " " << lname << endl;
	}

	char* getFname()
	{
		return fname;
	}
	char* getLname()
	{
		return lname;
	}


	void ViewTimeline()
	{
		
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] != NULL)
			{
				cout << "\n\n" << fname << " " << lname << "\n\n";
				Timeline[i]->Displaypost(date::CurrentDate);
				Timeline[i]->ShowComments();
			}
			else
			{
				break;
			}
		}

	}

	void ViewHome()
	{
	
		this->PrintRecent();
		cout << endl;
		for (int i = 0; i < 10; i++)
		{
			if (FriendList[i] == NULL)
			{
				break;
			}

			FriendList[i]->PrintRecent();
			cout << endl;
		}

		for (int i = 0; i < 10; i++)
		{
			if (LikedPages[i] == NULL)
			{
				break;
			}

			LikedPages[i]->PrintRecent();
			cout << endl;
		}

		
	}
	void SeeYourMemories()
	{
		cout << "We hope you enjoy looking back and sharing your memories on Fast-book, from the most recent to those long ago.\n\n";
		cout << "On this Day\n";
		for (int i = 0; i < 10; i++)
		{
			if (Timeline[i] == NULL)
			{
				break;
			}

			Timeline[i]->SeeYourMemories();
		}
	}
	~User()
	{
		delete[] fname;
		delete[] lname;
		
		delete[] FriendList;
		
		delete[] LikedPages;

	}

	
};



class Controller
{
private:
    User** AllUsers;
    Pages** AllPages;
	posts** AllPosts;
	activity** AllActivities;
	static int totalUsers;
	static int totalPages;
	static int totalPosts;
	static int totalComments;
	static int totalActivity;


public:
	Controller()
	{
		AllUsers = NULL;
		AllPages = NULL;
		AllPosts = NULL;
		AllActivities = NULL;

	}
  
	void LoadAllUsers() {

		ifstream fin("users.txt");

		fin >> totalUsers;
		AllUsers = new User * [totalUsers];
		for (int i = 0; i < totalUsers; i++) 
		{
			AllUsers[i] = new User();
			AllUsers[i]->ReadDataFromFile(fin);

		}
	}

	void LoadAllPages()
	{

		ifstream fin("pages.txt");

		fin >> totalPages;
		AllPages = new Pages * [totalPages];
		for (int i = 0; i < totalPages; i++) 
		{
			AllPages[i] = new Pages();
			AllPages[i]->ReadDataFromFile(fin);
		}

	}

	User* SearchUserByID(char* id)
	{
		for (int i = 0; i < totalUsers; i++)
		{

			if (AllUsers[i]->SearchID(id) == true)
			{
				return AllUsers[i];
			}
		}
		
		return NULL;

	}
	Pages* SearchPageByID(char* ID)
	{
		for (int i = 0; i < totalPages; i++)
		{

			if (AllPages[i]->SearchID(ID) == true)
			{
				return AllPages[i];
			}
		}
		
		return NULL;
	}

	posts* SearchPostByID(char* ID)
	{
		for (int i = 0; i < totalPages; i++)
		{

			if (AllPosts[i]->SearchID(ID) == true)
			{
				return AllPosts[i];
			}
		}

		return NULL;
	}

	object* SearchObjectByPost(char* id)
	{
		if (id[0] == 'u')
		{
			return SearchUserByID(id);
		}
		else if (id[0] == 'p')
		{
			return SearchPageByID(id);
		}

		return NULL;
	}
	void LoadAllPosts()
	{
		ifstream fin("posts.txt");
		fin >> totalPosts;
		
		AllPosts = new posts * [totalPosts];
		char buffer[20];


		for (int i = 0; i < totalPosts; i++) 
		{
			AllPosts[i] = new posts();
			AllPosts[i]->ReadDataFromFile(fin);
			fin >> buffer;
			AllPosts[i]->SetSharedby(SearchObjectByPost(buffer));
			SearchObjectByPost(buffer)->AddToTimeline(AllPosts[i]);
			
			char ID[25];
			do {
				fin >> ID;
				AllPosts[i]->SetLikedby(SearchObjectByPost(ID));
			} while (ID[0] != '-');
			
		}
	}


	void LoadAllActivities()
	{
		ifstream fin("activity.txt");
		fin >> totalActivity;

		AllActivities = new activity * [totalActivity];

		char buffer[10];

		for (int i = 0; i < totalActivity; i++)
		{
			AllActivities[i] = new activity();
			fin >> buffer;

			SearchPostByID(buffer)->AddContent(AllActivities[i]);

			AllActivities[i]->ReadDataFromFile(fin);
		}

	}

	void ShareMemory(Memory* ptr, char* postid, char* userid, char* text)
	{
		ptr->SetMemory(SearchPostByID(postid), text);
		SearchObjectByPost(userid)->AddToTimeline(ptr);
	}

	void LoadAllComments()
	{
		ifstream fin("comments.txt");
		fin >> totalComments;

		char ID[10] = { '\0' };
		char Text[100] = { '\0' };
		char buffer[10] = { '\0' };
		posts* CommentedOn = NULL;
		object* CommentedBy = NULL;


		for (int i = 0; i < totalComments; i++)
		{
			fin >> ID;
			fin >> buffer;
			CommentedOn=SearchPostByID(buffer);
			fin >> buffer;
			CommentedBy = SearchObjectByPost(buffer);
			fin.ignore();
			fin.getline(Text, 99);
			Comments temp(ID, CommentedOn, CommentedBy, Text);
			CommentedOn->AddComment(temp);

		}

	}

	void ViewLikedBy(posts* ptr)
	{
		cout <<  ptr->GetPostId()<< " is Liked By : \n\n";
		ptr->DisplayLikedBy();
	}

	void ViewAPost(posts* temp)
	{
		object* ptr=temp->GetSharedBy();
		ptr->PrintName();
		
		cout << endl;
		temp->Displaypost(date::CurrentDate);
		cout << endl << endl << "Comments:\n";
		temp->ShowComments();
	
	}
	void ViewPage(Pages* ptr)
	{
		ptr->ViewTimeLine();
	}

	void LoadData()
	{
		
		LoadAllUsers(); 
		LoadAllPages();
	    LinkUsersAndPages();
		
		LoadAllPosts();

		LoadAllActivities();
		LoadAllComments();
		cout << endl << endl;
		
		cout << "\n\t\t\t\t\tCurrent date of system is set to:\t";
		date::CurrentDate.PrintDate();

		cout << endl << endl << endl;
		char currentuser[5];		//current user set
		cout << "\t\t\t\t\tEnter user ID: ";
		cin >> currentuser;
		cout << "Set current user as: " << currentuser << endl;
		char functionality='\0';
	
		SetCurrentUser(currentuser);

		while (functionality != 'x')
		{
			cout << "\tChoose your option:\n\n";
			cout << "1)\t For view friendlist press f\n";
			cout << "2)\t For view likedpages press p\n";
			cout << "3)\t For view home press h\n";
			cout << "4)\t For view timeline press t \n";
			cout << "5)\t For liking a post press l \n";
			cout << "6)\t For liking a page press r \n";

			cout << "7)\t For adding a comment on a post press c \n";
			cout << "8)\t For viewing a post press a \n";
			cout << "9)\t For viewing a page press b \n";
			cout << "10)\t For viewing memories press m \n";
			cout << "11)\t For switching user press z \n";
			cout << "12)\t For exit press x \n";

			
			cin >> functionality;
			User* current = SearchUserByID(currentuser);
			if (functionality == 'f')
			{
				current->ViewFriendList();
				cout << endl<<endl;
			}
			else if (functionality == 'p')
			{
				current->ViewLikedPages();
				cout << endl<<endl;
			}
			else if (functionality == 'h')
			{
				cout << "\n\n\nView Home of ";
				current->PrintName();
				cout << endl << endl;
				current->ViewHome();
				cout << endl << endl;
			}
			else if (functionality == 't')
			{
				current->ViewTimeline();
				cout << endl << endl;
			}
			else if (functionality == 'l')
			{
				cout << "\nEnter post you want to like: \n";
				char id[10] = { '\0' };
				cin >> id;
				ViewLikedBy(SearchPostByID(id));
				cout << endl;
				current->LikeAPost(SearchPostByID(id));
				cout << "\nAfter Liking Post 5 \n\n\n";
				ViewLikedBy(SearchPostByID(id));
				cout << endl;

				cout << endl << endl;
			}
			else if (functionality == 'r')
			{
				cout << "\nEnter page id you want to like: \n";
				char id[10] = { '\0' };
				cin >> id;
				cout << "\nDisplaying LikedPages before:\n";
				current->ViewLikedPages();
				current->LikePage(SearchPageByID(id));
				cout << "\nDisplaying LikedPages after Liking:\n";
				current->ViewLikedPages();
			

				cout << endl << endl;
			}
			else if (functionality == 'c')
			{
				cout << "\nEnter post you want to comment on: \n";
				char id[10] = { '\0' };
				cin >> id;
				posts* ptr = SearchPostByID(id);
				char text[100] = { '/0' };
				cout << "\nDisplaying Post:\n";
				ViewAPost(ptr);
				cout << "\nEnter comment you want to add:\n";
				//cin.getline(text,99);
				cin >> text;
				current->AddCommentByUser(ptr, text);
				cout << "\nDisplaying Post after adding comment:\n";
				ViewAPost(ptr);


				cout << endl << endl;
			}
			else if (functionality == 'a')
			{
				cout << "\nEnter post you want to view: \n";
				char id[10] = { '\0' };
				cin >> id;
				posts* ptr = SearchPostByID(id);
				cout << "\nDisplaying Post:\n";
				ViewAPost(ptr);

				cout << endl << endl;
			}
			else if (functionality == 'b')
			{
				cout << "\nEnter page you want to view: \n";
				char id[10] = { '\0' };
				cin >> id;
			
				cout << "\nDisplaying Page:\n";
				ViewPage(SearchPageByID(id));

				cout << endl << endl;
			}
			else if (functionality == 'm')
			{

				cout << "\nEnter post you want to search for in memories on: \n";
				char id[10] = { '\0' };
				cin >> id;
				posts* ptr = SearchPostByID(id);
				char text[100] = { '/0' };
				Memory m1;
				Memory* memoryPtr = &m1;
				cout << "\nEnter text you want to add:\n";
				cin >> text;
				//cin.getline(text,99);
				ShareMemory(memoryPtr, id, currentuser, text);
				current->ViewTimeline();

				current->SeeYourMemories();


				cout << endl << endl;
			}
			else if (functionality == 'z')
			{

				cout << "\t\t\t\t\tEnter user ID: ";
				cin >> currentuser;
				cout << "Set current user as: " << currentuser << endl << endl;
				SetCurrentUser(currentuser);

				
				cout << endl << endl;
			}
			
		}
		cout << "\n\t\t\t\t\t\t*****THANK YOU*****";
		return;

		cout << "\nView Page\n";
		char id[] = "p1";
		ViewPage(SearchPageByID(id));
		

		cout << "\n\nView a post: \n";
		cout << "\nDisplaying Post1: \n";
		ViewAPost(AllPosts[0]);
		

		User* current = SearchUserByID(currentuser);

		cout << "\n\nDisplaying Post7: \n";
		ViewAPost(AllPosts[6]);


		char temp[] = "post7";
		posts* ptr = SearchPostByID(temp);
		char text[] = "kaisa hai jaanii";
		current->AddCommentByUser(ptr, text);

		
		cout << "\n\nComment Added on Post7\n";
		cout << "\n\nDisplaying Post7: \n";
		ViewAPost(AllPosts[6]);


		cout << "\n\n\nView Home of ";
		current->PrintName();
		cout<< ":\n\n\n";
		current->ViewHome();



		cout << "\n\n\nView Memories\n\n";
		Memory m1;
		Memory* memoryPtr = &m1;
		char postidformemory[] = "post10";
		char memorytext[] = "Never thought I'll live to see this day";
		ShareMemory(memoryPtr, postidformemory, currentuser, memorytext);
		current->ViewTimeline();

		current->SeeYourMemories();

	}

    void LinkUsersAndPages() {

		ifstream fin("link.txt");
		
			for (int i = 0; i < totalUsers; i++)
			{
				char ID[5];
				fin >> ID;
				if ((ID[0] == '-'))
				{
					break;
				}
				User* temp = SearchUserByID(ID);

				while ((ID[0] != '-'))
				{
					fin >> ID;// “u16”
					temp->AddFriend(SearchUserByID(ID));
				}


				do {
					fin >> ID;
					temp->LikePage(SearchPageByID(ID));
				} while ((ID[0] != '-'));
			}
		
    }
	
	void SetCurrentUser(char* userId)
	{
		User* current = SearchUserByID(userId);
		cout << current->getFname() << " " << current->getLname() << " has been added as current user\n";
		
		/*current->ViewFriendList();
		cout << endl;
		current->ViewLikedPages();
		cout << endl;


		char id[] = "post5";
		ViewLikedBy(SearchPostByID(id));
		cout << endl;
		current->LikeAPost(SearchPostByID(id));
		cout << "\nAfter Liking Post 5 \n\n\n";
		ViewLikedBy(SearchPostByID(id));
		cout << endl;

		cout << "\nView Timeline:\n";
		current->ViewTimeline();
		*/
	}

	~Controller()
	{
		if (AllUsers)
		{
			for (int i = 0; i < totalUsers; ++i)
			{
				delete AllUsers[i];
			}
			delete[] AllUsers;
		}
		if (AllPages)
		{
			for (int i = 0; i < totalPages; ++i)
			{
				delete AllPages[i];
			}
		}
		delete[] AllPages;


		if (AllActivities)
		{
			/*for (int i=0;i<totalActivity;i++)
			{
				delete AllActivities[i];
			}*/

			delete[] AllActivities;
		}


		if (AllPosts)
		{
			for (int i = 0; i < totalPosts; i++)
			{
				delete AllPosts[i];
			}

			delete[] AllPosts;
		}

		

	}

	

};
int Controller::totalPages = 0;
int Controller::totalUsers = 0;
int Controller::totalPosts = 0;
int Controller::totalComments = 0;
int Controller::totalActivity = 0;


int main()
{
	Controller mainApp;
	cout << "\033[1;34m"; // Set text color to bright blue
	cout << "\n\n\n\n\n\n\t\t\t\t\t\tWELCOME TO FAST-BOOK\n\n\n\t\t\t\t\tCREATED BY:\tMuhammad Abdullah Iqbal (23L-0811)\n\n";

	mainApp.LoadData();

	return 0;
}	
