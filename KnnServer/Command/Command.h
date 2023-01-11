#include <utility>

#ifndef ADVPROG1_5_COMMAND_H
#define ADVPROG1_5_COMMAND_H
using namespace std;
#include <string>
#include "../IO/DefaultIO.h"
#include "../ClientData.h"

template <class T>
class Command {

private:
        string desc;        //desc. of the command
        DefaultIO *io;      //method of input/output
        ClientData *cd;     //contains data essential for classification
public:
    virtual void execute() = 0;
    string getDesc() {
        return this->desc;
    }

    void setDesc(const string &desc) {
        Command::desc = desc;
    }

    void setIo(DefaultIO *io) {
        Command::io = io;
    }

    void setCd(ClientData *cd) {
        Command::cd = cd;
    }

    DefaultIO *getIo() const {
        return io;
    }

    ClientData *getCd() const {
        return cd;
    }

    DefaultIO* getIO() {
        return this->io;
    }
    Command (string desc, DefaultIO* io, ClientData clientData) {
        this->desc = desc;
        this->io = io;
        this->cd = clientData;
    }
};
#endif //ADVPROG1_5_COMMAND_H
