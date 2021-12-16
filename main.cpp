//***************************************************************
// Library Management System
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
        cout << endl
             << "Enter The Book No.";
        cin >> book_no;
        cout << "Enter The Book Name : ";
        gets(book_name);
        cout << "Enter The Book Author's Name : ";
        gets(author_name);
    }
    void show_book()
    {
        cout << endl
             << "Book No. : " << book_no;
        cout << endl
             << "Book Name : ";
        puts(book_name);
        cout << endl
             << "Book Author Name : ";
        puts(author_name);
    }
    void modify_book()
    {
        cout << endl
             << "Book No. " << book_no;
        cout << endl
             << "Modify Book Name";
        cin >> book_name;
        cout << endl
             << "Modify Book Author's Name : ";
        cin >> author_name;
    }

    char *retbno()
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
        cout << endl
             << "!!! *** NEW STUDENT ENTRY *** !!!" << endl;
        cout << endl
             << "Enter Admission No. ";
        cin >> admission_no;
        cout << endl
             << endl
             << "Enter Student Name : ";
        puts(student_name);
        token = 0;
        student_book_no[0] = '/0';
        cout << "\n\n!!! SUCCESS !!! Student Record Created !!!";
    }
    void show_student()
    {
        cout << endl
             << "Addmission No. : \t\t" << admission_no;
        cout << endl
             << "Student Name : ";
        puts(student_name);
        cout << endl
             << "No. Of Book Issued : " << token;
        if (token == 1)
        {
            cout << endl
                 << "Book no. " << student_book_no;
        }
    }
    void modify_student()
    {
        cout << endl
             << "Addmission No. : " << admission_no;
        cout << endl
             << "Modify Student Name : ";
        cin >> student_name;
    }

    char *retadmno()
    {
        return admission_no;
    }
    char *retstbno()
    {
        return student_book_no;
    }
    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token = 1;
    }
    void resettoken()
    {
        token = 0;
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
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char *)&bk, sizeof(Book));
        cout << "\n\nDo You Want To Add More Record....(Yes/No?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char *)&st, sizeof(Student));
        cout << "\n\nDo You Want To Add More Record....(Yes/No?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_spb(char n[])
{
    cout << '\n BOOK DETAILS \n';
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.retbno(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
        fp.close();
        if (flag == 0)
        {
            cout << "\n\nBook Does Not Exits";
        }
    }
}

void display_sps(char n[])
{
    cout << '\n STUDENT DETAILS \n';
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.retadmno(), n) == 0)
        {
            st.show_student();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
    {
        cout << "\n\nStudent Does Not Exist";
    }
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_book()
{
    char n[6];
    int found = 0;
    cout << "\n\n\tMODIFY BOOK RECORD.....";
    cout << "\n\n\tEnter The Book No. Of The Book : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(Book)) && found == 0)
    {
        if (strcmpi(bk.retbno(), n) == 0)
        {
            bk.show_book();
            cout << "Enter The New Detail Of Book" << endl;
            bk.modify_book();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(Book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\n Record Not Found";
    }
}

void modify_student()
{
    char n[6];
    int found = 0;
    cout << "\n\n\tMODIFY STUDENT RECORD.....";
    cout << "\n\n\tEnter The Admission No. Of The Student";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.retadmno(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter The New Detail Of The Student" << endl;
            st.modify_student();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(Student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\n No Record Found";
    }
}

//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
    fp.open("student.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tSTUDENT LIST\n\n";
    cout << "==================================================================\n";
    cout << "Admission No." << setw(10) << "        Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";

    while (fp.read((char *)&st, sizeof(Student)))
    {
        st.report();
    }

    fp.close();
}

//***************************************************************
//    	function to issue book
//****************************************************************

void book_issue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	cout << "\n\nBOOK ISSUE ...";
	cout << "\n\n\tEnter The student's admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(Student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 0)
			{
				cout << "\n\n\tEnter the book no. ";
				cin >> bn;
				while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), bn) == 0)
					{
						bk.show_book();
						flag = 1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char *)&st, sizeof(Student));
						cout << "\n\n\t Book issued successfully\n\nPlease Note: Write the current date 						in backside of your book and submit within 15 days fine Rs. 1 for each day 							after 15 days period";
					}
				}
				if (flag == 0)
					cout << "Book no does not exist";
			}
			else
				cout << "You have not returned the last book ";
		}
	}
	if (found == 0)
		cout << "Student record not exist...";
	getch();
	fp.close();
	fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void book_deposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	cout << "\n\nBOOK DEPOSIT ...";
	cout << "\n\n\tEnter The student's admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char *)&st, sizeof(Student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 1)
			{
				while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), st.retstbno()) == 0)
					{
						bk.show_book();
						flag = 1;
						cout << "\n\nBook deposited in no. of days";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine has to deposited Rs. " << fine;
						}
						st.resettoken();
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char *)&st, sizeof(Student));
						cout << "\n\n\t Book deposited successfully";
					}
				}
				if (flag == 0)
					cout << "Book no does not exist";
			}
			else
				cout << "No book is issued..please check!!";
		}
	}
	if (found == 0)
		cout << "Student record not exist...";
	getch();
	fp.close();
	fp1.close();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student()
{
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.retadmno(), n) != 0)
            fp2.write((char *)&st, sizeof(Student));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    getch();
}

