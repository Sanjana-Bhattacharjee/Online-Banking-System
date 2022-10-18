#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>

class bank{
	int cid;
	char name[30],address[50],bdate[8];
	float cb,wd,dep;
     public:
	int pin1;
	void cmenu(int k);
	void balance(int k);
	void withdraw(int k);
	void deposit(int k);
	void chpin(int k);

	void getdata()
	{       cout<<"----------------------------------------------"<<endl
		    <<"             CUSTOMER DETAIL ENTRY            "<<endl
		    <<"----------------------------------------------"<<endl
		    <<"Enter Customer ID:                ";
		cin>>cid;
		cout<<"Enter Customer Name:              ";
		gets(name);
		cout<<"Enter Customer 4-digit PIN:       ";
		cin>>pin1;
		cout<<"Enter date of birth (dd/mm/yy):   ";
		gets(bdate);
		cout<<"Enter address:			  ";
		gets(address);
		cout<<"Enter amount to be deposited(Rs): ";
		cin>>cb;
	}
	void display()
	{	cout<<cid<<'\t'<<name<<'\t'<<pin1<<'\t'<<bdate<<'\t'
		    <<address<<'\t'<<cb<<endl;
	}
	int getcid(){   return cid;   }
	int getpin(){   return pin1;  }
	float getbal(){ return cb;    }
	char* getname(){ return name;}
};

void bmenu();
void clogin();

void wmenu()
{       int ch;
	do{
		clrscr();
		cout<<"-------------------------------------------------------------------------------";
		gotoxy(25,2);
		cout<<"WELCOME TO BANK OF THE PEOPLE";
		gotoxy(35,3);
			cout<<"MAIN MENU"<<endl
		    <<"------------------------------------------------------------------------------- ";
		gotoxy(30,6);
		cout<<"1) Login as banker"<<endl;
		gotoxy(30,7);
		cout<<"2) Login as customer"<<endl;
		gotoxy(30,8);
		cout<<"3) Exit"<<endl<<endl;
		gotoxy(30,10);
		cin>>ch;
		switch(ch)
		{	case 1 : bmenu();
				 break;
			case 2 : clogin();
				 break;
			case 3 : exit(0);
			default: cout<<"Wrong choice! Try again";
				 getch();
				 break;
		}
	}while(ch!=3);
}

void bmenu()
{	int ch,cid;
	bank b;
	do{
		clrscr();
		cout<<"-------------------------------------------------------------------------------"<<endl;
		gotoxy(25,2);
		cout<<"WELCOME TO BANK OF THE PEOPLE"<<endl;
		gotoxy(33,3);
		cout<<"Banker's Menu"<<endl
		    <<"-------------------------------------------------------------------------------"<<endl<<endl
		    <<"1) Create new account"<<endl
		    <<"2) Delete existing account"<<endl
		    <<"3) View customer details"<<endl
		    <<"4) Back to main menu"<<endl
		    <<"5) Exit"<<endl<<endl;
		cin>>ch;
		switch(ch)
		{	case 1 : ofstream fout("bank.dat",ios::binary|ios::app);
				 clrscr();
				 b.getdata();
				 fout.write((char*)&b,sizeof(b));
				 fout.close();
				 break;
			case 2 : clrscr();
				 ifstream fin("bank.dat",ios::binary);
				 ofstream foutt("temp.dat",ios::binary);
				 int rno,flag=0;	char confirm='n';
				 cout<<"Enter customer id of customer whose record is to be deleted: ";
				 cin>>cid;
				 while(!fin.eof())
				 {	fin.read((char*)&b,sizeof(b));
					if(fin.eof())
						break;
					if(b.getcid()==cid)
					{	flag=1;
						cout<<"Are you sure you want to delete this?(y/n) ";
						cin>>confirm;
						if(confirm=='n')
							foutt.write((char*)&b,sizeof(b));
					}
					else
						foutt.write((char*)&b,sizeof(b));
				 }
				 if(flag==0)
					cout<<"\n\tRecord not found!!";
				 fin.close();
				 foutt.close();
				 remove("bank.dat");
				 rename("temp.dat","bank.dat");
				 if(flag==1)
					cout<<"\n\tRecord Deleted...\n\tPress any key to Continue.";
				 getch();
				 break;
			case 3 : clrscr();
				 ifstream finn("bank.dat",ios::binary);
				 finn.seekg(0);
				 cout<<"CID\tName\t\tPIN \tDOB     \tAddress"
				     <<"\t\tCurrent Balance"<<endl
				     <<"-------------------------------------------------------------------------------"<<endl;
				 while(!finn.eof())
				 {(finn.read((char*)&b,sizeof(b)));
				 if(finn.eof())break;
					b.display();
				 }
				 getch();
				 finn.close();
				 break;
			case 4 : clrscr();
				 wmenu();
				 break;
			case 5 : exit(0);
			default: cout<<"Wrong choice! Try again";
				 getch();
				 break;
		}
	}while(ch!=5);
}

