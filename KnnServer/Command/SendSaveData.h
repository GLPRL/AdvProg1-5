

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
        if (this->getCd()->getV().size() == 0) {            //If no test vector exists
            s = "please upload data";
            this->getIO()->write(s);
            s = "@";
            this->getIO()->write(s);
        }
        if (this->getCd()->getV()[0].getType() == "") {
            s = "please classify the data";
            this->getIO()->write(s);
            s = "!";
            this->getIO()->write(s);
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
    void execute() override {
        //std::thread t(&SendSaveData::saveInThread, this);
        //t.join();
        //thread t1([this](){ saveInThread();});
        //t1.join();
        std::thread classify(&SendSaveData::saveInThread, this);
        classify.detach();
        //saveInThread();
    }

    SendSaveData(DefaultIO *io, Client *cd) : Command("send classifications", io, cd) {}
};