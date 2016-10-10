#include "Application_Server.h"

using namespace std;

void Application_Server::CreateCustomer(int server)
{
  DB_Set db_set;
  char buffer[4096];
  recv(server, buffer, 4096, 0);
  cout << "Client: " << buffer << endl;
  string commands = buffer;
  cout << "Parsing commands for CreateCustomer!!!\n";
  db_set.input(commands);

  string result = "Successfully create new user!\n";
  strncpy(buffer, result.c_str(), sizeof(buffer));
  send(server, buffer, 4096, 0);    
  cout <<buffer;
}

void Application_Server::CreateBankAccount(int server)
{
  DB_Set db_set;
  int new_account = 1000000;  //account number starting at 1000000
  char buffer[4096];

  recv(server, buffer, 4096, 0);
  string ss_num = buffer;
  cout << ss_num << endl;

  recv(server, buffer, 4096, 0);
  string account_type = buffer;
  cout << account_type << endl;

  bool first_loop = true; 
  Table* account_table;

  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "SHOW customers_ssn;" +
      "CLOSE customers;\n"
    );
  Table* customer_table = db_set.get_last();
  if (!customer_table->is_empty()){

    do
    {
      if(!first_loop)
      {
        new_account++;
      }
      
      first_loop = false;
      
      db_set.input( (string)
        "OPEN accounts;\n" + 
        "account_numbers <- SELECT ( account_number == " + to_string(new_account) + " ) accounts;\n" +
        "CLOSE accounts;\n"
      );
      
      account_table = db_set.get_last();
    } while(!account_table->is_empty());

    cout << "New account number is: " << new_account << endl;

    string commands = "OPEN accounts;\n" + 
      ("INSERT INTO accounts VALUES FROM (" + to_string(new_account) + ", \"" + account_type + "\", 0);\n" +
      "CLOSE accounts;\n");
    cout << commands;
    db_set.input(commands);

    commands = "OPEN customer_account;\n" + 
      ("INSERT INTO customer_account VALUES FROM (\"" + ss_num + "\", " + to_string(new_account) + ");\n" +
      "CLOSE customer_account;\n");
    cout << commands;
    db_set.input(commands);
    string result = "Finish!!!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
  else {
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
}

void Application_Server::MakeTransaction(int server)
{
  DB_Set db_set;

  char buffer[4096];

  recv(server, buffer, 4096, 0);
  string ss_num = buffer;
  cout << ss_num << endl;

  recv(server, buffer, 4096, 0);
  string account_number = buffer;
  cout << account_number << endl;

  recv(server, buffer, 4096, 0);
  string amount = buffer;
  cout << amount << endl;

  bool first_loop = true; 
  Table* account_table;
  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "SHOW customers_ssn;" +
      "CLOSE customers;\n"
    );
  Table* customer_table = db_set.get_last();
  if (!customer_table->is_empty()){
    db_set.input( (string)
      "OPEN customer_account;\n" + 
      "account_numbers <- SELECT ( social_security_num == \"" + ss_num + "\" && account_number == \"" + account_number + "\") customer_account;\n" +
      "SHOW account_numbers;" +
      "CLOSE customer_account;\n"
    );
    Table* account_table = db_set.get_last();
    if (!account_table->is_empty()){
      cout << "Making transaction!!!\n";
        
        db_set.input( (string)
          "OPEN accounts;\n" + 
          "customer_account <- SELECT ( account_number == \"" + account_number + "\" ) accounts;\n" +
          "SHOW customer_account;\n" +
          "CLOSE accounts;\n"
        );
      Table* customer_account = db_set.get_last();
      vector<Tuple> check_tuple;
      check_tuple = customer_account->get_Tuples();
      vector<Attribute> check_attribute;
      check_attribute = check_tuple[0].get_Attributes();
      int temp_amount = check_attribute[2].get_Int_Value();
      cout << "Current balance = "<< temp_amount << endl;
      temp_amount = temp_amount + stoi(amount);
      cout << "New abalance = "<< temp_amount << endl;
      string new_balance = to_string (temp_amount);
        db_set.input( (string)
          "OPEN accounts;\n" + 
          "UPDATE accounts SET balance = \"" + new_balance + "\" WHERE ( account_number == \"" + account_number + "\"  );\n" +
          "after_account <- SELECT ( account_number == \"" + account_number + "\" ) accounts;\n" +
          "SHOW after_account;\n" +
          "CLOSE accounts;\n"
        );

      time_t raw_time;   //temp variables to store time info
      struct tm* usable_time;
      string time_stamp;   

      //get timestamp
      time(&raw_time);
      usable_time = gmtime(&raw_time);
      time_stamp = asctime(usable_time);    
      time_stamp.resize(time_stamp.size()-1);

      bool first_loop = true; 
      Table* transaction_table;
      int transaction_ID = 1;

      do
      {
        if(!first_loop)
        {
          cout << transaction_ID++ << endl;
        }
        
        first_loop = false;
        
        db_set.input( (string)
          "OPEN transactions;\n" + 
          "transaction_IDs <- SELECT ( transaction_ID == \"" + to_string(transaction_ID) + "\" ) transactions;\n" +
          "CLOSE transactions;\n"
        );
        
        transaction_table = db_set.get_last();
      } while(!transaction_table->is_empty());

      cout << "New transaction ID is: " << transaction_ID << endl;

      string commands = "OPEN transactions;\n" + 
        ("INSERT INTO transactions VALUES FROM (\"" + to_string(transaction_ID) + "\", \"" + time_stamp + "\", \"" + amount + "\");\n" +
        "CLOSE transactions;\n");
      cout << commands;
      db_set.input(commands);

      commands = "OPEN customer_transaction;\n" + 
        ("INSERT INTO customer_transaction VALUES FROM (\"" + ss_num + "\", \"" + to_string(transaction_ID) + "\");\n" +
        "CLOSE customer_transaction;\n");
      cout << commands;
      db_set.input(commands);

      commands = "OPEN account_transaction;\n" + 
        ("INSERT INTO account_transaction VALUES FROM (\"" + account_number + "\", \"" + to_string(transaction_ID) + "\");\n" +
        "CLOSE account_transaction;\n");
      cout << commands;
      db_set.input(commands);

      string result = "Finish perform transaction!\n";
      strncpy(buffer, result.c_str(), sizeof(buffer));
      send(server, buffer, 4096, 0);    
      cout <<buffer;
    } 
    else {
      string result = "This accounts doesn't belong to this customer!!!\n Please try again!\n";
      strncpy(buffer, result.c_str(), sizeof(buffer));
      send(server, buffer, 4096, 0);    
      cout <<buffer;
    }

  }
  else {
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }

}


