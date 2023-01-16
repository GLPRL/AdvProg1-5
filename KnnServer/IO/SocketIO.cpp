#include "SocketIO.h"
/**
 * Read single line
 * @return line of text
 **/
string SocketIO::read() {
    string msg = "";
    char buffer[1];
    int read_bytes = recv(this->client_sock, buffer, 1, 0);       //Receive from client
    if (read_bytes < 0) {                                                                                     //If error
        perror("Error reading data from server");
    }
    msg = msg + buffer[0];
    memset(&buffer, 0, sizeof(buffer));
    return msg;
}
void SocketIO::write(string s) {
    size_t sent_bytes = send(this->client_sock, s.c_str(), strlen(s.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
}
