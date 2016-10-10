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

    int portNum; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    // char* ip = "127.0.0.1";

    cout << "\nWhat port number you want to connect to: ";
    cin >> portNum;

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    if (client < 0) 
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }


    cout << "\n=> Socket client has been created..." << endl;
    

    server_addr.sin_family = AF_INET;

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(portNum);

    
    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Connection to the server port number: " << portNum << endl;


    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed!!!";
    string temp = "Connection confirmed by the client side!!!";
    strncpy(buffer, temp.c_str(), sizeof(buffer));
    send(client, buffer, bufsize, 0);

    Application_Client::main_menu(client);

    // cout << "\n\n=> Enter # to end the connection\n" << endl;

    // Once it reaches here, the client can send a message first.

    // do {
    //     cout << "Client: ";
    //     string temp;
    //     getline(cin, temp);
    //     strncpy(buffer, temp.c_str(), sizeof(buffer));
    //     send(client, buffer, bufsize, 0);
    //     if (*buffer == '#') {
    //         isExit = true;
    //     }

    //     cout << "Server: ";
    //     recv(client, buffer, bufsize, 0);
    //     if (*buffer == '#') {
    //         isExit = true;
    //     }
    //     cout << buffer << " ";
        
    //     cout << endl;

    // } while (!isExit);

    /* ---------------- CLOSE CALL ------------- */
    /* ----------------- close() --------------- */

    cout << "\n=> Connection terminated.\nGoodbye...\n";

    close(client);
    return 0;
}
