#include<conio.h>
#include<string.h>
#include<fstream>
#include<iostream>
//#include <bits/stdc++.h>
using namespace std;

class report_card  //base class containing data members
{
	public:

	int rno;
	float M,C,P;


};

class student :protected report_card//Class used in project
{
    char name[50];
public:
    void create_card(int rn)
    {   
        rno=rn;
        cout<<"Enter the name of student : ";
        cin.ignore();
        cin.getline(name,50,'\n');
        cout<<"Enter the marks of student in mathematics : ";
        cin>>M;
        cout<<"Enter the marks of student in chemistry : ";
        cin>>C;
        cout<<"Enter the marks of student in physics : ";
        cin>>P;
        cout<<"\n\n\t\tDETAILS REGISTERED!";
    }
    int retrno()//return roll no
    {
        return rno;
    }
    string retname()//return student name
    {
    	return name;
	}
	void  showall_card()
    {
        cout<<"Rno\t\t\tName\n";
        cout<<rno<<"\t\t"<<name;
        char grade;
        if((M+P+C)/3>90)
            grade='S';
        else if ((M+P+C)/3>80)
            grade='A';
        else if ((M+P+C)/3>70)
            grade='B';
        else if ((M+P+C)/3>60)
            grade='C';
        else if ((M+P+C)/3>50)
            grade='D';
        else if ((M+P+C)/3>40)
            grade='E';
        else
            grade='F';
        cout<<"\n\nM\tC\tP\tTotal\tPercentage\tGrade\n";
        cout<<M<<"\t"<<C<<"\t"<<P<<"\t"<<(M+C+P)<<"\t"<<(M+P+C)/3<<"\t\t"<<grade;

    }
    void show_card();

};

void student::  show_card()//non-inline function
    {   
        char grade;
        if((M+P+C)/3>90)
            grade='S';
        else if ((M+P+C)/3>80)
            grade='A';
        else if ((M+P+C)/3>70)
            grade='B';
        else if ((M+P+C)/3>60)
            grade='C';
        else if ((M+P+C)/3>50)
            grade='D';
        else if ((M+P+C)/3>40)
            grade='E';
        else
            grade='F';

        cout<<"Rno\t\t\tName\n";
        cout<<rno<<"\t\t"<<name;
        cout<<"\n\nMaths\t\tChemistry\t\tPhysics";
        cout<<"\n"<<M<<"\t\t"<<C<<"\t\t\t"<<P;
        cout<<"\n\nTotal: "<<(M+C+P)<<"/300";
        cout<<"\nPercentage: "<<(M+C+P)/3;
        cout<<"\nGrade: "<<grade;
        cout<<"\n-------------------------------------------------\n";
    }
//Global stream for object
fstream fp;
student pr;
void write_card()
{   
    int rn;
    cout<<"\nEnter the roll no. of student: ";
    cin>>rn;
    fp.open("card.dat", ios:: in );
    bool exist=false;
    while (fp.read((char * ) & pr, sizeof(student)))
    {
        if(pr.retrno()==rn)
        {
            exist=true;
            break;
        }

    }
    fp.close();
    if(exist)
    {
        cout<<"Record Already exist";
        return;
    }
    
    fp.open("Card.dat",ios::out|ios::app);
    pr.create_card(rn);
    fp.write((char *)&pr,sizeof(student));
    fp.close();
}

void display_card()
{
    int no,found=0;
    cout<<"\n\nPlease enter the roll no of student whose report card you want to see: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    while(fp.read((char *)& pr,sizeof(student))&&found==0)
    {
        if(pr.retrno()==no)
        {
            pr.show_card();
            found=1;
        }
    }
    if(found==0)
        cout<<"\n\nRecord not found!";
        fp.close();
        getch();
}

