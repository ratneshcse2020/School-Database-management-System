#include <fstream.h>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <iomanip.h>


/**********************************************************
//           CODING FOR TEARCHERS INFO---
//**********************************************************/

class MENU
{
	public :
			void MAIN_MENU(void) ;
	private :
			void EDIT_MENU(void) ;

} ;




//**********************************************************
// THIS CLASS CONTROL ALL THE FUNCTIONS RELATED TO EMPLOYEE
//**********************************************************

class EMPLOYEE
{
	public :
			void NEW_EMPLOYEE(void) ;
			void DELETE_RECORD(int) ;
			void ADD_RECORD(int, char[], char[], char[], int, int, int, char[], char, char, char, float, float) ;
			void DELETION(void);
			void LIST(void) ;
	private :


			int  LASTCODE(void) ;
			int  CODEFOUND(int) ;
			int  RECORDNO(int) ;
			int  FOUND_CODE(int) ;
			int  VALID_DATE(int, int, int) ;

			int   code, dd, mm, yy ;
			char  name[26], address[31], phone[10], desig[16] ;
			char  grade, house, convense ;
			float loan, basic ;
} ;


//**********************************************************
//              FUNCTIONS FOR TEACHER INFO---
//**********************************************************



//**********************************************************
// THIS FUNCTION CONTROL ALL THE FUNCTIONS IN THE MAIN MENU
//**********************************************************

void MENU :: MAIN_MENU(void)
{
	char ch ;

	while (1)
	{	int textcolor[15];
		int textbackground[1];
		clrscr() ;
		gotoxy(31,8) ;
		cout <<" DIVINE PUBLIC SCHOOL" ;
		gotoxy(30,11) ;
		cout <<"1:NEW EMPLOYEE" ;
		gotoxy(30,12) ;
		cout <<"2:LIST OF EMPLOYEES" ;
		gotoxy(30,13) ;
		cout <<"3:DELETE"  ;
		gotoxy(30,14) ;
		cout <<"0:QUIT "<<endl ;
		cout <<"ENTER YOUR CHOICE :" ;
		ch = getch() ;
		if (ch == 27 || ch == '0')
			break ;
		else
		if (ch == '1')
		{
			EMPLOYEE E ;
			E.NEW_EMPLOYEE() ;
		}
		else
		if (ch == '2')
		{
			EMPLOYEE E ;
			E.LIST() ;
		}
		else
		if (ch == '3')
		{ int code;
		EMPLOYEE E;
		E.DELETION();
	}

}
}
//**********************************************************
// THIS FUNCTION ADDS THE GIVEN DATA IN THE EMPLOYEE'S FILE
//**********************************************************



void EMPLOYEE :: ADD_RECORD(int ecode, char ename[26], char eaddress[31], char ephone[10], int d, int m, int y, char edesig[16], char egrade, char ehouse, char econv, float eloan, float ebasic)
{
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::app) ;
	code = ecode ;
	strcpy(name,ename) ;
	strcpy(address,eaddress) ;
	strcpy(phone,ephone) ;
	dd = d ;
	mm = m ;
	yy = y ;
	strcpy(desig,edesig) ;
	grade = egrade ;
	house = ehouse ;
	convense = econv ;
	loan = eloan ;
	basic = ebasic ;
	file.write((char *) this, sizeof(EMPLOYEE)) ;
	file.close() ;
}


//**********************************************************
// THIS FUNCTION DELETE THE RECORD IN THE EMPLOYEE FILE
// FOR THE GIVEN EMPLOYEE CODE
//**********************************************************

