#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
#include <stdlib.h>
#define MIN_BALANCE 100 
using namespace std;
class deficient_funds {};
class Cl_Accounts
{
private:
	long Accnt_No;
	string client_fname;
	string client_lname;
	float client_balance;
	static long Nxt_Accnt_No;

public:
	Cl_Accounts() {}
	Cl_Accounts(string fname, string lname, float client_balance);
	long getAccNo() { return Accnt_No; }
	string getFName() { return client_fname; }
	string getLName() { return client_lname; }
	float getBlnce() { return client_balance; }
	void Deposit(float amount);
	void Withdraw(float amount);
	static void setLstAccntNo(long Accnt_No);
	static long getLstAccntNo();
	friend ofstream& operator<<(ofstream& ofs, Cl_Accounts& acc);
	friend ifstream& operator>>(ifstream& ifs, Cl_Accounts& acc);
	friend ostream& operator<<(ostream& os, Cl_Accounts& acc);
};
long Cl_Accounts::Nxt_Accnt_No = 0;

class Bank
{
private:
	map<long, Cl_Accounts> accounts_cl;
public:
	Bank();
	Cl_Accounts Cl_Open_Account(string fname, string lname, float balance);
	Cl_Accounts Cl_Balance_Enquiry(long Account_no);
	Cl_Accounts Deposit(long Account_no, float amt);
	Cl_Accounts Withdraw(long Account_no, float amt);
	void CloseAccount(long Account_no);
	void ShowAllAccounts();
	~Bank();
};
int main()
{
	Bank b;
	Cl_Accounts acc;
	int option;
	string fname, lname;
	long account_no;
	float blnced;
	float amnts;
	system("Color B5");
	cout << "**********WELCOME TO BANK MANAGEMENT SYSTEM USING C++, OOPS AND FILEHANDLING*********" << endl;
	do
	{
		cout << "\n\tSelect One Option Below ";
		cout << "\n\t\t 1 Open an Account";
		cout << "\n\t\t 2 Balance Enquiry";
		cout << "\n\t\t 3 Cash Deposit";
		cout << "\n\t\t 4 Cash Withdrawal";
		cout << "\n\t\t 5 Close an Account";
		cout << "\n\t\t 6 Show All Current Accounts";
		cout << "\n\t\t 7 Quit";
		cout << "\n\t Enter required service option : ";
		cin >> option;
		switch (option)
		{
		case 1:
			system("Color E4");
			cout << "Enter First Name: " ;
			cin >> fname;
			cout << "Enter Last Name: ";
			cin >> lname;
			cout << "Enter Initial Deposit : ";
			cin >> blnced;
			acc = b.Cl_Open_Account(fname, lname, blnced);
			cout << endl << "Congratulations!!! Account Created" << endl;
			cout << acc;
			system("Color B5");
			break;
		case 2:
			system("Color E4");
			cout << "Enter Account Number:";
			cin >> account_no;
			acc = b.Cl_Balance_Enquiry(account_no);
			cout << endl << "Your Account Details" << endl;
			cout << acc;
			system("Color B5");
			break;
		case 3:
			system("Color E4");
			cout << "Enter Account Number:";
			cin >> account_no;
			cout << "Enter Cash To Be Deposited:";
			cin >> amnts;
			acc = b.Deposit(account_no, amnts);
			cout << endl << "Amount is Deposited" << endl;
			cout << acc;
			system("Color B5");
			break;
		case 4:
			system("Color E4");
			cout << "Enter Account Number:";
			cin >> account_no;
			cout << "Enter Balance:";
			cin >> amnts;
			acc = b.Withdraw(account_no, amnts);
			cout << endl << "Amount Withdrawn" << endl;
			cout << acc;
			system("Color B5");
			break;
		case 5:
			system("Color E4");
			cout << "Enter Account Number:";
			cin >> account_no;
			b.CloseAccount(account_no);
			cout << endl << "Account is Closed" << endl;
			cout << acc;
			system("Color B5");
		case 6:
			b.ShowAllAccounts();
			break;
		case 7: break;
		default:
			cout << "\nEnter corret choice";
			exit(0);
		}
	} while (option != 7);
	return 0;
}
Cl_Accounts::Cl_Accounts(string fname, string lname, float client_balance)
{
	Nxt_Accnt_No++;
	Accnt_No = Nxt_Accnt_No;
	client_fname = fname;
	client_lname = lname;
	this->client_balance = client_balance;
}

void Cl_Accounts::Deposit(float amt)
{
	client_balance += amt;
}
void Cl_Accounts::Withdraw(float amt)
{
	if (client_balance - amt <= MIN_BALANCE)
		throw deficient_funds();
	client_balance -= amt;
}
void Cl_Accounts::setLstAccntNo(long Accnt_No)
{
	Nxt_Accnt_No = Accnt_No;
}
long Cl_Accounts::getLstAccntNo()
{
	return Nxt_Accnt_No;
}
ofstream& operator<<(ofstream& ofs, Cl_Accounts& acc)
{
	ofs << acc.Accnt_No << endl;
	ofs << acc.client_fname << endl;
	ofs << acc.client_lname << endl;
	ofs << acc.client_balance << endl;
	return ofs;
}
ifstream& operator>>(ifstream& ifs, Cl_Accounts& acc)
{
	ifs >> acc.Accnt_No;
	ifs >> acc.client_fname;
	ifs >> acc.client_lname;
	ifs >> acc.client_balance;
	return ifs;
}
ostream& operator<<(ostream& os, Cl_Accounts& acc)
{
	os << "First Name:" << acc.getFName() << endl;
	os << "Last Name:" << acc.getLName() << endl;
	os << "Account Number:" << acc.getAccNo() << endl;
	os << "Balance:" << acc.getBlnce() << endl;
	return os;
}

Bank::Bank()
{
	Cl_Accounts acnt;
	ifstream infile;
	infile.open("Bank.data");
	if (!infile)
	{
		//cout<<"Error in Opening! File Not Found!!"<<endl;
		return;
	}
	while (!infile.eof())
	{
		infile >> acnt;
		accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccNo(), acnt));
	}
	Cl_Accounts::setLstAccntNo(acnt.getAccNo());
	infile.close();
}
Cl_Accounts Bank::Cl_Open_Account(string fname, string lname, float balance)
{
	ofstream outfile;
	Cl_Accounts acnt(fname, lname, balance);
	accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccNo(), acnt));
	outfile.open("Bank.data", ios::trunc);
	map<long, Cl_Accounts>::iterator itr;
	for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
	return acnt;
}
Cl_Accounts Bank::Cl_Balance_Enquiry(long Accnt_No)
{
	map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
	return itr->second;
}
Cl_Accounts Bank::Deposit(long Accnt_No, float amt)
{
	map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
	itr->second.Deposit(amt);
	return itr->second;
}
Cl_Accounts Bank::Withdraw(long Accnt_No, float amt)
{
	map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
	itr->second.Withdraw(amt);
	return itr->second;
}

void Bank::CloseAccount(long Accnt_No)
{
	map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
	cout << "Account Deleted" << itr->second;
	accounts_cl.erase(Accnt_No);
}

void Bank::ShowAllAccounts()
{
	map<long, Cl_Accounts>::iterator itr;
	for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
	{
		cout << "Account " << itr->first << endl << itr->second << endl;
	}
}

Bank::~Bank()
{
	ofstream outfile;
	outfile.open("Bank.data", ios::trunc);
	map<long, Cl_Accounts>::iterator itr;
	for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
	{
		outfile << itr->second;
	}
	outfile.close();
}
