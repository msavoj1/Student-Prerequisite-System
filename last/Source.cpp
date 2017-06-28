
#include"Header.h"

///////////////////////////////////////////////////////////////////////////////////////

// Handle data passing to and from files ;

// Fill_In functions :- Data travel from file ---> system data structures ;

// Fill_Out functions:- Data travel from system data structures ---> files for saving ;

void Fill_In_Subject(unordered_map<string,Sub>& Sb)
{
	string x,y;     

	int cnt=0;                     // rows counter .. count file rows for each subject ;
	Sub sub;                       // Subject Object ;
	char line[10000];              // Line to move throw file ;
	ifstream openfile;             // input sfile stream object;
	openfile.open("subjects.txt"); 
	while(!openfile.eof())         // loob to move throw file ;
	{
		openfile.getline(line,10000);
		if(cnt==0)                      // 0 ---> subject name position in file ;
		{
			x=line;
			cnt++;
		}
		
		else if(cnt==1)                // 1 ---> subject prerequisite position in file ;
		{
		char *token=strtok(line,"-");
		sub.prereq.clear();
			while(token)
			{
				sub.prereq.push_back(token);  // fill prerequisite vector ;
				token=strtok(NULL,"-");
			}
			sub.name=x;
			Sb[x]=sub;                    // insert subjects into data structure ;
			cnt=0;
		}
    }
	openfile.close();
}

void Fill_Out_Subject(unordered_map<string,Sub>& Sb)
{
	ifstream infile;                           // input stream object;
	infile.open("subjects.txt");
	infile.clear();                            // clear file history
	unordered_map<string,Sub>::iterator it;
	vector<string>:: iterator it2;
	ofstream update;
	update.open("subjects.txt");
	for(it=Sb.begin() ; it!=Sb.end(); it++)    // Update file ;
	{
		update<<it->first<<endl;
		for(it2=it->second.prereq.begin() ; it2!=it->second.prereq.end() ; it2++)
		{
			update<<*it2<<"-";
		}
		update<<endl;
	}
	update.close();
}

void Fill_In_Admin(unordered_map<string,Admin>& a )
{
	ifstream infile;
	int cnt=0;
	string x,y;
	Admin z;
	char line[10000];
	infile.open("admin.txt");
	while(!infile.eof())
	{
		infile.getline(line,10000);
		if(cnt==0)                    // 0 ---> admin name position ;
		{
			x=line;
			cnt++;
		}
		else if(cnt==1)                // 1 ---> Admin password position ;
		{
			y=line;
			z.Username=x;
			z.password=y;
			a[x]=z;
			cnt=0;
		}
	}
	infile.close();
}

void Fill_Out_admin(unordered_map<string,Admin>& a)
{
	ifstream infile;
	infile.open("admin.txt");
	infile.clear();
	unordered_map<string,Admin>::iterator it;
	ofstream update;
	update.open("admin.txt");                      // update admin file ;
	for(it=a.begin() ; it!=a.end(); it++)
	{
		update<<it->first<<endl<<it->second.password<<endl;
	}
	update.close();

}

void Fill_In_Student(unordered_map<string,Student>& St)
{
	int cnt=0;
	string x,y;
	Student s;
	char line[10000];
	ifstream infile;
	infile.open("Student.txt");
	while(!infile.eof())
	{
		infile.getline(line,10000);
		if(cnt==0)                        // 0 ---> student name position ;
		{
			x=line;
			cnt++;
		}
		else if(cnt==1)                  // 1 ---> student password position;
		{
			y=line;
			cnt++;
		}
		else if(cnt==2)                  // 2 ---> student qualifications position;
		{
		  char *token=strtok(line,"-");
		  s.qal.clear();
			while(token)
			{
				s.qal.push_back(token);
				token=strtok(NULL,"-");
			}	
			cnt++;
		}
		else if(cnt==3)                  // 3 ---> student wanted subject position ;
		{
		    char *token=strtok(line,"-");
			s.wanted_Sub.clear();
			while(token)
			{
				s.wanted_Sub.push_back(token);
				token=strtok(NULL,"-");
			}		
			s.Username=x;
			s.password=y;
			St[x]=s;
			cnt=0;
		}
	}
	infile.close();
}

