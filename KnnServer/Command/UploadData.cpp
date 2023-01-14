#include "Command.h"
#include "thread"
#include "iostream"
#include "string"
#include "sstream"
const string s1 = "Please upload your local train CSV file.\n";
const string s2 = "Please upload your local test CSV file.";

class UploadData : public Command {
public:
    void execute() override {
        //get the known types vectors
        this->getIO()->write(s1);
        //get the new vectors to classifyd
        this->getIO()->write(s2);
        string num;
        vector<TypeVector> temp;
        char v[1];                          //copy from vtemp
        string vtemp;                       //receive from read()
        while (true) {                      //run over the lines
            vector<double> vNum;
            vtemp = this->getIO()->read();
            v[0] = vtemp[0];
            if (strcmp(v, ">") == 0) {          //end cond.
                break;
            }
            while (strcmp(v, "$") != 0) {        //Receive a full line
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
            temp.push_back(tv);
        }
        this->getCd()->setV(&temp);
        //cout << this->getCd().getV().size() << endl;
    }
    UploadData(DefaultIO *io, Client *cd) : Command("upload data", io, cd) {}
};