void delete_book()
{
    char n[6];
    cout << "\n\n\n\tDELETE BOOK ...";
    cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.retbno(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(Book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}

//***************************************************************
//    	function to display Books list
//****************************************************************
void display_allb()
{
    fp.open("book.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }

    cout << "\n\n\t\tBook LIST\n\n";
    cout << "=========================================================================\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    cout << "=========================================================================\n";

    while (fp.read((char *)&bk, sizeof(Book)))
    {
        bk.report();
    }
    fp.close();
}

//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//***************************************************************

void admin_menu()
{
    int ch2;
    cout << "\n\n\n\tADMINISTRATOR MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout << "\n\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\n\t5.DELETE STUDENT RECORD";
    cout << "\n\n\t6.CREATE BOOK ";
    cout << "\n\n\t7.DISPLAY ALL BOOKS ";
    cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout << "\n\n\t9.MODIFY BOOK ";
    cout << "\n\n\t10.DELETE BOOK ";
    cout << "\n\n\t11.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-11) ";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        write_student();
        break;
    case 2:
        display_alls();
        break;
    case 3:
        char num[6];
        cout << "\n\n\tPlease Enter The Addmission No.";
        cin >> num;
        display_sps(num);
        break;
    case 4:
        modify_student();
        break;
    case 5:
        delete_student();
        break;
    case 6:
        write_book();
        break;
    case 7:
        display_allb();
        break;
    case 8:
    {
        char num[6];
        cout << "\n\n\tPlease Enter The book No. ";
        cin >> num;
        display_spb(num);
        break;
    }
    break;
    case 9:
        modify_book();
        break;
    case 10:
        delete_book();
        break;
    case 11:
        return;
    default:
        cout << "\a";
    }
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
        cout << endl
             << endl
             << endl
             << "\t"
             << "MAIN MENU";
        cout << endl
             << endl
             << "\t"
             << "01. BOOK ISSUE";
        cout << endl
             << endl
             << "\t"
             << "02. BOOK DEPOSIT";
        cout << endl
             << endl
             << "\t"
             << "03. ADMINISTRATOR MENU";
        cout << endl
             << endl
             << "\t"
             << "04. EXIT";
        cout << endl
             << endl
             << "\t"
             << "PLEASE SELECT YOUR OPTION (1-4) : ";
        ch = getche();
        switch (ch)
        {
        case '1':
            book_issue();
            break;

        case '2':
            book_deposit();
            break;

        case '3':
            admin_menu();
            break;

        case '4':
            exit(0);

        default:
            cout << "\a";
            break;
        }
    } while (ch != 4);
}

//****************************END OF PROJECT*********************************//