void Fill_Out_Student(unordered_map<string,Student>& St)
{
	ifstream infile;
	infile.open("Student.txt");
	infile.clear();
	unordered_map<string,Student>::iterator it;
	vector<string>::iterator it2;
	ofstream update;
	update.open("Student.txt");
	for(it=St.begin() ; it!=St.end(); it++)          // update student file ;
	{
		update<<it->first<<endl<<it->second.password<<endl;
		for(it2=it->second.qal.begin() ; it2!=it->second.qal.end() ; it2++)
		{
			update<<*it2<<"-";
		}
		update<<endl;
		for(it2=it->second.wanted_Sub.begin() ; it2!=it->second.wanted_Sub.end() ; it2++)
		{
			update<<*it2<<"-";
		}
		update<<endl;
	}
	update.close();
}

//////////////////////////////////////////////////////////////////////////////////////

Sub::Sub()      // subject defult constructor;
{
	Num_Of_Std=0;
	prereq.push_back("No required prerequisite .");
}

// Admin functions :-

string Admin::add_admin(unordered_map<string,Admin>& ad)   // create account;
{
	Admin a;                 // admin object;

	unordered_map<string,Admin>::iterator it;

	cout<<"User name  and pssword can not include spaces ... "<<endl;  // constraint 

	cout<<"Enter user name :  ";
	cin>>a.Username;
	cout<<"Enter password  :  ";
	cin>>a.password;

	it=ad.find(a.Username);

	while(it!=ad.end())
	{
	system("CLS");
	cout<<"Username you entered is allready used by another user ..."<<endl;
	cout<<"_________________________________________________________"<<endl;
	cout<<"Enter user name :  ";
	cin>>a.Username;
	cout<<"Enter password  :  ";
	cin>>a.password;

	it=ad.find(a.Username);
	}

	ad[a.Username]=a;
	cout<<"________________________________"<<endl;
	cout<<"Your username is : " <<a.Username<<endl;
	cout<<"________________________________"<<endl;
	cout<<"Your password is : " <<a.password<<endl;
	cout<<"________________________________"<<endl;
	return a.Username;
}

void Admin::Add_Sub(unordered_map<string,Sub> &subs)
{
	Sub s;                                     // subject object;
	string prereq_name,c;
	unordered_map<string,Sub>::iterator it;


	cout<<"Enter name of the subject : "<<endl;
	cout<<"____________________________"<<endl;
	cin.ignore();
	getline(cin,s.name);

	it=subs.find(s.name);

	if(it!=subs.end())
	{
		cout<<"Subject is allready found !! ..."<<endl;
		cout<<"________________________________"<<endl;
	}


	c=s.name;
	

	cout<<endl;

	

	cout<<"Enter prerequisite : "<<endl<<"To escape adding prerequisite 'press E + Enter key' ... "<<endl;
	cout<<"_____________________"<<endl;

	s.prereq.clear();

	getline(cin,prereq_name);

	if(prereq_name!="E")
		s.prereq.clear();

	while(prereq_name!="E")
	{
		s.prereq.push_back(prereq_name);
		getline(cin,prereq_name);
	}

	subs[c]=s;
}

void Admin::Remove_Sub(unordered_map<string,Sub>& subs)
{
	string removed;                             // string holdes removed sub..'s name;

	unordered_map<string,Sub>::iterator it;

	cout<<"Enter name of subject you want to remove : "<<endl;
	cin.ignore();
	getline(cin,removed);

	it=subs.find(removed);

	if(it!=subs.end())
	{
		subs.erase(removed);                    // erase subject from data structure ;
		cout<<"Removed successfully ..."<<endl<<endl;
	}

	else
	{
		cout<<"Subject not found !! ..." <<endl;
		cout<<"________________________"<<endl;
	}
}

void Admin::Search_Student(unordered_map<string,Student> S)
{
	string un;                                 // holdes searched student name;
	unordered_map<string,Student>::iterator it;
	vector<string>::iterator it2,it3;             // iterators ;

	cout<<"Enter username of student you want to search for :  ";

	cin>>un;

	it=S.find(un);

	if(it!=S.end())        // if found --> show data ;
	{
		cout<<" Username : " << it->first <<endl<<endl;
		cout<<"____________"<<endl;
		cout<<"Student qualifications :- "<<endl<<endl;
		cout<<"__________________________"<<endl;
		
		for(it2=S[un].qal.begin();it2!=S[un].qal.end();it2++)
			cout<<*it2<<endl;

		cout<<"__________________________"<<endl;

		cout<<"Student wanted subjects :- "<<endl;
		cout<<"___________________________"<<endl;

		for(it3=S[un].wanted_Sub.begin();it3!=S[un].wanted_Sub.end();it3++)
			cout<<*it3<<endl;
		cout<<"___________________________"<<endl;
	}

	else                    // if not found --> show text message ;
	{
		cout<<"Student not found !! ... " <<endl;
		cout<<"_________________________"<<endl;
	}

}

