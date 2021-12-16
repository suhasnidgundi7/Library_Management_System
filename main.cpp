//***************************************************************
//Library Management System
//****************************************************************

#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <iomanip>
#include <windows.h>

using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class Book
{
    char book_no[6];
    char book_name[50];
    char author_name[20];

public:
    void create_book()
    {
        cout << "\n NEW BOOK ENTRY...." << endl;
        cout << endl << "Enter The Book No.";
        cin >> book_no;
        cout << "Enter The Book Name : ";
        gets(book_name);
        cout << "Enter The Book Author's Name : ";
        gets(author_name);
    }
    void show_book()
    {
        cout << endl << "Book No. : " << book_no;
        cout << endl << "Book Name : ";
        puts(book_name);
        cout << endl << "Book Author Name : ";
        puts(author_name);
    }
    void modify_book(){
        cout << endl << "Book No. " << book_no;
        cout << endl << "Modify Book Name";
        gets(book_name);
        cout << endl << "Modify Book Author's Name : ";
        gets(author_name);
    }

    char * retbno()
    {
        return book_no;
    }

    void report()
    {
        cout << book_no << setw(30) << book_name << setw(30) << author_name << endl;
    }
};

class Student
{
    char admission_no[6];
    char student_name[20];
    char student_book_no[6];
    int token;

public:
    void create_student()
    {
        cout << endl << "!!! *** NEW STUDENT ENTRY *** !!!" << endl;
        cout << endl << "Enter Admission No. ";
        cin >> admission_no;
        cout << endl << endl << "Enter Student Name : ";
        gets(student_name);
        token = 0;
        student_book_no[0] = '/0';
        cout << endl << endl << "!!! SUCCESS !!! Student Record Created !!!";
    }    
    void show_student()
    {
        cout << endl << "Addmission No. : \t\t" << admission_no;
        cout << endl << "Student Name : ";
        puts(student_name);
        cout << endl << "No. Of Book Issued : " << token;
        if(token==1)
        {
            cout << endl << "Book no. " << student_book_no;
        }
    }
    void modify_student()
    {
        cout << endl << "Addmission No. : " << admission_no;
        cout << endl << "Modify Student Name : ";
        gets(student_name);
    }

    char * retadmno()
    {
        return admission_no;
    }
    char * retstbno()
    {
        return student_book_no;
    }
    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token=1;
    }
    void resettoken()
    {
        token=0;
    }
    void getstbno(char t[])
    {
        strcpy(student_book_no, t);
    }
    void report()
    {
        cout << "\t\t" << admission_no << setw(20) << student_name << setw(10) << token << endl;
    }
};

//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp, fp1;
Book bk;
Student st;

//***************************************************************
//    	function to write in file
//****************************************************************
void write_book()
{
    char ch;
    fp.open("book.txt", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char*)&bk, sizeof(Book));
        cout << "\n\nDo You Want To Add More Record....(Yes/No?)";
        cin >> ch;
    } while (ch=='y'|| ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.txt", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st, sizeof(Student));
        cout << "\n\nDo You Want To Add More Record....(Yes/No?)";
        cin >> ch;
    } while (ch=='y'|| ch=='Y');
    fp.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_spb(char n[])
{
    cout << '\n BOOK DETAILS \n';
    int flag = 0;
    fp.open("book.txt", ios::in);
    while (fp.read((char*)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.retbno(), n)==0)
        {
            bk.show_book();
            flag=1;
        }
        fp.close();
        if (flag==0)
        {
            cout << "\n\nBook Does Not Exits";
        }        
    }    
}

void display_sps(char n[])
{

}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	COORD c;
    c.X = 35;
    c.Y = 11;

    COORD c1;
    c1.X = 35;
    c1.Y = 14;

    COORD c2;
    c2.X = 35;
    c2.Y = 17;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << "LIBRARY";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c1);
	cout << "MANAGEMENT";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c2);
	cout << "SYSTEM";
	cout << "\n\nMADE BY\t: Suhas Nidgundi";
	cout << "\n\nCollege\t: Venutai Chavan Polytechnic";
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//***************************************************************

int main()
{
    char ch;
    intro();

    do
    {
        cout << endl << endl << endl << "\t" << "MAIN MENU";
        cout << endl << endl << "\t" << "01. BOOK ISSUE";
        cout << endl << endl << "\t" << "02. BOOK DEPOSIT";
        cout << endl << endl << "\t" << "03. ADMINISTRATOR MENU";
        cout << endl << endl << "\t" << "04. EXIT";
        cout << endl << endl << "\t" << "PLEASE SELECT YOUR OPTION (1-4) : ";
        ch=getche();
        switch (ch)
        {
        case '1':
            /* code */
            break;

        case '2':
            /* code */
            break;

        case '3':
            /* code */
            break;
        
        case '4':
            exit(0);

        default:
            cout << "\a";
            break;
        }
    } while (ch!=4);    
}

//****************************END OF PROJECT*********************************//