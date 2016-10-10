#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Application_Client.h"

using namespace std;

int client;
int main()
{

    int portNum; 
    bool isExit = false;
    int bufsize = 4096;
    char buffer[bufsize];

    cout << "\nWhat port number you want to connect to: ";
    cin >> portNum;

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    /************* ESTABLISHING SOCKET CONNECTION *************/

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }


    cout << "\n=> Socket client has been created. Waiting for server feedback..." << endl;
    

    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(portNum);

    
    /************** CONNECTING THE SOCKET ***************/

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << ">>> Connecting to the server port number: " << portNum << endl;


    cout << ">>> Waiting for server confirmation..." << endl; 
    recv(client, buffer, bufsize, 0);
    cout << ">>> Connection confirmed!!!";
    string temp = "Connection confirmed by the client side!!!";
    strncpy(buffer, temp.c_str(), sizeof(buffer));
    send(client, buffer, bufsize, 0);


    /************** STARTING THE APPLICATION ***************/
    
    Application_Client::main_menu(client);

    /*************** CLOSE CONNECTION ****************/

    cout << "\n>>> Connection terminated.\nThank you for using Banking Application...\n";

    close(client);
    return 0;
}
