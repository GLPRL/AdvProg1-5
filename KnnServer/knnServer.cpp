#include "knnServer.h"
#include "Command/Command.h"
#include "thread"
#include "Command/AlgoSettings.h"
#include "Command/SendData.h"
/**
 * Extracts relevant information from message received from the client.(from char[] c).
 * Separates the info to number vector, distanceType and k.
 */
void extract(char c[],int &k,string &distanceType,vector<double> &v) {

    string s (c);
    char *e;
    int pos=0;
    int wasDistance = 0;
    double x;
    s = ' ' + s + " ";
    while ((pos = s.find(" ")) != string::npos) {
        string sub = s.substr(0, pos);
        if ((sub.compare("AUC") == 0)
            || (sub.compare("MAN") == 0)
            || (sub.compare("CHB") == 0)
            || (sub.compare("CAN") == 0)
            || (sub.compare("MIN") == 0)
                ) {
            wasDistance = 1;
            distanceType = sub;

        } else if (wasDistance) {
            k = stoi(sub);
        } else {
            x = std::strtod(sub.c_str(), &e);
            v.push_back(x);
        }
        s.erase(0, pos + 1);
    }
    v.erase(v.begin());
}
/**
 * Check if port is valid: If can be converted to int, and is in range 0-65535
 * @param port port to listen on
 * @return port number if exists, -1 otherwise.
 */
int getPort(string port) {
    int size = port.size();
    for (int i = 0; i < size; i++) {                                  //Iterate through the port characters and validate
        if (isdigit(port[i]) == false) {
            perror("Invalid port entered");
            return -1;
        }
    }
    int serverPort = stoi(port);
    if (serverPort > 65535) {
        return -1;
    }
    if (serverPort < 0) {
        return -1;
    }
    return serverPort;
}
/**
 * Handle a single client in thread.
 * @param client_sock client
 */
void handleClient(int client_sock) {
    Client cd;
    SocketIO io(client_sock);
    cd.setClientSock(client_sock);
    ClassifyData classifyData(&io, &cd);
    UploadData uploadData(&io, &cd);
    SendData sendData(&io, &cd);
    AlgoSettings algoSettings(&io,&cd);
    map<int, Command*> options;
    options.insert({1, &uploadData});
    options.insert({3, &classifyData});
    options.insert({2, &algoSettings});
    options.insert({5, &sendData});

    CLI CLI(&io, options);
    CLI.run();
    close(client_sock);
}
/**
 * KNN Server.
 * @param argc count of command line args
 * @param argv command line args:
 * ARG[0] = server.out
 * ARG[1] = file to classify with
 * ARG[2] = port
 * Server receives data from client as STRING, and then divides according to whitespace the items
 * @return nothing
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {                                                                               //Arg count validation
        perror("invalid input");
        return 1;
    }
    const int server_port = getPort(argv[1]);                                                     //Port validation
    if (server_port == -1) {
        perror("invalid input");
        return 1;
    }
    int sock = socket(AF_INET, SOCK_STREAM, 0);                                   //Declaring socket
    if (sock < 0) {
        perror("Error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {                              //Bind socket
        perror("Error binding socket");
    }
    while (true) {
        if (listen(sock, 5) < 0) {
            perror("Error listening to a socket");
        }
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {                  //failed accepting new connection
            break;
        }
        //TODO: Thread to handle client
        // std:handleClient(client_sock);
        std::thread handleConnection(handleClient,client_sock);
        handleConnection.detach();
        //TODO: detach from thread
    }
}