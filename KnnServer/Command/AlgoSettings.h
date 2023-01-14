//
// Created by dekel on 1/13/23.
//

#ifndef ADVPROG1_5_ALGOSETTINGS_H
#define ADVPROG1_5_ALGOSETTINGS_H

#endif //ADVPROG1_5_ALGOSETTINGS_H
#include "Command.h"
class AlgoSettings : public Command {
private:
    void tokenize(std::string const &str, const char delim,
                  std::vector<std::string> &out) {
        std::stringstream ss(str);
        std::string s;
        while (std::getline(ss, s, delim)) {
            out.push_back(s);
        }
    }

public:
    AlgoSettings(DefaultIO *io, Client *cd) : Command("settings", io, cd) {}

    void execute() override {
        int k;
        int kInvalid = 0;
        int metInvalid = 0;

        string s = this->getIo()->read();
        string input = "";
        vector<string> msg;
        if (s.compare("$") == 0) {
            return;
        }
        while (s.compare("$") != 0) {
            input = input + s[0];
            s = this->getIo()->read();
        }
        tokenize(input, ' ', msg);
        try {
            k = stoi(msg[0]);
        }
        catch (...) {
            this->getIO()->write("invalid value for K");
            kInvalid = 1;
        }
        string met = (msg[1]);
        if(met.compare("AUC")||met.compare("MIN")||met.compare("CHB")||met.compare("CAN")||met.compare("MAN")){
            if(!kInvalid){
                this->getCd()->setK(k);
                this->getCd()->setAlg(met);
            }
        }
        else{
            this->getIO()->write("invalid value for metric");
            metInvalid=1;
        }
    }
};