#include "Command.h"
#include "thread"
#include "iostream"
#include "../MainDistance.h"
template<class T>
class ClassifyData : public Command <T> {
public:

    void execute() override {
        if (this->getCd()->getFileName().empty()) {             //If there's no file
            this->getIO()->write("Please upload data");
            return;
        }
        //classify in thread? it's runMain function
        //detach from thread
        string s = runMain(this->getCd()->getAlg(), this->getCd()->getTv(), this->getCd()->getV(),
                this->getCd()->getK(), this->getCd()->getNames(), this->getCd()->getVSize());
        cout << s << endl;
    }
    ClassifyData(DefaultIO *io, Client *cd) : Command<T>("classify data", io, cd){}
};