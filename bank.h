#pragma once
#include <vector>
#include <iostream>
using namespace std;

class user
{
	friend class bank;
	friend class control;
	friend class ConsoleApplication20;
protected:
	int id;
	string name;
	string surname;
	int age;
	bool work;
	string password; 
public:
	user(int Id, string Name, string Surname, int Age, bool Work, string Password);
	string virtual save_text() = 0;
};

class customer :public user
{
public:
	vector <int> acc;
	customer(int Id, string Name, string Surname, int Age, bool Work, string Password, vector<int> X);
	string save_text();

	
};
class employee :public user
{
public:
	int num_services;
	employee(int Id, string Name, string Surname, int Age, bool Work, string Password, int Num_services);
	vector<user*>::iterator cl_user;
	string save_text();
};
class account
{
public:
	int id;
	float balance;
	int user_id;
	account(int Id, float Balance, int User_id); 
	string save_text();

	
};
class bank
{
public:
	vector <user*> client;
	vector <account*> acc;
	string name;
	int max_employees;
	bank(string Name);

	void eksport();
};
class control
{
public:
	bank* probank;
	vector<user*>::iterator prouser;
	vector <account*>::iterator proaccount;
	control(string Name);

};
//Magdalena Kasiñska