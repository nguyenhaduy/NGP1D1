#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include "DB_Set.h"
#include "DB_Engine.h"
#include "Application_Server.h"

using namespace std;

int main()
{
    /* ---------- INITIALIZING VARIABLES ---------- */

    int client, server;
    int portNum;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    DB_Set db_set;

    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\nWhat port number you want to connect to: ";
    cin >> portNum;

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }


    cout << "\n=> Socket server has been created..." << endl;


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */


    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(client, 1);


    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) 
        cout << "=> Error on accepting..." << endl;
    string input;
    while (server > 0) 
    {
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);
        cout << buffer << endl;

        cout << "Client: ";
        recv(server, buffer, bufsize, 0);
        cout << buffer << endl;

        while (!isExit)
        {
            cout << "Client: ";
            recv(server, buffer, bufsize, 0);
            cout << buffer << endl;
            input = buffer;
            if (*buffer == '#') {
                isExit = true;
            }
            else if (input == "@CreateCustomer") {
                Application_Server::CreateCustomer(server);
            }
            else if (input == "@CreateBankAccount"){
                cout << "Calling CreateBankAccount() function \n";
                Application_Server::CreateBankAccount(server);
            }
            else if (input == "@MakeTransaction"){
                cout << "Calling MakeTransaction() function \n";
                Application_Server::MakeTransaction(server);
            }
            else if (input == "@DeleteCustomer"){
                cout << "Calling DeleteCustomer() function \n";
                Application_Server::DeleteCustomer(server);
            }
            else if (input == "@DeleteBankAccount"){
                cout << "Calling DeleteBankAccount() function \n";
                Application_Server::DeleteBankAccount(server);
            }
            else if (input == "@DeleteTransaction"){
                cout << "Calling DeleteTransaction() function \n";
                Application_Server::DeleteTransaction(server);
            }
            else if (input == "@ViewCustomer"){
                cout << "Calling ViewCustomer() function \n";
                Application_Server::ViewCustomer(server);
            }
            else if (input == "@ViewBankAccount"){
                cout << "Calling ViewBankAccount() function \n";
                Application_Server::ViewBankAccount(server);
            }
            else if (input == "@ViewTransaction"){
                cout << "Calling ViewTransaction() function \n";
                Application_Server::ViewTransaction(server);
            }
            else {
                cout << buffer << endl;
                cout << "Strange function!!\n";
                db_set.input(input); 
            }
                       
        } 


        // inet_ntoa converts packet data to IP, which was taken from client
        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
    }

    close(client);
    close(server);
    return 0;
}