void EMPLOYEE :: DELETE_RECORD(int ecode)
{
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while (!file.eof())
	{
		file.read((char *) this, sizeof(EMPLOYEE)) ;
		if (file.eof())
			break ;
		if (code != ecode)
			temp.write((char *) this, sizeof(EMPLOYEE)) ;
	}
	file.close() ;
	temp.close() ;
	file.open("EMPLOYEE.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while (!temp.eof())
	{
		temp.read((char *) this, sizeof(EMPLOYEE)) ;
		if ( temp.eof() )
			break ;
		file.write((char *) this, sizeof(EMPLOYEE)) ;
	}
	file.close() ;
	temp.close() ;
}



//**********************************************************
// THIS FUNCTION RETURNS THE LAST EMPLOYEE'S CODE
//**********************************************************

int EMPLOYEE :: LASTCODE(void)
{
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int count=0 ;
	while (file.read((char *) this, sizeof(EMPLOYEE)))
		count = code ;
	file.close() ;
	return count ;
}


//**********************************************************
// THIS FUNCTION RETURNS 0 IF THE GIVEN CODE NOT FOUND
//**********************************************************

int EMPLOYEE :: FOUND_CODE(int ecode)
{
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(EMPLOYEE)))
	{
		if (code == ecode)
		{
			found = 1 ;
			break ;
		}
	}
	file.close() ;
	return found ;
}


//**********************************************************
// THIS FUNCTION RETURNS RECORD NO. OF THE GIVEN CODE
//**********************************************************

int EMPLOYEE :: RECORDNO(int ecode)
{
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int recno=0 ;
	while (file.read((char *) this, sizeof(EMPLOYEE)))
	{
		recno++ ;
		if (code == ecode)
			break ;
	}
	file.close() ;
	return recno ;
}



//**********************************************************
// THIS FUNCTION DISPLAYS THE LIST OF THE EMPLOYEES
//**********************************************************

