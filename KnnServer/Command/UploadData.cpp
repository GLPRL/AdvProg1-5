#include "Command.h"
#include "../MainDistance.h"
const string s1 = "Please upload your local train CSV file.\n";
const string s2 = "Please upload your local test CSV file.\n";

class UploadData : public Command {
public:
    void execute() override {
        //get the known types vectors
        this->getIO()->write(s1);
        string num;
        string s;
        vector<TypeVector> temp;
        char v[1];                               //copy from vtemp
        string vtemp;                            //receive from read()
        while (true) {                           //run over the lines
            vector<double> vNum;
            vtemp = this->getIO()->read();
            v[0] = vtemp[0];
            if (v[0] != '>') {                       //end cond.
                break;
            }
            while (v[0] != '$') {                   //Receive a full line
                num = num + v[0];                //vector represented as string
                vtemp = this->getIO()->read();
                v[0] = vtemp[0];
            }
            string word;
            stringstream ss(num);
            while (!ss.eof()) {                 //convert a line into vector of double prec. floating point
                getline(ss, word, ',');
                try {
                    double n = stod(word);
                    vNum.push_back(n);
                } catch (...) {                 //is a type string
                    s = word;
                    break;
                }
            }
            num = "";
            TypeVector tv = TypeVector(vNum, s);
            temp.push_back(tv);
        }
        this->getCd()->setVSize(temp[0].getVector().size());
        this->getCd()->setTv(&temp);
        this->getCd()->setNames(getAllNames(this->getCd()->getTv()));       //Create names DB
                                                //get the new vectors to classify
        this->getIO()->write(s2);
        num = "";
        vector<TypeVector> temp1;
        memset(&v, 0, 1);              //copy from vtemp
        vtemp.empty();                          //receive from read()
        while (true) {                          //run over the lines
            vector<double> vNum;
            vtemp = this->getIO()->read();
            v[0] = vtemp[0];
            if (v[0] != '>') {                   //end cond.
                break;
            }
            while (v[0] != '$') {                //Receive a full line
                num = num + v[0];                //vector represented as string
                vtemp = this->getIO()->read();
                v[0] = vtemp[0];
            }
            string word;
            stringstream ss(num);
            while (!ss.eof()) {                 //convert a line into vector of double prec. floating point
                getline(ss, word, ',');
                try {
                    double n = stod(word);
                    vNum.push_back(n);
                } catch (...) {
                    perror("error converting numbers");
                }
            }
            num = "";
            TypeVector tv = TypeVector(vNum, "");
            temp1.push_back(tv);
        }
        this->getCd()->setV(&temp1);
    }
    UploadData(DefaultIO *io, Client *cd) : Command("upload data", io, cd) {}
};