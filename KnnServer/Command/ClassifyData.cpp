#include "Command.h"
#include "thread"
#include "iostream"
#include "../MainDistance.h"

class ClassifyData : public Command {
public:
    void execute() override {
        if (this->getCd().getK() < 1 || this->getCd().getAlg() == "") {
            cout << "required parameters are not loaded" << endl;
            return;
        }
        if (this->getCd().getV().size() == 0 || this->getCd().getTv().size() == 0) {
            cout << "please upload data" << endl;
            return;
        }
        string s = runMain(this->getCd().getAlg(), this->getCd().getTv(), this->getCd().getV(),
                           this->getCd().getK(), this->getCd().getNames(), this->getCd().getVSize());
        cout << s << endl;
    }
    ClassifyData(DefaultIO *io, Client *cd) : Command("classify data", io, cd) {}
};