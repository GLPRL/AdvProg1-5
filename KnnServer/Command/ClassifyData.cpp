#include "Command.h"
#include "thread"
#include "iostream"
#include "../MainDistance.h"
#include "string.h"

class ClassifyData : public Command {
public:
    void execute() override {
        //if (this->getCd().getFileName().empty()) {             //If there's no file
        //    this->getIO()->write("Please upload data");
        //    return;
        //}
        //classify in thread? it's runMain function
        //detach from thread
        //TODO: runMain on the vectors from the user object Client, after all vectors were loaded
        //TODO: receive data in loop. each vector will be received and processed, then inserted into v;
        char buffer[2048];
        //int expected_data_len = sizeof(buffer);
        //while(true) {
        //    memset(&buffer, 0, sizeof(buffer));
        //    int read_bytes = recv(this->getCd().getClientSock(), buffer, expected_data_len, 0);        //Receive data
        //    if (read_bytes < 0) {
        //        perror("Error reading from client");
        //    }
        //    char substr[6];
        //    memcpy(substr,&buffer[0], 5);               //check end condition: is <end>
        //    substr[5] = '\0';
        //    string endCheck = "<end>";
        //    int i;
        //    for (i = 0; i < 6; i++) {                           //if not equal then continue receiving from client
        //        if (endCheck[i] != substr[i]) {
        //            break;
        //        }
        //    }
        //    if (i == 5) {                       //if reached the end and all characters are equal then stop receiving
        //        break;
        //    }
            //TODO: PROCESS THE VECTOR
        //    continue;
        //}
        //temp vectors for checking
        vector<double> t1 = {0.1, 1.5, 3.1, 4.9};                   //TEMP VECTORS
        TypeVector tv1;
        tv1.setV(t1);
        vector<double> t2 = {1.3, 4.5, 2.8, 5.7};
        TypeVector tv2;
        tv2.setV(t2);
        vector<double> t3 = {1.4, 4.4, 3.1, 6.7};
        TypeVector tv3;
        tv3.setV(t3);
        vector<TypeVector> vv;
        vv.push_back(tv1);
        vv.push_back(tv2);
        vv.push_back(tv3);
        this->getCd().setV(vv);
        string s = runMain(this->getCd().getAlg(), this->getCd().getTv(), this->getCd().getV(),
                           this->getCd().getK(), this->getCd().getNames(), this->getCd().getVSize());
        cout << s << endl;
    }
    ClassifyData(DefaultIO *io, Client *cd) : Command("classify data", io, cd) {}
};