void Application_Server::DeleteCustomer(int server)
{
  DB_Set db_set;

  char buffer[4096];

  recv(server, buffer, 4096, 0);
  string ss_num = buffer;
  cout << ss_num << endl;

  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "SHOW customers_ssn;" +
      "CLOSE customers;\n"
    );

  Table* customer_table = db_set.get_last();
  
  if (!customer_table->is_empty()){

      Table* relationship_table;
        
        db_set.input( (string)
          "OPEN customer_account;\n" + 
          "relationship_table <- SELECT ( social_security_num == \"" + ss_num + "\" ) customer_account;\n" +
          "SHOW relationship_table;\n" + 
          "CLOSE customer_account;\n"
        );

      relationship_table = db_set.get_last();
      vector<Tuple> check_tuple;
      check_tuple = relationship_table->get_Tuples();
      for (int i = 0; i <  check_tuple.size(); ++i){
        vector<Attribute> check_attribute;
        check_attribute = check_tuple[i].get_Attributes();
        int temp_account = check_attribute[1].get_Int_Value();
        db_set.input( (string)
          "OPEN accounts;\n" + 
          "DELETE FROM accounts WHERE( account_number == \"" + to_string(temp_account) + "\" );\n" +
          "CLOSE accounts;\n"
        );

      }

      db_set.input( (string)
          "OPEN customer_account;\n" + 
          "DELETE FROM customer_account WHERE( social_security_num == \"" + ss_num + "\" );\n" +
          "CLOSE customer_account;\n"
          );

      db_set.input( (string)
          "OPEN customers;\n" + 
          "DELETE FROM customers WHERE( social_security_num == \"" + ss_num + "\" );\n" +
          "CLOSE customers;\n"
          );

    string result = "Finish deleting account!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }

  else{
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }


}