void Admin::View_sub(unordered_map<string,Sub> subs)
{
	string name;                            // holdes subject name;
	unordered_map<string,Sub>::iterator it;
	vector<string>::iterator it2;            // iterators ;

	cout<<"Enter name of subject you want to search for : "<<endl;
	cout<<"_______________________________________________"<<endl;
	cin.ignore();
	getline(cin,name);

	it=subs.find(name);

	if(it!=subs.end())                      // if found --> show data ;
	{
		cout<<"Subject Named is : "<<it->first<<endl<<endl;
		cout<<"___________________"<<endl;
		cout<<"Subject prerequisite :- "<<endl;
		cout<<"________________________"<<endl;
		
		for(it2=subs[name].prereq.begin();it2!=subs[name].prereq.end();it2++)
			cout<<*it2<<endl;
		cout<<"________________________"<<endl;
		cout<<"Number of enrolled students = " << it->second.Num_Of_Std<<endl<<endl;
		cout<<"______________________________"<<endl;
	}

	else                                   // if not found --> show text message;
	{
		cout<<"Subject Does not exist"<<endl;
		cout<<"______________________"<<endl;
	}
}

void Admin::View_all_sub(unordered_map<string,Sub> subs)
{
	unordered_map<string,Sub>::iterator it;
	if(subs.size()==0)
		cout<<"No subjects to be showen ..."<<endl<<endl;
	else
	{
	    cout<<"Subject :-" << endl;
		cout<<"__________" <<endl;
	    for(it=subs.begin();it!=subs.end();it++)
		    cout << it->first <<endl;

		cout<<"_________________________________"<<endl;
	}

}

/////////////////////////////////////////////////////////////////////////////////////

// Student's functions :-

Student::Student()      // defult constructor ;
{
	qal.push_back("No initial qualifications .");
	wanted_Sub.push_back("No initial subjects .");
	results.push_back("No initial results to be showen .");
}

string Student::add_Student(unordered_map<string,Student> &St)
{
	Student a;

	unordered_map<string,Student>::iterator it;

	cout<<"User name and password can not include spaces ... "<<endl;  // constraint ;

	cout<<"Enter user name  :  ";
	cin>>a.Username;
	cout<<"Enter password   :  ";
	cin>>a.password;

	it=St.find(a.Username);

	while(it!=St.end())              // if user name is found in data structure before
	{                                // Unique identifire ...;
	system("CLS");
	cout<<"Username you entered is allready being used by another user ..."<<endl;
	cout<<"_______________________________________________________________"<<endl;
	cout<<"Enter user name  :  ";
	cin>>a.Username;
	cout<<"Enter password   :  ";
	cin>>a.password;

	it=St.find(a.Username);
	}
	
	
	string qual_name,subj_want;

	
	cout<<"Enter your qualifications : " <<endl<<" To escape adding qualifications press 'E + Enter key' ."<<endl<<endl;
	cout<<"____________________________"<<endl;
	
	getline(cin,qual_name);

	if(qual_name!="E")                    // Enter "E" to stop adding;
		a.qal.clear();

	while(qual_name!="E")
	{
		a.qal.push_back(qual_name);
		getline(cin,qual_name);
	}
	
	cout<<"Enter wanted subjects : " <<endl<<" To escape adding wanted subjects press 'E + Enter key' ."<<endl<<endl;
	cout<<"________________________"<<endl;
	
	getline(cin,subj_want);
	
	if(subj_want!="E")                     // Enter "E" to stop adding;
	{
		a.wanted_Sub.clear();
		a.results.clear();
	}

	while(subj_want!="E")
	{
		a.wanted_Sub.push_back(subj_want);
		getline(cin,subj_want);
	}

	St[a.Username]=a;
	//.....................show login data ................
	system("CLS");
	cout<<"Your username is : " <<a.Username<<endl;
	cout<<"________________________________"<<endl;
	cout<<"Your password is : " <<a.password<<endl;
	cout<<"________________________________"<<endl;

	return a.Username;
}

