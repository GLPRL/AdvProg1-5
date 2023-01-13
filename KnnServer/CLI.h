

#ifndef ADVPROG1_4_CLI_H
#define ADVPROG1_4_CLI_H

using namespace std;
#include "iostream"
#include "IO/DefaultIO.h"
#include "Command/Command.h"
const char* menu = "Welcome to the KNN Classifier Server. Please choose an option: \n"
                   "1. upload an unclassified csv data file\n"
                   "2. algorithm settings\n"
                   "3. classify data\n"
                   "4. display results\n"
                   "5. download results\n"
                   "8. exit\0";
class CLI {
    DefaultIO *io;
    map<int, Command> options;
public:
    CLI(DefaultIO *io, const map<int, Command> &options) : io(io), options(options) {}
    void run() {
        while (true) {
            io->write(menu);                               //Print menu
            string option = io->read();
            int optNum;
            try {
                optNum = stoi(option);
            } catch (...) {                             //Could not convert to option number
                io->write("Please enter a number");
                continue;
            }
            if (optNum == 6 || optNum == 7 || optNum < 1 || optNum > 8) {
                cout << "invalid option" << endl;
                continue;
            }
            if (optNum == 8) {
                cout << "exit" << endl;
                break;
            }
            options.at(optNum).execute();
        }
    }
};

#endif //ADVPROG1_4_CLI_H