void EMPLOYEE :: LIST(void)
{
	clrscr() ;
	int row = 6 , found=0, flag=0 ;
	char ch ;
	gotoxy(31,2) ;
	cout <<"LIST OF EMPLOYEES" ;
	gotoxy(30,3) ;
	cout <<"~~~~~~~~~~~~~~~~~~~" ;
	gotoxy(1,4) ;
	cout <<"CODE NAME                     PHONE    DOJ         DESIGNATION    GRADE  SALARY" ;
	gotoxy(1,5) ;
	cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;
	fstream file ;
	file.open("EMPLOYEE.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(EMPLOYEE)))
	{
		flag = 0 ;
		//delay(20) ;
		found = 1 ;
		gotoxy(2,row) ;
		cout <<code ;
		gotoxy(6,row) ;
		cout <<name ;
		gotoxy(31,row) ;
		cout	<<phone ;
		gotoxy(40,row) ;
		cout <<dd <<"/" <<mm <<"/" <<yy ;
		gotoxy(52,row) ;
		cout <<desig ;
		gotoxy(69,row) ;
		cout <<grade ;
		if (grade != 'E')
		{
			gotoxy(74,row) ;
			cout <<basic ;
		}
		else
		{
			gotoxy(76,row) ;
			cout <<"-" ;
		}
		if ( row == 23 )
		{
			flag = 1 ;
			row = 6 ;
			gotoxy(1,25) ;
			cout <<"Press any key to continue or Press <ESC> to exit" ;
			ch = getch() ;
			if (ch == 27)
				break ;
			clrscr() ;
			gotoxy(31,2) ;
			cout <<"LIST OF EMPLOYEES" ;
			gotoxy(30,3) ;
			cout <<"~~~~~~~~~~~~~~~~~~~" ;
			gotoxy(1,4) ;
			cout <<"CODE NAME                     PHONE    DOJ         DESIGNATION    GRADE  SALARY" ;
			gotoxy(1,5) ;
			cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ;
		}
		else
			row++ ;
	}
	if (!found)
	{
		gotoxy(5,10) ;
		cout <<"\7Records not found" ;
	}
	if (!flag)
	{
		gotoxy(1,25) ;
		cout <<"Press any key to continue..." ;
		getche() ;
	}
	file.close () ;
}


//**********************************************************
// THIS FUNCTION GIVE DATA TO ADD IN THE FILE
//**********************************************************

void EMPLOYEE :: NEW_EMPLOYEE(void)
{
	clrscr() ;
	char  ch, egrade, ehouse='N', econv='N' ;
	char  ename[26], eaddress[31], ephone[10], edesig[16], t1[10] ;
	float t2=0.0, eloan=0.0, ebasic=0.0 ;
	int   d, m, y, ecode, valid ;
	gotoxy(72,2) ;
	cout <<"<0>=EXIT" ;
	gotoxy(28,3) ;
	cout <<"ADDITION OF NEW EMPLOYEE" ;
	gotoxy(5,5) ;
	cout <<"Employee Code # " ;
	gotoxy(5,6) ;
	cout <<"~~~~~~~~~~~~~" ;
	gotoxy(5,7) ;
	cout <<"Name         : " ;
	gotoxy(5,8) ;
	cout <<"Address      : " ;
	gotoxy(5,9) ;
	cout <<"Phone no.    : " ;
	gotoxy(5,11) ;
	cout <<"JOINING DATE" ;
	gotoxy(5,12) ;
	cout <<"~~~~~~~~~~~~" ;
	gotoxy(5,13) ;
	cout <<"Day   : " ;
	gotoxy(5,14) ;
	cout <<"Month : " ;
	gotoxy(5,15) ;
	cout <<"Year  : " ;
	gotoxy(5,17) ;
	cout <<"Designation  : " ;
	gotoxy(5,18) ;
	cout <<"Grade        : " ;
	gotoxy(5,21) ;
	cout <<"Loan           : " ;

	ecode = LASTCODE() + 1 ;
	if (ecode == 1)
	{
		ADD_RECORD(ecode, "null", "null", "null", 0, 0, 0, "null", 'n', 'n', 'n', 0.0, 0.0) ;
		DELETE_RECORD(ecode) ;
	}
	gotoxy(21,5) ;
	cout <<ecode ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"Enter the name of the Employee" ;
		gotoxy(20,7) ; clreol() ;
		gets(ename) ;
		strupr(ename) ;
		if (ename[0] == '0')
			return ;
		if (strlen(ename) < 1 || strlen(ename) > 25)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter correctly (Range: 1..25)" ;
			getch() ;
		}
	} while (!valid) ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"Enter Address of the Employee" ;
		gotoxy(20,8) ; clreol() ;
		gets(eaddress) ;
		strupr(eaddress) ;
		if (eaddress[0] == '0')
			return ;
		if (strlen(eaddress) < 1 || strlen(eaddress) > 30)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter correctly (Range: 1..30)" ;
			getch() ;
		}
	} while (!valid) ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"Enter Phone no. of the Employee or Press <ENTER> for none" ;
		gotoxy(20,9) ; clreol() ;
		gets(ephone) ;
		if (ephone[0] == '0')
			return ;
		if ((strlen(ephone) < 7 && strlen(ephone) > 0) || (strlen(ephone) > 9))
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter correctly" ;
			getch() ;
		}
	} while (!valid) ;
	if (strlen(ephone) == 0)
		strcpy(ephone,"-") ;
	char tday[3], tmonth[3], tyear[5] ;
	int td ;
	do
	{
		valid = 1 ;
		do
		{
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER DAY OF JOINING" ;
			gotoxy(13,13) ; clreol() ;
			gets(tday) ;
			td = atoi(tday) ;
			d = td ;
			if (tday[0] == '0')
				return ;
		} while (d == 0) ;
		do
		{
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER MONTH OF JOINING" ;
			gotoxy(13,14) ; clreol() ;
			gets(tmonth) ;
			td = atoi(tmonth) ;
			m = td ;
			if (tmonth[0] == '0')
				return ;
		} while (m == 0) ;
		do
		{
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER YEAR OF JOINING" ;
			gotoxy(13,15) ; clreol() ;
			gets(tyear) ;
			td = atoi(tyear) ;
			y = td ;
			if (tyear[0] == '0')
				return ;
		} while (y == 0) ;
		if (d>31 || d<1)
			valid = 0 ;
		else
		if (((y%4)!=0 && m==2 && d>28) || ((y%4)==0 && m==2 && d>29))
			valid = 0 ;
		else
		if ((m==4 || m==6 || m==9 || m==11) && d>30)
			valid = 0 ;
		else
		if (y<1990 || y>2020)
			valid = 0 ;
		if (!valid)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter correctly" ;
			getch() ;
			gotoxy(13,14) ; clreol() ;
			gotoxy(13,15) ; clreol() ;
		}
	} while (!valid) ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"Enter Designation of the Employee" ;
		gotoxy(20,17) ; clreol() ;
		gets(edesig) ;
		strupr(edesig) ;
		if (edesig[0] == '0')
			return ;
		if (strlen(edesig) < 1 || strlen(edesig) > 15)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter correctly (Range: 1..15)" ;
			getch() ;
		}
	} while (!valid) ;
	do
	{
		gotoxy(5,25) ; clreol() ;
		cout <<"Enter Grade of the Employee (A,B,C,D,E)" ;
		gotoxy(20,18) ; clreol() ;
		egrade = getche() ;
		egrade = toupper(egrade) ;
		if (egrade == '0')
			return ;
	} while (egrade < 'A' || egrade > 'E') ;
	if (egrade != 'E')
	{
		gotoxy(5,19) ;
		cout <<"House (y/n)    : " ;
		gotoxy(5,20) ;
		cout <<"Convense (y/n) : " ;
		gotoxy(5,22) ;
		cout <<"Basic Salary   : " ;
		do
		{
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER IF HOUSE ALLOWANCE IS ALLOTED TO EMPLOYEE OR NOT" ;
			gotoxy(22,19) ; clreol() ;
			ehouse = getche() ;
			ehouse = toupper(ehouse) ;
			if (ehouse == '0')
				return ;
		} while (ehouse != 'Y' && ehouse != 'N') ;
		do
		{
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER IF CONVENCE ALLOWANCE IS ALLOTED TO EMPLOYEE OR NOT" ;
			gotoxy(22,20) ; clreol() ;
			econv = getche() ;
			econv = toupper(econv) ;
			if (econv == '0')
				return ;
		} while (econv != 'Y' && econv != 'N') ;
	}
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"ENTER LOAN AMOUNT IF ISSUED" ;
		gotoxy(22,21) ; clreol() ;
		gets(t1) ;
		t2 = atof(t1) ;
		eloan = t2 ;
		if (eloan > 50000)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7SHOULD NOT GREATER THAN 50000" ;
			getch() ;
		}
	} while (!valid) ;
	if (egrade != 'E')
	{
		do
		{
			valid = 1 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"ENTER BASIC SALARY OF THE EMPLOYEE" ;
			gotoxy(22,22) ; clreol() ;
			gets(t1) ;
			t2 = atof(t1) ;
			ebasic = t2 ;
			if (t1[0] == '0')
				return ;
			if (ebasic > 50000)
			{
				valid = 0 ;
				gotoxy(5,25) ; clreol() ;
				cout <<"\7SHOULD NOT GREATER THAN 50000" ;
				getch() ;
			}
		} while (!valid) ;
	}
	gotoxy(5,25) ; clreol() ;
	do
	{
		gotoxy(5,24) ; clreol() ;
		cout <<"Do you want to save (y/n) " ;
		ch = getche() ;
		ch = toupper(ch) ;
		if (ch == '0')
			return ;
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N')
		return ;
	ADD_RECORD(ecode, ename, eaddress, ephone, d, m, y, edesig, egrade, ehouse, econv, eloan, ebasic) ;
}



