#include "Command.h"
#include "thread"
#include "iostream"

const string s1 = "Please upload your local train CSV file.";
const string s2 = "Please upload your local test CSV file.";

class UploadData : public Command {
public:
    void execute() override {
        this->getIO()->write(s1);
        string v;                                   //dest to receive vectors to
        string num;                                 //dest for a single double floating number
        while (v != sEnd) {
            v = this->getIO()->read();
            string temp = "";
            int size = v.size();
            for(int i=0; i < size; i++){
                if(v[i] != ','){
                    temp += v[i];
                } else {                //reached "," . process the string to a number
                    cout << temp << " ";
                    temp = "";
                }
            }
        }
    }
    UploadData(DefaultIO *io, Client *cd) : Command("upload data", io, cd) {}
};
