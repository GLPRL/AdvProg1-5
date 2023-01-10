#include <utility>

#ifndef ADVPROG1_5_COMMAND_H
#define ADVPROG1_5_COMMAND_H
using namespace std;
#include <string>
#include "../IO/DefaultIO.h"
class Command {

private:
        string desc;
        DefaultIO *io;
public:
    virtual void execute() = 0;
};
#endif //ADVPROG1_5_COMMAND_H
