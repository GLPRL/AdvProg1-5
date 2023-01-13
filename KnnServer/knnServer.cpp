#include "knnServer.h"
#include "MainDistance.h"
#include "Command/Command.h"

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
void handleClient(int client_sock, map<string, int> names, vector<TypeVector> v) {
    Client cd;
    SocketIO io(client_sock);
    cd.setTv(v);
    cd.setNames(names);
    cd.setClientSock(client_sock);
    cd.setVSize(v[0].getVector().size());

    ClassifyData classifyData(&io, &cd);
    UploadData uploadData(&io, &cd);
    map<int, Command*> options;
    options.insert({1, &uploadData});
    options.insert({3, &classifyData});

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
    if (argc != 3) {                                                                               //Arg count validation
        perror("invalid input");
        return 1;
    }
    const int server_port = getPort(argv[2]);                                                     //Port validation
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
    int vSize = -1;
    string fileName = argv[1];
    vector<TypeVector> v = readData(vSize, fileName);           //TODO: move it. each client will have file
    map<string, int> names = getAllNames(v);                            //TODO: move it. each client will have file
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
        handleClient(client_sock, names, v);
        //TODO: detach from thread
    }
}