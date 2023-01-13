
#ifndef ADVPROG1_4_CLIENT_H
#define ADVPROG1_4_CLIENT_H
using namespace std;

#include <map>
#include "string"
#include "TypeVector.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
class Client {
private:
    int client_sock;        //Client socket
    string alg;             //Client's algorithm
    string fileName;        //Client's file
    int k;                  //Num of neighbors
    vector <TypeVector> tv; //known vectors
    vector <TypeVector> v;  //vectors to classify
    map<string, int> names; //names of types
    int vSize;
public:
    Client();

    Client(const string &alg, const string &fileName, int k, const vector<TypeVector> &tv, const vector<TypeVector> &v,
               const map<string, int> &names, int vSize);
    int getClientSock() const;
    void setClientSock(int clientSock);
    const string &getAlg() const;
    void setAlg(const string &alg);
    const string &getFileName() const;
    void setFileName(const string &fileName);
    int getK() const;
    void setK(int k);
    const vector<TypeVector> &getTv() const;
    void setTv(const vector<TypeVector> &tv);
    const vector<TypeVector> &getV() const;
    void setV(const vector<TypeVector> &v);
    const map<string, int> &getNames() const;
    void setNames(const map<string, int> &names);
    int getVSize() const;
    void setVSize(int vSize);
};
#endif //ADVPROG1_4_CLIENT_H