void Application_Server::DeleteBankAccount(int server)
{
  DB_Set db_set;

  char buffer[4096];

  recv(server, buffer, 4096, 0);
  string account_number = buffer;
  cout << account_number << endl;

  db_set.input( (string)
      "OPEN accounts;\n" + 
      "delete_account <- SELECT ( account_number == \"" + account_number + "\" ) accounts;\n" +
      "SHOW delete_account;" +
      "CLOSE accounts;\n"
  );
  Table* delete_account_table = db_set.get_last();
  if (!delete_account_table->is_empty()){

      string commands = "OPEN accounts;\n" + 
        ("DELETE FROM accounts WHERE ( account_number == \"" + account_number + "\"  );\n" +
        "CLOSE accounts;\n");
      cout << commands;
      db_set.input(commands);

      commands = "OPEN customer_account;\n" + 
        ("DELETE FROM customer_account WHERE ( account_number == \"" + account_number + "\" );\n" +
        "CLOSE customer_account;\n");
      cout << commands;
      db_set.input(commands);

      string result = "Finish deleting account\n";
      strncpy(buffer, result.c_str(), sizeof(buffer));
      send(server, buffer, 4096, 0);    
      cout <<buffer;
  } else {
    string result = "The database doesn't have this account!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
}

void Application_Server::DeleteTransaction(int server)
{
  DB_Set db_set;
  char buffer[4096];
  recv(server, buffer, 4096, 0);
  string transaction_ID = buffer;
  cout << transaction_ID << endl;

  db_set.input( (string)
      "OPEN transactions;\n" + 
      "delete_transaction <- SELECT ( transaction_ID == \"" + transaction_ID + "\" ) transactions;\n" +
      "SHOW delete_transactions" +
      "CLOSE transactions;\n"
  );
  Table* delete_account_table = db_set.get_last();
  if (!delete_account_table->is_empty()){

      string commands = "OPEN customer_transaction;\n" + 
        ("DELETE FROM customer_transaction WHERE ( transaction_ID == \"" + transaction_ID + "\" );\n" +
        "CLOSE customer_transaction;\n");
      cout << commands;
      db_set.input(commands);

      commands = "OPEN account_transaction;\n" + 
        ("DELETE FROM account_transaction WHERE ( transaction_ID == \"" + transaction_ID + "\" );\n" +
        "CLOSE account_transaction;\n");
      cout << commands;
      db_set.input(commands);

      commands = "OPEN transactions;\n" + 
        ("DELETE FROM transactions WHERE ( transaction_ID == \"" + transaction_ID + "\" );\n" +
        "CLOSE transactions;\n");
      cout << commands;
      db_set.input(commands);

      string result = "Finish deleting transactions history!\n";
      strncpy(buffer, result.c_str(), sizeof(buffer));
      send(server, buffer, 4096, 0);    
      cout <<buffer;

  }
  else {
      string result = "The database doesn't have this transaction!!!\n Please try again!\n";
      strncpy(buffer, result.c_str(), sizeof(buffer));
      send(server, buffer, 4096, 0);    
      cout <<buffer;
    }
}

void Application_Server::ViewCustomer(int server)
{
  DB_Set db_set;
  char buffer[4096];
  recv(server, buffer, 4096, 0);
  string ss_num = buffer;
  cout << ss_num << endl;

  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "CLOSE customers;\n"
    );
  Table* customer_table = db_set.get_last();

  if (!customer_table->is_empty()){

    string commands = "OPEN customers;\n" + 
        ("viewed_customer <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
        "SHOW viewed_customer;" +
        "CLOSE customers;\n"
        );
    cout << commands;
    db_set.input(commands);
    strncpy(buffer, db_set.show_output.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);
  }
  else {
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
}

void Application_Server::ViewBankAccount(int server)
{
  DB_Set db_set;
  char buffer[4096];
  recv(server, buffer, 4096, 0);
  string ss_num = buffer;




aaadsfqewr


`   
  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "CLOSE customers;\n"
    );
  Table* customer_table = db_set.get_last();
  
  if (!customer_table->is_empty()){

    string commands = "OPEN customer_account;\n" + 
        ("viewed_customer <- SELECT ( social_security_num == \"" + ss_num + "\" ) customer_account;\n" +
        "CLOSE customer_account;\n"
        );
    cout << commands;
    db_set.input(commands);

    Table* relationship_table;
        
    relationship_table = db_set.get_last();
    vector<Tuple> check_tuple;
    check_tuple = relationship_table->get_Tuples();
    string output;
    for (int i = 0; i <  check_tuple.size(); ++i){
      vector<Attribute> check_attribute;
      check_attribute = check_tuple[i].get_Attributes();
      int temp_account = check_attribute[1].get_Int_Value();
      db_set.input( (string)
        "OPEN accounts;\n" + 
        "temp_table <- SELECT( account_number == \"" + to_string(temp_account) + "\" ) accounts;\n" +
        "SHOW temp_table;" +
        "CLOSE temp_table;"
        "CLOSE accounts;\n"
      );
      output = output + db_set.show_output;
    }

    strncpy(buffer, output.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);
  }
  else {
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
}

void Application_Server::ViewTransaction(int server)
{
  DB_Set db_set;
  char buffer[4096];
  recv(server, buffer, 4096, 0);
  string ss_num = buffer;
  cout << ss_num << endl;
  string output;

  db_set.input( (string)
      "OPEN customers;\n" + 
      "customers_ssn <- SELECT ( social_security_num == \"" + ss_num + "\" ) customers;\n" +
      "CLOSE customers;\n"
    );
  Table* customer_table = db_set.get_last();
  
  if (!customer_table->is_empty()){

    string commands = "OPEN customer_transaction;\n" + 
        ("viewed_customer <- SELECT ( social_security_num == \"" + ss_num + "\" ) customer_transaction;\n" +
        "CLOSE customer_transaction;\n"
        );
    cout << commands;
    db_set.input(commands);

    Table* relationship_table;
        
    relationship_table = db_set.get_last();
    vector<Tuple> check_tuple;
    check_tuple = relationship_table->get_Tuples();
    if ( check_tuple.size() != 0){
      for (int i = 0; i <  check_tuple.size(); ++i){
        vector<Attribute> check_attribute;
        check_attribute = check_tuple[i].get_Attributes();
        int temp_ID = check_attribute[1].get_Int_Value();
        db_set.input( (string)
          "OPEN transactions;\n" + 
          "temp_table <- SELECT( transaction_ID == \"" + to_string(temp_ID) + "\" ) transactions;\n" +
          "SHOW temp_table;" +
          "CLOSE temp_table;"
          "CLOSE transactions;\n"
        );
        output = output + db_set.show_output;
        }
      }
      else {
        output = "This customer doesn't have any transaction.\n";
      }

    strncpy(buffer, output.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);
  }
  else {
    string result = "The database doesn't have this customer!!!\n Please try again!\n";
    strncpy(buffer, result.c_str(), sizeof(buffer));
    send(server, buffer, 4096, 0);    
    cout <<buffer;
  }
}