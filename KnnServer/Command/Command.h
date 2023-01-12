#include <utility>

#ifndef ADVPROG1_5_COMMAND_H
#define ADVPROG1_5_COMMAND_H
using namespace std;
#include <string>
#include "../IO/DefaultIO.h"
#include "../Client.h"
#include "../Client.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
class Command {

private:
        string desc;        //desc. of the command
        DefaultIO *io;      //method of input/output
        Client *cd;     //contains data essential for classification
public:
    virtual void execute() {}
    string getDesc() {
        return this->desc;
    }

    void setDesc(const string desc) {
        this->desc = desc;
    }

    void setIo(DefaultIO *io) {
        this->io = io;
    }

    void setCd(Client *cd) {
        this->cd = cd;
    }

    DefaultIO *getIo() const {
        return io;
    }

    Client getCd() const {
        return *cd;
    }

    DefaultIO* getIO() {
        return this->io;
    }
    Command (string desc, DefaultIO* io, Client *clientData) {
        this->desc = desc;
        this->io = io;
        this->cd = clientData;
    }
};
#endif //ADVPROG1_5_COMMAND_H