void Student:: Modify_qal(string username,unordered_map<string,Student> &St)
{
	string s;

	cout<<"Enter your new qualifications :"<<endl<<"To escape adding press 'E + Enter key' :"<<endl<<endl;

	St[username].qal.clear();
	cin.ignore();                         // Enter new qualification ;
	getline(cin,s);

	while(s!="E")                         // Enter "E" to stop adding;
	{
		St[username].qal.push_back(s);
		getline(cin,s);
	}

}

void Student:: Modify_wanted_Sub(string username,unordered_map<string,Student> &St)
{
	string s;
	cout<<"Enter wanted subjects :"<<endl<<"To escape adding wanted subjects press 'E + Enter key' :"<<endl;
	cout<<"_______________________"<<endl;
	St[username].wanted_Sub.clear();
	cin.ignore();                       // enter new wanted subjects names;
	getline(cin,s);

	while(s!="E")              // enter "E" to stop adding;
	{
		St[username].wanted_Sub.push_back(s);
		getline(cin,s);
	}

}

void Student::view_acc(string username,unordered_map<string,Student> St)
{
	vector<string>::iterator it;       // iterator to hold data to be showen;

	cout<<"Username :  "<<St[username].Username<<endl;
	cout<<"____________"<<endl;
	cout<<"Qualifications :-  " <<endl<<endl;
	cout<<"___________________"<<endl;

	for(it=St[username].qal.begin() ; it!=St[username].qal.end() ; it++)
		cout<<*it<<endl;

	cout<<"___________________"<<endl;

	cout<<"Wanted subjects for this term :- "<<endl;
	cout<<"_________________________________"<<endl;

	for(it=St[username].wanted_Sub.begin() ; it!=St[username].wanted_Sub.end() ; it++)
		cout<<*it<<endl;

	cout<<"___________________"<<endl;
}

void Student::Search_Sub_Prereq(unordered_map<string,Sub> subs)
{
	unordered_map<string,Sub>::iterator it;      // iterator holdes subject;
	vector<string>::iterator it2;                // iterator holdes prerequisite vector ;
	string name, s;

	cout<<"Enter name of subject you search for :"<<endl;
	cout<<"______________________________________"<<endl;

	cin.ignore();
	getline(cin,name);

	it=subs.find(name);
	if(it!=subs.end())                // if found show prerequisite;
	{
		for(it2=subs[name].prereq.begin();it2!=subs[name].prereq.end();it2++)
			cout<<*it2<<endl;
		cout<<"________________________"<<endl;
	}

	else                              // if not found show text message;
	{
		cout<<"Subject not found !! ..."<<endl; 
		cout<<"________________________"<<endl;
	}

}

////////////////////////////////////////////////////////////////////////////////////

// Controle menues and loging functions :-

int show_Admin_Operations()          // Admin Operations menue "A_O_M"
{
	int operation;                         // holdes admin choice flag ;
	cout<<"press ' number of oberation + Enter Key ' : "<<endl;   // choosing way ;
	cout<<"____________________________________________"<<endl;
	cout<<"1- Add subject."<<endl;
	cout<<"__________"<<endl;
	cout<<"2- Remove subject."<<endl;
	cout<<"__________"<<endl;
	cout<<"3- view all subjects."<<endl;
	cout<<"__________"<<endl;
	cout<<"4- view spesific subject."<<endl;
	cout<<"__________"<<endl;
	cout<<"5- Search spesific student."<<endl;
	cout<<"__________"<<endl;
	cout<<"6- log out."<<endl;
	cout<<"___________________________"<<endl;
	cin>>operation;                       // get admin choice ;

	return operation;                     // returns flage of user choice;
}

string Admin_Login(unordered_map<string,Admin> a )
{
	string un,pass;

	cout<<"Enter Username  :  " ;
	cin>>un;
	cout<<"Enter password  :  ";
	cin>>pass;

	unordered_map<string,Admin>::iterator it;
	it=a.find(un);

	while(a[un].password != pass || it==a.end())   // check correctness of login data ;
	{                                              // if correct ,, breack loop ,, Log in;
		system("CLS");
		cout<<"Wrong username or password ..."<<endl;
		cout<<"______________________________"<<endl;
	    cout<<"Enter Username  :  " ;
	    cin>>un;
	    cout<<"Enter password  :  ";
	    cin>>pass;
		
		it=a.find(un);                            // search for entered user name in data structure;
	}

		return un;             // returns unique key for loged in User ;
}

