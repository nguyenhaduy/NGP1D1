#include "Application_Client.h"

using namespace std;

void Application_Client::exit(int client)
{
  cout<<"\nThank you for using Banking Application! Goodbye!\n";
  char buffer[1024] = "#";
  send(client, buffer, 1024, 0);

}

void Application_Client::main_menu(int client)
{
  string input;
  int choice;
  bool isContinue = true;

  //chose which menu option to execute based on user input
  while (isContinue){

    cout<< "Press ENTER to continue!\n";
    getchar();
    //print welcome and ask user for menu input
    cout<<"\nWelcome to the Banking Application! What would you like to do?\n";
    cout<<"\n1. Create Customer";
    cout<<"\n2. Create Bank Account";
    cout<<"\n3. Make Transaction";
    cout<<"\n4. Delete Customer";
    cout<<"\n5. Delete Bank Account";
    cout<<"\n6. Delete Transaction History";
    cout<<"\n7. View Customer's Basic Information";
    cout<<"\n8. View Customer's Bank Accout";
    cout<<"\n9. View Customer's Transaction history";
    cout<<"\n10. Exit";
    cout<<"\n\nPlease enter your choice: ";
    
    // getline(cin, input);
    getline(cin, input);
    
    choice = atoi(input.c_str());

    switch(choice)
    {
      case 1:
        CreateCustomer(client);
        break;
      case 2:
        CreateBankAccount(client);
        break;
      case 3:
        MakeTransaction(client);
        break;
      case 4:
        DeleteCustomer(client);
        break;
      case 5:
        DeleteBankAccount(client);
        break;
      case 6:
        DeleteTransaction(client);
        break;
      case 7:
        ViewCustomer(client);
        break;
      case 8:
        ViewBankAccount(client);
        break;
      case 9:
        ViewTransaction(client);
        break;
      case 10:
        isContinue = false;
        exit(client);
        break;
      default:
        cout<<"\nInvalid user input. \n";
        break;
    }
  }
}

void Application_Client::CreateCustomer(int client)
{
  string full_name;           //stores inputted user data
  string ss_num;
  string address, phone_num, date_of_birth;
  cout<<"\nAdding new customer!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"\nFull Name: ";
  getline(cin, full_name);
  cout<<"Social security number: ";
  getline(cin, ss_num);
  cout<<"Address: ";
  getline(cin, address);
  cout<<"Phone number: ";
  getline(cin, phone_num);
  cout<<"Day of birth: ";
  getline(cin, date_of_birth);

  char buffer[1024] = "@CreateCustomer";
  send(client, buffer, 1024, 0);
  string query;
  //order of customers is (SSC number, name, address, phone, date of birth)
    query = "OPEN customers;\n" + 
    ("INSERT INTO customers VALUES FROM (\"" + ss_num + "\", \"" + full_name + 
      "\", \"" + address + "\", \"" + phone_num + "\", \"" + date_of_birth + "\");\n" + 
      "CLOSE customers;\n");
    // query = "OPEN customers;\nCLOSE customers;\n";
    strncpy(buffer, query.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);
}

void Application_Client::CreateBankAccount(int client)
{
  //stores inputted user data
  string ss_num;
  string input;
  int choice;
  string account_type;
  cout<<"\nCreating new account!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"\nSocial security number: ";
  getline(cin, ss_num);

  bool isContinue = true;
  bool cancel = false;
  while(isContinue)
  {
    cout<<"\nWhat type of account you want to create?\n";
    cout<<"\n1. Debit Account";
    cout<<"\n2. Credit Account";
    cout<<"\n3. Cancel";
    cout<<"\n\nPlease enter your choice: ";
    getline(cin, input);
    choice = atoi(input.c_str());

    //chose which menu option to execute based on user input
    switch(choice)
    {
      case 1:
        account_type = "Debit";
        isContinue = false;
        break;
      case 2:
        account_type = "Credit";
        isContinue = false;
        break;
      case 3:
        isContinue = false;
        cancel = true;
        break;
      default:
        cout<<"\nInvalid user input.\n Please try again!\n";
        break;
    }
  }

  if (!cancel){

    char buffer[1024] = "@CreateBankAccount";
    send(client, buffer, 1024, 0);
    strncpy(buffer, ss_num.c_str(), sizeof(buffer));
    send(client, buffer, 1024, 0);
    strncpy(buffer, account_type.c_str(), sizeof(buffer));
    send(client, buffer, 1024, 0);
    recv(client, buffer, 1024, 0);
    cout << buffer;
  }
}