void clogin()
{	int CID,pin;
	bank b;
	ifstream fin("bank.dat",ios::binary);
	clrscr();
	cout<<"-------------------------------------------------------------------------------"<<endl;
	gotoxy(25,2);
	cout<<"WELCOME TO BANK OF THE PEOPLE"<<endl;
	gotoxy(33,3);
	cout<<"Customer Login"<<endl
	    <<"------------------------------------------------------------------------------- ";
	gotoxy(24,5);
	cout<<"Enter your Customer ID: ";
	cin>>CID;
	gotoxy(24,6);
	cout<<"Enter your 4 digit PIN: ";
	cin>>pin;
	fin.seekg(0);

	while(!fin.eof())
	{	fin.read((char*)&b,sizeof(b));
		if(fin.eof())
			break;
		if(b.getcid()==CID)
		{	if(b.getpin()==pin)
			{   	clrscr();
				b.cmenu(CID);
				break;
			}
			else
			{	cout<<"Invalid PIN !"<<endl<<endl
				    <<"Your Account has been Temporarily Suspended"<<endl
				    <<"Please contact your Home Branch";
				getch();
				exit(0);
			}
		}
	}
	fin.close();
}

void bank::cmenu(int cid)
{       int choice;
	char ch;
	bank b;
	ifstream fin("bank.dat",ios::binary);
	while(!fin.eof())
	{       fin.read((char*)&b,sizeof(b));
		if(b.getcid()==cid)
		do{
			clrscr();
			cout<<"-------------------------------------------------------------------------------"<<endl;
			gotoxy(25,2);
			cout<<"WELCOME TO BANK OF THE PEOPLE"<<endl;
			gotoxy(32,3);
			cout<<"Customer's Menu"<<endl
			    <<"-------------------------------------------------------------------------------"<<endl<<endl
			    <<"Welcome "<<b.getname()<<endl<<endl
			    <<"1. Current Balance"<<endl
			    <<"2. Withdraw"<<endl
			    <<"3. Deposit"<<endl
			    <<"4. Change PIN"<<endl

			    <<"5. Log out"<<endl
			    <<"6. Exit"<<endl<<endl;
			cout<<"Please select a banking activity: ";
			cin>>choice;
			switch(choice)
			{	case 1 : b.balance(cid);
					 break;
				case 2 : b.withdraw(cid);
					 break;
				case 3 : b.deposit(cid);
					 break;
				case 4 : b.chpin(cid);
					 break;
				case 5 : clrscr();
					 gotoxy(30,10);
					 cout<<"You have logged out!";
					 gotoxy(27,12);
					 cout<<"Press any key to continue...";
					 getch();
					 wmenu();
				case 6 : clrscr();
					 gotoxy(25,12);
					 cout<<"Thank you for banking with us!";
					 getch();
					 exit(0);
				default: cout<<"Wrong choice try again!";
					 ch='y';
					 getch();
					 break;
			}
			if(ch==1||ch==2||ch==3||ch==4)
			{	cout<<"\n\nWould you like to make another transaction? (y/n) ";
				cin>>ch;
			}
			if(ch=='n'||ch=='N')
			{       clrscr();
				gotoxy(25,12);
				cout<<"Thank you for banking with us!";
				getch();
				exit(0);
			}
		}while(ch=='y'||ch=='Y');
	}
	fin.close();
}

