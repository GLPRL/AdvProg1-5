

#ifndef ADVPROG1_5_SENDSAVEDATA_H
#define ADVPROG1_5_SENDSAVEDATA_H
#include "Command.h"
#include "../MainDistance.h"
#endif //ADVPROG1_5_SENDSAVEDATA_H
class SendnSaveData : public Command {
public:
    void execute() override {
        string s;
        if (this->getCd()->getV().size() == 0) {            //If no test vector exists
            s = "please upload data\n";
            this->getIO()->write(s);
            s = "@";
            this->getIO()->write(s);
            return;
        }
        if (this->getCd()->getV()[0].getType() == "") {
            s = "please classify the data\n";
            this->getIO()->write(s);
            s = "!";
            this->getIO()->write(s);
            return;
        }
        int size = this->getCd()->getV().size();
        for (int i = 0; i < size; i++) {
            s = s + to_string(i + 1);
            s = s + "\t";
            s = s + this->getCd()->getV()[i].getType();
            s = s + "\n";
        }
        s = s + ">";
        this->getIo()->write(s);
    }
    SendnSaveData(DefaultIO *io, Client *cd) : Command("send classifications w/o saving", io, cd) {}
};