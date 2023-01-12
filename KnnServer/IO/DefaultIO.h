

#ifndef ADVPROG1_5_DEFAULTIO_H
#define ADVPROG1_5_DEFAULTIO_H
using namespace std;
#include <string>
class DefaultIO {
public:
    virtual void write(string) = 0;
    virtual string read() = 0;
};
#endif //ADVPROG1_5_DEFAULTIO_H
