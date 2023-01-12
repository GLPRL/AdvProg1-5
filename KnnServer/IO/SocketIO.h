
#ifndef ADVPROG1_4_SOCKETIO_H
#define ADVPROG1_4_SOCKETIO_H
#include "string"
#include "DefaultIO.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "cstring"

class SocketIO: public DefaultIO {
private:
    int client_sock;
public:
    SocketIO(int client_sock) {
        this->client_sock = client_sock;
    }
    void write(string) override;
    string read() override;
};

#endif //ADVPROG1_4_SOCKETIO_H
