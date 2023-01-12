#include "../knnServer.h"
#include "SocketIO.h"
//TODO: read any data: options and lines
string SocketIO::read() {
    string msg;
    string ending = "\0";
    //Read until ending is detected
    char buffer[2048];
    ssize_t read_bytes;
    buffer[0] = 0;
    read_bytes = recv(this->sock, buffer, sizeof(buffer), 0);
    if (read_bytes < 0) {
        perror("error receiving from client");
    }
    msg.append(buffer);
    msg.append(ending);
    return msg;
}
void SocketIO::write(string s) {
    std::string msg = s + "\0";
    //Send the string through the socket
    size_t sent_bytes = send(this->sock, msg.c_str(), strlen(msg.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}
