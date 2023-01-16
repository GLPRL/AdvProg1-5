

#ifndef ADVPROG1_5_SENDDATA_H
#define ADVPROG1_5_SENDDATA_H
#include "Command.h"
#include <string>
#include <iostream>
#include "thread"
#include "../MainDistance.h"
#endif //ADVPROG1_5_SENDDATA_H

class SendSaveData : public Command {
public:
    void saveInThread() {
        string s;
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
    void execute() override {
        if (this->getCd()->getV().size() == 0) {            //If no test vector exists
            this->getIO()->write("@"); // please upload data
            return;
        }
        if (this->getCd()->getV()[0].getType() == "") {
            this->getIO()->write("!"); // please classify the data
            return;
        }
        std::thread classify(&SendSaveData::saveInThread, this);
        classify.detach();
    }

    SendSaveData(DefaultIO *io, Client *cd) : Command("send classifications", io, cd) {}
};