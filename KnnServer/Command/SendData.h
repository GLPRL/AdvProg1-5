

#ifndef ADVPROG1_5_SENDDATA_H
#define ADVPROG1_5_SENDDATA_H
#include "Command.h"
#include "../MainDistance.h"
#endif //ADVPROG1_5_SENDDATA_H

class SendData : public Command {
public:

    void execute() override {
        string s;
        if (this->getCd()->getV().size() == 0) {            //If no test vector exists
            s = "please upload data";
            this->getIO()->write(s);
            s = "@";
            this->getIO()->write(s);
            return;
        }
        if (this->getCd()->getV()[0].getType() == "") {
            s = "please classify the data";
            this->getIO()->write(s);
            s = "!";
            this->getIO()->write(s);
            return;
        }

        int size = this->getCd()->getV().size();
        for (int i = 0; i < size; i++) {
            s = s + to_string(i);
            s = s + "\t";
            s = s + this->getCd()->getV()[i].getType();
            s = s + "\n";
        }
        s = s + ">";
        this->getIo()->write(s);
    }
    SendData(DefaultIO *io, Client *cd) : Command("send classifications", io, cd) {}
};