void bank::balance(int cid)
{	clrscr();
	bank b;
	ifstream fin("bank.dat",ios::binary);
	while(!fin.eof())
	{       fin.read((char*)&b,sizeof(b));
		if(b.getcid()==cid)
		{	cout<<"\n\nYou have Rs. "<<b.cb<<" in your account";
			break;
		}
	}
	fin.close();
}

void bank::withdraw(int cid)
{	int flag=0;
	long amt;
	do{
		clrscr();
		gotoxy(13,7);
		cout<<"Enter the amount you want to withdraw (multiple of 100)"
		<<"\n\t\t\t\tRs. ";
		cin>>amt;
		if(amt%100==0)
			flag=1;
		else
		    {cout<<"       Amount entered is not in multiple of 100. Please Try Again";
		     getch();
		    }
	   }while(flag==0);
	bank b;
	long pos=0;
	fstream finout("bank.dat",ios::in|ios::out|ios::binary);
	while(!finout.eof())
	{	pos=finout.tellg();
		finout.read((char*)&b,sizeof(b));
		if(b.getcid()==cid)
		{	clrscr();
			if(amt>b.cb)
			{	gotoxy(2,7);
				cout<<"Sorry. Your account does not have sufficient balance"
				    <<" to make this withdrawal";
			}
			else
			{       gotoxy(29,7);
				b.cb-=amt;
				cout<<"Withdrawal successful!"<<endl<<endl
				    <<"Your current balance is now Rs."<<b.cb<<endl;
				finout.seekg(pos);
				finout.write((char*)&b,sizeof(b));
			}
			break;
		}
	}
	finout.close();
}

void bank::deposit(int cid)
{	clrscr();
	int amt;
	cout<<"\n\nPlease insert the exact amount of deposit "
	    <<"funds in the slot below."<<endl;
	cout<<"\n\nEnter the amount to be deposited: ";
	cin>>amt;

	bank b;
	long pos=0;
	fstream finout("bank.dat",ios::in|ios::out|ios::binary);
	while(!finout.eof())
	{	pos=finout.tellg();
		finout.read((char*)&b,sizeof(b));
		if(b.getcid()==cid)
		{	clrscr();
			b.cb+=amt;
			clrscr();
			gotoxy(30,7);
			cout<<"Deposit successful!"<<endl<<endl
			    <<"Your current balance is now Rs."<<b.cb<<endl;
			finout.seekg(pos);
			finout.write((char*)&b,sizeof(b));
			break;
		}
	}
	finout.close();

}

void bank::chpin(int cid)
{	int pina,pinb;
	long pos=0;
	bank b;
	fstream finout("bank.dat",ios::in|ios::out|ios::binary);
	do{     clrscr();
		cout<<"\n\nEnter your new 4 digit PIN:   \t";
		cin>>pina;
		cout<<"Re-enter your new 4 digit PIN:\t";
		cin>>pinb;
		if(pina==pinb)
		{	while(!finout.eof())
			{	pos=finout.tellg();
				finout.read((char*)&b,sizeof(b));
				if(b.pin1==pina)
				{       cout<<"\n\nEnter a different PIN";
					getch();
					pos=0;
					break;
				}
				else
				{    if(b.getcid()==cid)
				     {	clrscr();
					b.pin1=pina;
					gotoxy(29,7);
					cout<<"PIN change successful!";
					finout.seekg(pos);
					finout.write((char*)&b,sizeof(b));
					finout.close();
					pos=1;
					break;
				     }

				}
			}
		}
		else
		{	cout<<"\n\nPIN mismatch\n Try again!"<<endl<<endl;
			getch();
			pos=0;
		}
	}while(pos==0);
}

void main(){
	clrscr();
	wmenu();
}
