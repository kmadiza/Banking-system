#include "bank.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

user::user(int Id, string Name, string Surname, int Age, bool Work, string Password):id(Id),name(Name),surname(Surname),age(Age),work(Work), password(Password)
{

}
customer::customer(int Id, string Name, string Surname, int Age, bool Work, string Password, vector<int> X) : user(Id, Name, Surname, Age, Work, Password), acc(X)
{

}
string customer::save_text()
{
	string accounts;
	for (auto it = begin(acc); it != end(acc); it++)//saving text for customer
	{
		accounts += to_string(*it);
		accounts += ";";

	}
	return to_string(work) + ";" + to_string(id) + ";" + name + ";" + surname + ";" + to_string(age) + ";" + password + ";" + accounts ;
}
employee::employee(int Id, string Name, string Surname, int Age, bool Work, string Password, int Num_services) : user(Id, Name, Surname, Age, Work, Password), num_services(Num_services)
{

}
string employee::save_text()//saving text for employee
{
	return to_string(work) + ";" + to_string(id) + ";" + name + ";" + surname + ";" + to_string(age) + ";" + password + ";" + to_string(num_services) + ";";
}
account::account(int Id, float Balance, int User_id) : id(Id), balance(Balance), user_id(User_id)
{

}
string account::save_text()//saving account data
{
	return to_string(id) + ";" + to_string(balance) + ";" + to_string(user_id) + ";";
}
bank::bank(string Name) : name(Name)
{

}
void bank::eksport()//saving data to file
{
	ofstream plik;
	plik.open("Data\\"+name+"_Accounts.txt",ofstream::trunc);
	int inter=0;
	for (auto it = begin(acc); it != end(acc); it++)
	{
		if (inter != 0)
			plik << endl;
		plik << dynamic_cast<account*>(*it)->save_text();
		inter++;
	}
	plik.close();
	ofstream plik2;
	plik2.open("Data\\" + name + ".txt", ofstream::trunc);
	int iter=0;
	for (auto it = begin(client); it != end(client); it++)
	{
		if (dynamic_cast<employee*>(*it))
		{
			if (iter !=0)
				plik2 << endl;
			plik2 << dynamic_cast<employee*>(*it)->save_text();
			iter++;
		}
		else
		{
			
			if(iter!=0)
			plik2 << endl;
			plik2 << dynamic_cast<customer*>(*it)->save_text();
			iter++;
		}

	}
}
control::control(string Name)
{
	probank = new bank(Name);
	ifstream plik;

	plik.open("Data\\" + Name + ".txt");

	if (!plik.good())
	{
		cout << "File does not exist!!!";
	}
	else
	{

		string line;
		string sub;
		stringstream ss;

		while (plik.good())//reading data of users of bank to file
		{
			getline(plik, line);
			ss << line;
			getline(ss, sub, ';');
			string Id_e;
			string Name_e;
			string Surname_e;
			string Age_e;
			string Password_e;
			getline(ss, Id_e, ';');
			getline(ss, Name_e, ';');
			getline(ss, Surname_e, ';');
			getline(ss, Age_e, ';');
			getline(ss, Password_e, ';');
			if (sub == "1")
			{

				string Num_services;

				getline(ss, Num_services, ';');
				probank->client.push_back(new employee(stoi(Id_e), Name_e, Surname_e, stoi(Age_e), true, Password_e, stoi(Num_services)));

			}
			else if (sub == "0")
			{
				string buffor;
				vector <int> data;
				while (ss.good())
				{
					getline(ss, buffor, ';');
					if (buffor == "")
					{
						break;
					}
					data.push_back(stoi(buffor));

				}
				probank->client.push_back(new customer(stoi(Id_e), Name_e, Surname_e, stoi(Age_e), false, Password_e, data));

			}
			ss.clear();

		}

	}

	plik.close();
	ifstream plik2;
	plik2.open("Data\\" + Name + "_Accounts.txt");//reading list of accounts in bank to file
		if (!plik2.good())
		{
			cout << "File does not exist!!!";
		}
		else
		{
			string line;
			string sub;
			stringstream ss;
			while (plik2.good())
			{
				getline(plik2, line);
				ss << line;
				string Id_a;
				string Balance_a;
				string User_id_a;
				getline(ss, Id_a, ';');
				getline(ss, Balance_a, ';');
				getline(ss, User_id_a, ';');
				probank->acc.push_back(new account(stoi(Id_a), stof(Balance_a), stoi(User_id_a)));
				ss.clear();
			}


		}
	plik2.close();


}
//Magdalena Kasiñska