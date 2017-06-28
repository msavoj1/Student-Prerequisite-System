#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>      // main data structure ;
#include<fstream>            // For file management ;
#include<cstdlib>            // exit() function ;
#include<windows.h>          // system Appearances;
#include<conio.h>            // getch() function;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////

class Sub                      // Subject class;
{
public:
	string name;               //key :- name
	vector <string> prereq;    // prerequisite of subject ;
	int Num_Of_Std;            // number of inrolled student in subject ;
	Sub();                     // defult constructor ;
};

class Student                  // Student class ;
{
public:
	//............ Attributes ............
	string Username , password ;

	vector <string> qal , wanted_Sub ,results;     //key:- user name

	//........... functions ..............

	Student();            // defult constructor ;

	void Modify_qal(string username,unordered_map<string,Student>& St);

	void Modify_wanted_Sub(string username,unordered_map<string,Student>& St);

	void Search_Sub_Prereq(unordered_map<string,Sub> subs);

	string add_Student(unordered_map<string,Student>& St);

	void view_acc(string username,unordered_map<string,Student> St);
};


class Admin                  // Admin class;
{
public:
	//...........Attributes ..................

	string password,Username; // key:- username

	// ..........functions .....................
	void Add_Sub(unordered_map<string,Sub>& subs);

	void Remove_Sub(unordered_map<string,Sub>& subs);

	void Search_Student(unordered_map<string,Student> S);

	void View_sub(unordered_map<string,Sub> subs);

	void View_all_sub(unordered_map<string,Sub> subs);

	string add_admin(unordered_map<string,Admin>& ad);
};

//.................. indebendant functions ...........................

void Fill_In_Admin(unordered_map<string,Admin>& a );

void Fill_Out_admin(unordered_map<string,Admin>& a);


void Fill_In_Subject(unordered_map<string,Sub>& Sb);

void Fill_Out_Subject(unordered_map<string,Sub>& Sb);


void Fill_In_Student(unordered_map<string,Student>& St);

void Fill_Out_Student(unordered_map<string,Student>& St);

string Admin_Login(unordered_map<string,Admin> a);

string Student_Login(unordered_map<string,Student> s );

int show_Admin_Operations();

int show_Student_Operations();

int login_choice();

void Accept_Std(unordered_map<string,Sub> Sb,Student &st);

//............................................................ End;