//**********************************************************
// THIS FUNCTION GIVE CODE NO. FOR THE DELETION OF THE
// EMPLOYEE RECORD
//**********************************************************

void EMPLOYEE :: DELETION(void)
{
	clrscr() ;
	char t1[10], ch ;
	int t2, ecode ;
	gotoxy(72,2) ;
	cout <<"<0>=EXIT" ;
	gotoxy(5,5) ;
	cout <<"Enter code of the Employee  " ;
	gets(t1) ;
	t2 = atoi(t1) ;
	ecode = t2 ;
	if (ecode == 0)
		return ;
	clrscr() ;
	if (!FOUND_CODE(ecode))
	{
		gotoxy(5,5) ;
		cout <<"\7Record not found" ;
		getch() ;
		return ;
	}
	gotoxy(72,2) ;
	cout <<"<0>=EXIT" ;
	gotoxy(24,3) ;
	cout <<"DELETION OF THE EMPLOYEE RECORD" ;
	do
	{
		gotoxy(5,24) ;
		cout <<"Do you want to delete this record (y/n) " ;
		ch = getche() ;
		ch = toupper(ch) ;
		if (ch == '0')
			return ;
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N')
		return ;
	DELETE_RECORD(ecode) ;
	gotoxy(5,23) ;
	cout <<"\7Record Deleted" ;
	gotoxy(5,25) ;
	cout <<"Press any key to continue..." ;
	getch() ;
}


//**********************************************************
// THIS FUNCTION RETURN 0 IF THE GIVEN DATE IS INVALID
//**********************************************************

int EMPLOYEE :: VALID_DATE(int d1, int m1, int y1)
{
	int valid=1 ;
	if (d1>31 || d1<1)
		valid = 0 ;
	else
	if (((y1%4)!=0 && m1==2 && d1>28) || ((y1%4)==0 && m1==2 && d1>29))
		valid = 0 ;
	else
	if ((m1==4 || m1==6 || m1==9 || m1==11) && d1>30)
		valid = 0 ;
	return valid ;
}







//***************************************************************
//    	CODE FOR THE LIBRARY---
//****************************************************************




class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\nEnter The book no.";
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book ";
		gets(bname);
		cout<<"\n\nEnter The Author's Name ";
		gets(aname);
		cout<<"\n\n\nBook Created..";
	}

	void show_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nBook Name : ";
		puts(bname);
		cout<<"Author Name : ";
		puts(aname);
	}

	void modify_book()
	{
		cout<<"\nBook no. : "<<bno;
		cout<<"\nModify Book Name : ";
		gets(bname);
		cout<<"\nModify Author's Name of Book : ";
		gets(aname);
	}

	char* retbno()
	{
		return bno;
	}

	void report()
	{cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};         //class ends here