void display_all()// function to read all records from file
{
    system("cls");
    bool no_rec=true;
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("card.dat", ios:: in );
    while (fp.read((char * ) & pr, sizeof(student)))
    {
        pr.showall_card();
        no_rec=false;
        cout << "\n=====================================================\n\n";

    }
    fp.close();
    if(no_rec)
    cout<<"\t\tNO RECORDS AVAILABLE";
    getch();

}
void modify_card()
{
    int no,found=0;
    cout<<"Enter the roll of student whose report card you want to modify: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    while(fp.read((char *)&pr,sizeof(student))&&found==0)
    {
        if((pr.retrno())==no)
        {
            pr.show_card();
            cout<<"\nPlease enter the new details of Report card"<<endl;
            pr.create_card(no);
            int pos=-1*(int)sizeof(pr);
            fp.seekp(pos,ios::cur);
            fp.write((char *)&pr,sizeof(student));
            cout<<"\n\nRECORD UPDATED!!";
            found=1;
        }
    }
    fp.close();
    if(found==0)
        cout<<"Record not found!!";
    getch();
}
void delete_card()
{
    int no;
    bool flag=false;
    cout<<"Enter the rollno of student whose record you want to delete: ";
    cin>>no;
    fp.open("Card.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp2.seekg(0,ios::beg);
    while(fp.read((char *)&pr,sizeof(student)))
    {
        if(pr.retrno()!=no)
        {
            fp2.write((char *)&pr,sizeof(student));
        }

        else flag=true;
    }
    fp2.close();
    fp.close();
    remove("Card.dat");
    rename("Temp.dat","Card.dat");
    if(flag)
    cout<<"\n\n\tRecord deleted!";
    else cout<<"\n\n\tRecord not found!";
    getch();
}
void admin_menu()
{
    system("cls");
    char ch2,ch3;
    char pass[50];
    char logpass[]="12345";
    cout<<"Please Enter password for access:\n\t";
    int p=0;
    do
    {
        pass[p]=getch();
        if(pass[p]!='\r')
            cout<<"*";
        p++;
    }while(pass[p-1]!='\r');
    pass[p-1]='\0';
    if(strcmp(logpass,pass)==0)
        {cout<<"\n\nAccess Granted!";
        getch();}
    else
    {
        cout<<"Entered Wrong password!\nAccess Denied!!";
        getch();
        return;
    }
    system("cls");
    bool quit=false;
    do
    {
        quit=false;
        cout<<"\n\n\t\t    WELCOME ADMINISTRATOR";
        cout<<"\n\n\t\tREPORT CARD MANAGEMENT PORTAL\n";
        cout<<"\n1.New entry";
        cout<<"\n2.Display";
        cout<<"\n3.Modify";
        cout<<"\n4.display all";
        cout<<"\n5.Delete";
        cout<<"\n6.Back to main menu";
        cout<<"\n\n\tPlease enter your choice: ";
        ch2=getche();
        getch();
        switch(ch2)
        {
        case '1':
            system("cls");
            write_card();
            getch();
            break;
        case '2':
            system("cls");
            display_card();
            break;
        case '3':
            system("cls");
            modify_card();
            break;
        case '4':
            system("cls");
            display_all();
            break;
        case '5':
            system("cls");
            delete_card();
            break;
        case '6':
            quit=true;
            break;
        default:
            cout<<"invalid choice!!";
            break;
        }

        if(quit)
        return;
        cout<<"\nDo you wish to continue?(y/n);";
        ch3=getche();
        system("cls");

    }while(ch3!='n');
    if(ch3=='n')
    cout<<"\n\t\t\t\tEXITING...\n\t\t\t\tPRESS ENTER!";

    getch();
}
void intro() // INTRODUCTION FUNCTION
{
     system("cls");

    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t  REPORT CARD SYSTEM";
    cout<<"\n\t\t\t\t\t  ===================";
    cout << "\n\n\t\t\t\t\t\tMADE BY\n\n\t\t\t\t\t Naveen Kumar Jaiswal";
    cout<<"\n\t\t\t\t\t =====================";
    getch();

}
int main()
{
    char ch;
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01 Administrator";
        cout<<"\n\n\t02 Exit";
        cout<<"\n\n\tPlease enter your choice:";
        ch=getche();
        char che;
        switch (ch)
        {
        case '1':
            cout<<"\n\n\n\tWelcome Administrator!";
            getch();
            admin_menu();
            break;
        case '2':
            cout<<"\n\tPRESS ENTER EXIT";
            che = getch();
            if(che=='\n')
            exit(0);
            break;
        default:
            cout<<"\n\n\n\tInvalid choice!";
            getch();

        }
    }while(ch!='2');
}