
#ifndef ADVPROG1_4_CLIENT_H
#define ADVPROG1_4_CLIENT_H
using namespace std;

#include <map>
#include "string"
#include "TypeVector.h"

class Client {
    string alg;
    string fileName;
    int k;
    vector <TypeVector> tv;
    vector <double> v;
    map<string, int> names;
    int vSize;
public:         //constr, getters, setters
    Client(const string &alg, const string &fileName, int k, const vector<TypeVector> &tv, const vector<double> &v,
               const map<string, int> &names, int vSize);

    const string &getAlg() const;

    void setAlg(const string &alg);

    const string &getFileName() const;

    void setFileName(const string &fileName);

    int getK() const;

    void setK(int k);

    const vector<TypeVector> &getTv() const;

    void setTv(const vector<TypeVector> &tv);

    const vector<double> &getV() const;

    void setV(const vector<double> &v);

    const map<string, int> &getNames() const;

    void setNames(const map<string, int> &names);

    int getVSize() const;

    void setVSize(int vSize);
};
#endif //ADVPROG1_4_CLIENT_H