//***************************************************************
//    	FUNCTIONS FOR LIBRARY----
//****************************************************************



class student
{
	char admno[6];
	char name[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		clrscr();
		cout<<"\nNEW STUDENT ENTRY...\n";
		cout<<"\nEnter The admission no. ";
		cin>>admno;
		cout<<"\n\nEnter The Name of The Student ";
		gets(name);
		token=0;
		stbno[0]='/0';
		cout<<"\n\nStudent Record Created..";
	}

	void show_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nStudent Name : ";
		puts(name);
	       //	cout<<"\nNo of Book issued : "<<token;
		//if(token==1)
		  //	cout<<"\nBook No "<<stbno;
	}

	void modify_student()
	{
		cout<<"\nAdmission no. : "<<admno;
		cout<<"\nModify Student Name : ";
		gets(name);
	}

	char* retadmno()
	{
		return admno;
	}

	char* retstbno()
	{
		return stbno;
	}

	int rettoken()
	{
		return token;
	}

	void addtoken()
	{token=1;}

	void resettoken()
	{token=0;}

	void getstbno(char t[])
	{
		strcpy(stbno,t);
	}

	void report()
	{cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here


//***************************************************************
//    	function to write in file
//****************************************************************

void write_book()
{

fstream fp,fp1;
book bk;
student st;
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
fstream fp,fp1;
book bk;
student st;
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}





//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
fstream fp,fp1;
book bk;
student st;
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{

fstream fp,fp1;
book bk;
student st;

	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if((strcmpi(st.retadmno(),n)==0))
		{
			st.show_student();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nStudent does not exist";
	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{


fstream fp,fp1;
book bk;
student st;
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(strcmpi(bk.retbno(),n)==0)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			int pos=-1*sizeof(bk);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&bk,sizeof(book));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}


void modify_student()
{

fstream fp,fp1;
book bk;
student st;

	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),n)==0)
		{
			st.show_student();
			cout<<"\nEnter The New Details of student"<<endl;
			st.modify_student();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_student()
{
fstream fp,fp1;
book bk;
student st;
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(strcmpi(st.retadmno(),n)!=0)
			fp2.write((char*)&st,sizeof(student));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


void delete_book()
{

fstream fp,fp1;
book bk;
student st;
	char n[6];
	clrscr();
	cout<<"\n\n\n\tDELETE BOOK ...";
	cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(strcmpi(bk.retbno(),n)!=0)
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}



//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
fstream fp,fp1;
book bk;
student st;
	clrscr();
	fp.open("student.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}

	fp.close();
	getch();
}


//***************************************************************
//    	function to display Books list
//****************************************************************

void display_allb()
{
fstream fp,fp1;
book bk;
student st;
	clrscr();
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tBook LIST\n\n";
	cout<<"=========================================================================\n";
	cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
	cout<<"=========================================================================\n";

	while(fp.read((char*)&bk,sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}



//***************************************************************
//    	function to issue book
//****************************************************************

void book_issue()
{
fstream fp,fp1;
book bk;
student st;
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr();
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(strcmpi(st.retadmno(),sn)==0)
		{
			found=1;
			if(st.rettoken()==0)
			{
				cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
					if(strcmpi(bk.retbno(),bn)==0)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
						int pos=-1*sizeof(st);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current datein backside of book and submit within 15 days fine Rs. 1 for after 15 days period";
					}
				}
				if(flag==0)
					cout<<"Book no does not exist";
			}
			else
				cout<<"You have not returned the last book ";

		}
	}
	if(found==0)
		cout<<"Student record not exist...";
	getch();
	fp.close();
	fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void book_deposit()
{

fstream fp,fp1;
book bk;
student st;
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student’s admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(strcmpi(st.retadmno(),sn)==0)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(strcmpi(bk.retbno(),st.retstbno())==0)
			{
				bk.show_book();
				flag=1;
				cout<<"\n\nBook deposited in no. of days";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\nFine has to deposited Rs. "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist...";
	getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	clrscr();
	gotoxy(35,11);
	cout<<"LIBRARY";
	gotoxy(35,14);
	cout<<"MANAGEMENT";
	gotoxy(35,17);
	cout<<"SYSTEM";
	getch();
}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_student();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The Admission No. ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_student();break;
		case 5: delete_student();break;
		case 6: clrscr();
			write_book();break;
		case 7: display_allb();break;
		case 8: {
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The book No. ";
			cin>>num;
			display_spb(num);
			break;
			}
		case 9: modify_book();break;
		case 10: delete_book();break;
		case 11: return;
		default:cout<<"\a";
	}
	admin_menu();
}



//***************************************************************
//                   CODING FOR STUDENT INFO---
//****************************************************************

class student1
{
	int rollno;
	char name[50];
	int p_marks, c_marks, m_marks, e_marks, cs_marks;
	float per;
	char grade;
	void calculate();	//function to calculate grade
public:
	void getdata1();	//function to accept data from user
	void showdata1();	//function to show data on screen
	void show_tabular();
	int retrollno();
}; //class ends here





//***************************************************************
//                   FUNCTIONS FOR STUDENT INFO---
//****************************************************************


void student1::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=80)
		grade='A';
	else if(per>=60)
		grade='B';
	else if(per>=40)
		grade='C';
	else
		grade='D';
}

