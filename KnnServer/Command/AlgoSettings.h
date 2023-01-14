//
// Created by dekel on 1/13/23.
//

#ifndef ADVPROG1_5_ALGOSETTINGS_H
#define ADVPROG1_5_ALGOSETTINGS_H

#endif //ADVPROG1_5_ALGOSETTINGS_H
#include "Command.h"
class AlgoSettings : public Command {
public:
    AlgoSettings(DefaultIO *io, Client *cd) : Command("settings", io, cd) {}
    void execute() override {

    }
};