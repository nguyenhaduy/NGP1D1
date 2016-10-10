#pragma once

// #include "Login.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sstream>
#include "DB_Set.h"
#include "DB_Engine.h"
#include "Tuple.h"
#include "Table.h"
#include "Attribute.h"
#include "Relation_Ops.h"
#include "Condition.h"
#include <sstream>


// this class prints and manages the intro screen
class Application_Server
{	
public:
	static void CreateCustomer(int server);
	static void CreateBankAccount(int server);
	static void MakeTransaction(int server);
	static void DeleteCustomer(int server);
	static void DeleteBankAccount(int server);
	static void DeleteTransaction(int server);
	static void ViewCustomer(int server);
	static void ViewBankAccount(int server);
	static void ViewTransaction(int server);
};