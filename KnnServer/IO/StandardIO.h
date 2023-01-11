

#ifndef ADVPROG1_4_STANDARDIO_H
#define ADVPROG1_4_STANDARDIO_H
#include "DefaultIO.h"
using namespace std;
class StandardIO: public DefaultIO {
public:
    void write(string s) override;
    string read() override;
};
#endif //ADVPROG1_4_STANDARDIO_H