void Application_Client::MakeTransaction(int client)
{
  //stores inputted user data
  string ss_num;
  string address;
  string input;
  int choice;
  string account_number;
  string amount;
  int temp_amount;
  cout<<"\nMaking Transaction!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"\nSocial security number: ";
  getline(cin, ss_num);

  bool isContinue = true;  
  bool cancel = false;
    cout<<"\nWhat account number you want to do transaction: ";
    getline(cin, account_number);
    
    while (isContinue)
    {
      cout<<"\nWhat type of transaction you want to do?\n";
      cout<<"\n1. Deposit";
      cout<<"\n2. Withdraw";
      cout<<"\n3. Cancel";
      cout<<"\n\nPlease enter your choice: ";
      cin >> choice;

      //chose which menu option to execute based on user input
      switch(choice)
      {
        case 1:
          cout<<"\n\nHow much you want to deposit: ";
          isContinue = false;
          cin >> temp_amount;
          amount = to_string(temp_amount);
          break;
        case 2:
          cout<<"\n\nHow much you want to withdraw: ";
          isContinue = false;
          cin >> temp_amount;
          amount = '-' + to_string(temp_amount);
          break;
        case 3:
          isContinue = false;
          cancel = true;          
          break;
        default:
          cout<<"\nInvalid user input.\n";
          break;
      }
    }

  if (!cancel) {
    char buffer[1024] = "@MakeTransaction";
    send(client, buffer, 1024, 0);
    strncpy(buffer, ss_num.c_str(), sizeof(buffer));
    send(client, buffer, 1024, 0);
    strncpy(buffer, account_number.c_str(), sizeof(buffer));
    send(client, buffer, 1024, 0);
    strncpy(buffer, amount.c_str(), sizeof(buffer));
    send(client, buffer, 1024, 0);

    recv(client, buffer, 1024, 0);
    cout << buffer << endl;


  }
}

void Application_Client::DeleteCustomer(int client)
{
  //stores inputted user data
  string ss_num;
  cout<<"\nDeleting customer!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"\nSocial security number: ";
  getline(cin, ss_num);

  char buffer[1024] = "@DeleteCustomer";
  send(client, buffer, 1024, 0);
  strncpy(buffer, ss_num.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}

void Application_Client::DeleteBankAccount(int client)
{
  //stores inputted user data
  string ss_num;
  string account_number;
  cout<<"\nDeleting bank account!";
  cout<<"\nPlease enter customer's information below:\n";  
  cout<<"\nWhat account number you want to delete: ";
  getline(cin, account_number);

  char buffer[1024] = "@DeleteBankAccount";
  send(client, buffer, 1024, 0);
  strncpy(buffer, account_number.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}

void Application_Client::DeleteTransaction(int client)
{
  string transaction_ID;
  cout<<"\nDeleting transaction!";
  cout<<"\nWhat transaction ID you want to delete: ";
  getline(cin, transaction_ID);
  char buffer[1024] = "@DeleteTransaction";
  send(client, buffer, 1024, 0);
  strncpy(buffer, transaction_ID.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}

void Application_Client::ViewCustomer(int client)
{
  //stores inputted user data
  string ss_num;
  cout<<"\nView customer's information!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"Social security number: ";
  getline(cin, ss_num);
  char buffer[1024] = "@ViewCustomer";
  send(client, buffer, 1024, 0);
  strncpy(buffer, ss_num.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}

void Application_Client::ViewBankAccount(int client)
{
  string ss_num;
  cout<<"\nView Bank Account's information!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"Social security number: ";
  getline(cin, ss_num);
  char buffer[1024] = "@ViewBankAccount";
  send(client, buffer, 1024, 0);
  strncpy(buffer, ss_num.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}

void Application_Client::ViewTransaction(int client)
{
  string ss_num;
  cout<<"\nView Transaction history!";
  cout<<"\nPlease enter customer's information below:\n";
  cout<<"Social security number: ";
  getline(cin, ss_num);
  char buffer[1024] = "@ViewTransaction";
  send(client, buffer, 1024, 0);
  strncpy(buffer, ss_num.c_str(), sizeof(buffer));
  send(client, buffer, 1024, 0);

  recv(client, buffer, 1024, 0);
  cout << buffer << endl;
}