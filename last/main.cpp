#include"Header.h"

int main()
{

	int flag, operation;  //flages to hold user choice from menue;
	
	string loged_in;     // holdes user's name to determine which user is loged in system ;

	unordered_map<string,Admin> a;  // Data structure to hold Admins in the system ;
	unordered_map<string,Student> st;  // Data structure to hold Students in the system ;
	unordered_map<string,Sub> sb;   // Data structure to hold Subjects in the system ;
	//////////////////////////////////////////////////////////////////////////////////////////
	
	// this part controles the insertion of saved data from files into system at run time ;
	Fill_In_Admin(a);       // Insertion of Admins;
    Fill_In_Subject(sb);    // Insertion of Subjects;
	Fill_In_Student(st);    // Insertion of Students;


	/////////////////////////////////////////////////////////////////////////////////////////

	// this part handles font size and color in console;
	HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	PCONSOLE_FONT_INFOEX console_info = new CONSOLE_FONT_INFOEX;
    console_info->cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, console_info);
    console_info->dwFontSize.X = 9; //default 8
    console_info->dwFontSize.Y = 18; //default 12 
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, console_info);
	////////////////////////////////////////////////////////////////////////////////////////

	top_menue : flag = login_choice(); // Top menue of the system ;

	if(flag == 1)                      // when user chose "1" from menue ;
	{
		system("CLS");                 // clear system screen ;
		loged_in = Admin_Login( a );   // handles admin login to system 
		                               // and determine which user is loged in system ;

Admin_menue :                          // Admin Operations menue ;
		system("CLS");
	    operation = show_Admin_Operations(); 

		if(operation==1)              // choice "1" from admin operation menue;
		{
			system("CLS");

			a[loged_in].Add_Sub(sb);  // enable admin to add subject;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();                  // holdes screen tell pressing a key ;
			system("CLS");
			goto Admin_menue;         // go back to Admen operations menue;
			
		}	
		
		else if(operation==2)         // coice "2" from admin operation menue;
		{
			system("CLS");
			a[loged_in].Remove_Sub(sb);// Enable admin to remove subject ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("CLS");
			goto Admin_menue;
		}

		else if(operation==3)         // choice "3" from admin operation menue ;
		{
			system("CLS");
			a[loged_in].View_all_sub(sb); // View names of all subjects ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("CLS");
			goto Admin_menue;
		}

		else if(operation==4)         // choice "4" for A_O_M
		{
			system("CLS");
			a[loged_in].View_sub(sb); // Enable admin to enter specifice subject ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("CLS");
			goto Admin_menue;
		}

		else if(operation==5)        // choice "5" from A_O_M;
		{
			system("CLS");
			a[loged_in].Search_Student(st); // Enable user search specifice student ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("CLS");
			goto Admin_menue;
		}

		else
		{
			system("CLS");
			Fill_Out_admin(a);              // Save Admin data in files 
	        Fill_Out_Student(st);           // .... student ...........
	        Fill_Out_Subject(sb);           // .... subject ...........
			goto top_menue;
		}

	}


	/////////////////////////////////////////////////////////////////////////////////////////

	else if(flag==2)                       // choice "2" from Top menue ;
	{
		loged_in=Student_Login(st);        // handles student login to system ;

student_menue :                            // Student Operations menue;
		system("CLS");
		operation = show_Student_Operations();

		if(operation==1)                    // choice "1" from S_O_M;
		{
			system("CLS");
			st[loged_in].Modify_qal(loged_in,st);  // Allow student modify his qualifications;

			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("cls");
			goto student_menue;
		}

		else if(operation==2)              // choice "2" from S_O_M;
		{
			system("CLS");
			st[loged_in].Modify_wanted_Sub(loged_in,st); // allow student modify his wanted sub..s ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("cls");
			goto student_menue;
		}
		
		else if(operation==3)             //choice "3" from S_O_M;
		{
			system("CLS");
			st[loged_in].view_acc(loged_in,st);  // View loged in student account ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("cls");
			goto student_menue;
		}
		
		else if(operation==4)                   // choice "4" from S_O_M ;
		{
			system("CLS");
			st[loged_in].Search_Sub_Prereq(sb);  // Enable student seach subject's prerequisite ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
		    system("cls");
			goto student_menue;
		}

		else if(operation==5)                  // choice "5" from S_O_M ;
		{
			system("CLS");
			Accept_Std(sb,st[loged_in]);       // determine courses student was accepted in 
			                                   // and fill results ;
			cout<<"Press any key to go back to operations menue : "<<endl;
			getch();
			system("cls");
			goto student_menue;
		}

		else
		{
			system("cls");
			Fill_Out_admin(a);
	        Fill_Out_Student(st);
	        Fill_Out_Subject(sb);
			goto top_menue;
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////



	else if(flag==3)                          //choice "3" from Top menue;
	{
		system("CLS");
		loged_in = a[loged_in].add_admin(a);  // Create new admin acount ;
		cout<<"Press any key to go back to operations menue : "<<endl;
	    getch();
		system("cls");
		goto Admin_menue;
	}


	//////////////////////////////////////////////////////////////////////////////////////////

	else if(flag==4)                         // choice "4" from top menue;
	{
		system("CLS");
		loged_in = st[loged_in].add_Student(st); // Create new student account ;
		cout<<"Press any key to go back to operations menue : "<<endl;
		getch();
		system("cls");
		goto student_menue;
	}


	////////////////////////////////////////////////////////////////////////////////////

	// this part saves data of the system in files after exit ;

	else 
	{
		Fill_Out_admin(a);
	    Fill_Out_Student(st);
	    Fill_Out_Subject(sb);
		exit(0);
	}

	///////////////////////////////////////////////////////////////////////////////////

	return 0;

}