//
// Created by gp on 1/11/23.
//

#ifndef ADVPROG1_4_CLIENTDATA_H
#define ADVPROG1_4_CLIENTDATA_H
using namespace std;

#include <map>
#include "string"
#include "TypeVector.h"

class ClientData {
private:
    string fileName;
    int k;
    vector <TypeVector> tv;
    vector <double> v;
    map<string, int> names;
    int vSize;

public:
    const vector<TypeVector> &getTv() const;
    ClientData (string fileName, int k, vector <TypeVector> tv, vector<double> v, map<string, int> names, int vSize);

    void setFileName(const string &fileName);

    void setK(int k);

    void setTv(const vector<TypeVector> &tv);

    void setV(const vector<double> &v);

    void setNames(const map<string, int> &names);

    void setVSize(int vSize);

    const string &getFileName() const;

    int getK() const;

    const vector<double> &getV() const;

    const map<string, int> &getNames() const;

    int getVSize() const;
};


#endif //ADVPROG1_4_CLIENTDATA_H
