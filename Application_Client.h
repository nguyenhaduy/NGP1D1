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

// this class prints and manages the intro screen
class Application_Client
{
public:
	static void main_menu(int client); //prints menu, gets user input, and performs approprite action
	static void CreateCustomer(int client);
	static void CreateBankAccount(int client);
	static void MakeTransaction(int client);
	static void DeleteCustomer(int client);
	static void DeleteBankAccount(int client);
	static void DeleteTransaction(int client);
	static void ViewCustomer(int client);
	static void ViewBankAccount(int client);
	static void ViewTransaction(int client);
	static void exit(int client); //prints exit message and does no further action
};