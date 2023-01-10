
#ifndef ADVPROG1_4_SOCKETIO_H
#define ADVPROG1_4_SOCKETIO_H
#include "string"
#include "DefaultIO.h"


class SocketIO: public DefaultIO {
private:
    int sock;
public:
    explicit SocketIO(int socket);
    ~SocketIO();
    void write(string) override;
    string read() override;
};


#endif //ADVPROG1_4_SOCKETIO_H