int show_Student_Operations()         // Student Operations menue "S_O_M"
{
	int operation;                    // holdes admin choice flag ;

	cout<<"press 'number of oberation + Enter' : " <<endl;
	cout<<"______________________________________" <<endl;
	cout<<"1- Enter or modify your qualifications."<<endl;
	cout<<"__________"<<endl;
	cout<<"2- Enter or modify your wanted subjects."<<endl;
	cout<<"__________"<<endl;
	cout<<"3- View account."<<endl;
	cout<<"__________"<<endl;
	cout<<"4- View subject's prerequisite."<<endl;
	cout<<"__________"<<endl;
	cout<<"5- View results of applyed prerequisite ."<<endl;
	cout<<"__________"<<endl;
	cout<<"6- log out ."<<endl;
	cout<<"_______________________________"<<endl;
	cin>>operation;                  // get student choice ;

	return operation;                // returns flage of user choice;
}

string Student_Login(unordered_map<string,Student> s )
{
	string un,pass;
	cout<<"Enter Username  :  " ;
	cin>>un;
	cout<<"Enter password  :  ";
	cin>>pass;

	unordered_map<string,Student>::iterator it;
	it=s.find(un);
	
	while(s[un].password != pass || it==s.end())    // check correctness of login data ;
	{                                               // if correct ,, breack loop ,, Log in;
	
		system("CLS");
		cout<<"Wrong username or password ..."<<endl;
		cout<<"______________________________"<<endl;
	    cout<<"Enter Username  :  " ;
		cin>>un;
	    cout<<"Enter password  :  ";
		cin>>pass;
		
		it=s.find(un);
	}
		return un;                                 // return user unique key ;
}

int login_choice()       // System Top menue ;
{
	int choice;          // flage of user choice ;
	
	cout<<"Enter 'number of choice + Enter key' : "<<endl;
	cout<<"___________________________________"<<endl;
	cout<<"1- Enter as Admin."<<endl;
	cout<<"__________"<<endl;
	cout<<"2- Enter as Student."<<endl;
	cout<<"__________"<<endl;
	cout<<"3- Create Admin account."<<endl;
	cout<<"__________"<<endl;
	cout<<"4- Create Student account ."<<endl;
	cout<<"__________"<<endl;
	cout<<"5- Exit programme."<<endl;
	cout<<"___________________________"<<endl;
	cin>> choice;

	return choice;        // return flage ;
}

void Accept_Std(unordered_map<string,Sub> Sb,Student &st)
{
	int allow=1;
	vector<string> ::iterator want=st.wanted_Sub.begin(),qual,prerq,res;


	for(; want!=st.wanted_Sub.end() ; want++)  // Go throw wanted subject's names;
	{
		allow=1;      // flag to accept or reject student in subject ;

	   string want_name=(*want);    // string holdes wanted subject name;

	   prerq=Sb[want_name].prereq.begin();  // holdes vector of wanted subject prerequisite ;

	   for(;prerq!=Sb[want_name].prereq.end();prerq++)   // Go throw wanted subject prerquisite ;
	   {
		   qual=find(st.qal.begin(),st.qal.end(),(*prerq)); // find prerequisite in qualifications

		   if(*prerq=="No required prerequisite .") // if subject don't have prerequisite ;
		   {
			   allow=1;
		   break;
	      }
		   if(qual==st.qal.end())                  // if not found student is rejected
		   {
			   st.results.push_back(want_name + " Rejected ");  // fill result vector;
			   allow=0;
			   break;
		   }

	   }
	    //if(st.results[0]=="No initial results to be showen ." && allow==1) // clear result vector
		  // st.results.clear()

	    if(allow==1)        // if all prerequisite found --> accept student ;
		{
		    st.results.push_back(want_name + " Accepted "); // fill results vector;
		    Sb[want_name].Num_Of_Std ++;                    // increment number of inrolled students
		}

	}

	res=st.results.begin();

	for(;res!=st.results.end();res++)     // Print results vector ;
		cout<<*res<<endl;
	cout<<endl;

}

