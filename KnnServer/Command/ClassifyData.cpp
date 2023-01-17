#include "Command.h"
#include "thread"
#include "iostream"
#include "../MainDistance.h"

class ClassifyData : public Command {
public:
    void execute() override {
        if (this->getCd()->getV().size() == 0 || this->getCd()->getTv().size() == 0) {
            this->getIo()->write("!");
            this->getIo()->write("please upload data");
            return;
        }
        int i;
        for (i = 0; i < this->getCd()->getV().size(); i++) {                    //Classifies each vector
            string s = runMain(this->getCd()->getAlg(), this->getCd()->getTv(), this->getCd()->getV()[i],
                               this->getCd()->getK(), this->getCd()->getNames(), this->getCd()->getVSize());
            if (s == "invalid input") {             //if vectors aren't compliant
                return;
            }
            this->getCd()->getV()[i].setType(s);
        }
        this->getIo()->write(">");
    }
    ClassifyData(DefaultIO *io, Client *cd) : Command("classify data", io, cd) {}
};