#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "bank.h"
using namespace std;
//files needed to operate this program are in folder "Data"
int main()
{
         
        ifstream plik;
        vector<string> list_of_banks;
        plik.open("Data\\List_of_banks.txt");//importing list of avaiable banks from the file

            if (!plik.good())
            {
                cout << "File does not exist!!!";
            }
            else
            {

                string line;
                cout << "List of Banks:" << endl;//printing avaiable banks
                while (plik.good())
                {
                    getline(plik, line);  
                    cout << line << endl;
                    list_of_banks.push_back(line);
                }
                    
            }
                      
        plik.close();
        string bank_log;
        bool choose = true;
        while (choose)
        {
            cout << "Choose bank to login: " << endl;
            cin >> bank_log;
			
            for (auto it = begin(list_of_banks); it != end(list_of_banks); it++)//choosing one of the banks and comparing them with existing banks
            {
                if (*it == bank_log)
                {
                    choose = false;
                    break;
                }
               
            }
        }
        control object(bank_log);
        auto it = begin(object.probank->client);
      
      string log_id, log_pass;
      choose = true;
      while (choose)
      {
          
          cout << "Login with id and password " << endl;
          cout << "login: ";
          cin >> log_id;
          cout << "password: ";
          cin >> log_pass;
		 // log_id = "5"; ===================================================
		//  log_pass = "abc123"; //===========================================

          for (auto it = begin(object.probank->client); it != end(object.probank->client); it++)//comparing data that was input by user with data from the file of the bank
          {//only possible way to login is by having input data from file chosen to coressponding bank. 

              if (dynamic_cast<user*>(*it)->id ==stoi(log_id))
              {
                  if (dynamic_cast<user*>(*it)->password == log_pass)
                  {
                      object.prouser = it;
                      choose = false;
                      break;

                  }
                  else
                  {
                      cout << "Invalid password" << endl;
                  }
              }

          }
      }
      
	  choose = true;
      if (dynamic_cast<employee*>(*object.prouser))//checking if user is an employee or client of the bank
      {
          while (choose)
          {
              cout << "Hello " << dynamic_cast<employee*>(*object.prouser)->name << endl;
              int client_acc;
              cout << "Choose a client to do operations:" << endl;
              cin >> client_acc;
              
              for (auto it = begin(dynamic_cast<bank*>(object.probank)->client); it != end(dynamic_cast<bank*>(object.probank)->client); it++)
              {
                  //comparing chosen client with one from the list of the bank
                  if(dynamic_cast<customer*>(*it))
                  {
                      if (client_acc == dynamic_cast<customer*>(*it)->id)
                      {
                         dynamic_cast<employee*>(*object.prouser)->cl_user = it;
                          cout <<"Your customer: "<<dynamic_cast<customer*>(*(dynamic_cast<employee*>(*object.prouser)->cl_user))->name << endl;
                          choose = false;
                          break;
                      }
                  }

              }


          }
          
          
          string option;
          for (;;)
          {
              cout << "C - create account, END - exit" << endl;//menu with options of employee
              cin >> option;
              {
                  if (option == "C")
                  {
                     //creating account for client
                      int new_acc_id = dynamic_cast<bank*>(object.probank)->acc.size()+1;
                      dynamic_cast<bank*>(object.probank)->acc.push_back(new account(new_acc_id, 0, dynamic_cast<customer*>(*(dynamic_cast<employee*>(*object.prouser)->cl_user))->id));
                      dynamic_cast<customer*>(*(dynamic_cast<employee*>(*object.prouser)->cl_user))->acc.push_back(new_acc_id);
                      dynamic_cast<employee*>(*object.prouser)->num_services += 1;
                      cout << "New account created!" << endl;
                      cout << "Your number of services done: " << dynamic_cast<employee*>(*object.prouser)->num_services << endl;//when service done, adding it to the counter

                  }
                  else if (option == "END")
                  {
                      //finishing using program and saving changed data to the files, that were operated on
                      object.probank->eksport();
                      break;
                  }
                  else 
                  {
                      cout << "unknown command" << endl;
                  }
              }
          }
          
          
      }
      else //when logged user is a customer 
      {
          int log_acc;
          cout << "Hello " << dynamic_cast<customer*>(*object.prouser)->name << endl;
          while (choose)
          {
              int zmienna = 1;
              cout << "Your accounts: " << endl;
              for (auto it = begin(dynamic_cast<customer*>(*object.prouser)->acc); it != end(dynamic_cast<customer*>(*object.prouser)->acc); it++)
              {
                  cout <<zmienna<<". " <<*it << endl;//showing all accounts of the customer
                  zmienna++;

              }
              if (dynamic_cast<customer*>(*object.prouser)->acc.size()>0)//if account exists
              {
                  cout << "Choose account to manage " << endl;//choice of account to do operation, only if customer has one
                  cin >> log_acc;
                  for (auto it = begin(dynamic_cast<customer*>(*object.prouser)->acc); it != end(dynamic_cast<customer*>(*object.prouser)->acc); it++)
                  {
                      if (log_acc == *it)
                      {
                          for (auto it2 = begin(object.probank->acc); it2 != end(object.probank->acc); it2++)
                          {
                              if (dynamic_cast<account*>(*it2)->id == log_acc)
                              {
                                  object.proaccount = it2;
                                  choose = false;
                                  break;
                              }

                          }
                      }


                  }
                  
              }
              else//if account doesnt exist
              {
                  cout << "You don't have any account" << endl<<"Ask our employee to create one for you"<<endl;
                  choose = false;
              }
              
              
          }
          if (dynamic_cast<customer*>(*object.prouser)->acc.size() > 0)
          {
              cout << "Your balance: " << dynamic_cast<account*>(*object.proaccount)->balance << endl;//printing balace of chosen account
              string option;
              for (;;)
              {
                  cout << "T - transfer money, A - add money, W - withdraw money, END - exit" <<endl;//menu of possible operations

                  cin >> option;
                  if (option == "T")
                  {
                      float money;
                      cout << "How much money do you want to transfer account? ";
                      cin >> money;
                      if (money <= dynamic_cast<account*>(*object.proaccount)->balance)//checking if customer has enough money to transfer
                      {
                          cout << "Choose account to transfer money to " << endl;//picking account from the same bank to transfer money
                          int acc_ch;
                          cin >> acc_ch;
                          for (auto it2 = begin(object.probank->acc); it2 != end(object.probank->acc); it2++)
                          {
                              if (dynamic_cast<account*>(*it2)->id == acc_ch)
                              {
                                  dynamic_cast<account*>(*it2)->balance += money;

                                  dynamic_cast<account*>(*object.proaccount)->balance -= money;
                                  cout << "Your new balace: " << dynamic_cast<account*> (*object.proaccount)->balance << endl;
                                  cin.clear();
                                  break;
                              }
                          }

                      }
                      else
                      {
                          cout << "You do not have enough money" << endl;
                      }

                  }
                  else if (option == "A")
                  {
                      float money;
                      cout << "How much money do you want to add to your account? ";//adding money to account
                      cin >> money;
                      dynamic_cast<account*> (*object.proaccount)->balance += money;
                      cout << "Your new balace: " << dynamic_cast<account*>(*object.proaccount)->balance << endl;
                      cin.clear();
                  }
                  else if (option == "W")//operation of withdrawing money from the account
                  {
                      float money;
                      cout << "How much money do you want withdraw from your account? ";
                      cin >> money;
                      
                      if (money <= dynamic_cast<account*>(*object.proaccount)->balance)//checking if customer has enough money
                      {
                          dynamic_cast<account*>(*object.proaccount)->balance -= money;
                          cout << "Your new balace: " << dynamic_cast<account*>(*object.proaccount)->balance << endl;
                          cin.clear();
                      }
                      else
                      {
                          cout << "You do not have enough money";
                      }
                  }
                  else if (option == "END")//finishing work of program and saving changed data to the file
                  {
                      object.probank->eksport();
                      break;
                  }
                  else
                  {
                      cout << "unknown command" << endl;
                  }
              }
          }

      }
}
//Magdalena Kasińska