void student1::getdata1()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	gets(name);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>p_marks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs_marks;
	calculate();
}

void student1::showdata1()
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Chemistry : "<<c_marks;
	cout<<"\nMarks in Maths : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Computer Science :"<<cs_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}

void student1::show_tabular()
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)<<e_marks<<setw(4)<<cs_marks<<setw(6)<<per<<setw(6)<<" "<<grade<<endl;
}

int  student1::retrollno()
{
	return rollno;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_student1()
{
	student1 st;
	ofstream outFile;
	outFile.open("student1.dat",ios::binary|ios::app);
	st.getdata1();
	outFile.write((char *) &st, sizeof(student1));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	getch();
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
	student1 st;
	ifstream inFile;
	inFile.open("student1.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read((char *) &st, sizeof(student1)))
	{
		st.showdata1();
		cout<<"\n\n====================================\n";
	}
	inFile.close();

	getch();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
	student1 st;
	ifstream inFile;
	inFile.open("student1.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	int flag=0;
	while(inFile.read((char *) &st, sizeof(student1)))
	{
		if(st.retrollno()==n)
		{
			 st.showdata1();
			 flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\nrecord not exist";

	getch();
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_student1(int n)
{
	int found=0;
	student1 st;
	fstream File;
	File.open("student1.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}

	while(File.read((char *) &st, sizeof(student1)) && found==0)
	{
		if(st.retrollno()==n)
		{
			st.showdata1();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata1();
		    int pos=(-1)*sizeof(st);
		    File.seekp(pos,ios::cur);
		    File.write((char *) &st, sizeof(student1));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_student(int n)
{
	student1 st;
	ifstream inFile;
	inFile.open("student1.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		getch();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &st, sizeof(student1)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char *) &st, sizeof(student1));
		}
	}
	outFile.close();
	inFile.close();
	remove("student1.dat");
	rename("Temp.dat","student1.dat");
	cout<<"\n\n\tRecord Deleted ..";

	getch();
}

//***************************************************************
//    	function to display all students grade report
//****************************************************************

void class_result()
{
	student1 st;
	ifstream inFile;
	inFile.open("student1.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";

		getch();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read((char *) &st, sizeof(student1)))
	{
		st.show_tabular();
	}

	getch();
	inFile.close();
}

//***************************************************************
//    	function to display result menu
//****************************************************************

void result()
{
	char ch;
	int rno;
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro1()
{
	cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	getch();
}

//***************************************************************
//    	ENTRY / EDIT MENU FUNCTION
//****************************************************************

void entry_menu()
{
	char ch;
	int num;
	clrscr();
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	clrscr();
	switch(ch)
	{
	case '1':	write_student1(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				modify_student1(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}


void main()
{
front:
clrscr();
int a;
cout<<"WELCOME TO THE DIVINE PUBLIC SCHOOL"<<endl;
cout<<"1:-TEACHER'S INFORMATION"<<endl;
cout<<"2:-STUDENT'S INFORMATION"<<endl;
cout<<"3:-LIBRARY INFORMATION"<<endl;
cout<<"4:-EXIT"<<endl;
cout<<"ENTER YOUR CHOICE(1/2/3/4)";
cin>>a;
switch(a)
{
case 1:
{   MENU menu ;
	menu.MAIN_MENU() ;
   goto front;
}
case 2:{
char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2); // program outputs decimal number to two decimal places
	clrscr();
	intro1();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. RESULT MENU";
		cout<<"\n\n\t2. ENTRY/EDIT MENU";
		cout<<"\n\n\t3. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':cout<<"\n\nTHANKYOU FOR USING THIS SOFTWARE!!!";
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
goto front;
}
case 3:
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
		cout<<"\n\n\t03. ADMINISTRATOR MENU";
		cout<<"\n\n\t04. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();
				 book_issue();
				 break;
			case '2':book_deposit();
				 break;
			case '3':admin_menu();
				 break;
			case '4':cout<<"Thank you for using Library Management";
			default :cout<<"\a";
		}
	}while(ch!='4');
goto front;
 }


case 4:
{
cout<<"THANKYOU FOR USING THIS SOFTWARE"<<endl;
cout<<"THE PROGRAME IS EXISTING";
for(int i=0;i<4;i++)
delay(500);
cout<<i;
exit(0);
}
}
}

