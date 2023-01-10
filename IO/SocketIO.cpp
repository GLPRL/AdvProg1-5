#include "../KnnServer/knnServer.h"
#include "SocketIO.h"

string SocketIO::read() {
    string msg;
    string ending = "\0";
    //Read until ending is detected
    char buffer[1];
    while (!equal(ending.rbegin(), ending.rend(), msg.rbegin())) {
        buffer[0] = 0;
        ssize_t read_bytes = recv(this->sock, buffer, 1, 0);
        if (read_bytes < 0) {
            perror("error writing to sock");
        }
        msg.append(buffer);
    }
    return msg.substr(0, msg.length() - 5);
}
void SocketIO::write(string s) {
    std::string msg = s + "\0";
    //Send the string through the socket
    size_t sent_bytes = send(this->sock, msg.c_str(), strlen(msg.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}
