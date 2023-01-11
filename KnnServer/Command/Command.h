#include <utility>

#ifndef ADVPROG1_5_COMMAND_H
#define ADVPROG1_5_COMMAND_H
using namespace std;
#include <string>
#include "../../IO/DefaultIO.h"
template <class T>
class Command {

private:
        string desc;
        DefaultIO *io;
        string alg;
        int k = -1;
public:
    virtual void execute() = 0;
    string getDesc() {
        return this->desc;
    }
    DefaultIO* getIO() {
        return this->io;
    }
    Command (string desc, DefaultIO* io) {
        this->desc = desc;
        this->io = io;
        this->alg = NULL;
    }
};
#endif //ADVPROG1_5_COMMAND_H
