
#include "Client.h"
Client::Client() {};

Client::Client(const string &alg, const string &fileName, int k, const vector<TypeVector> &tv,
               const vector<TypeVector> &v, const map<string, int> &names, int vSize) : alg(alg),
                                                                                        fileName(fileName), k(k),
                                                                                        tv(tv), v(v), names(names),
                                                                                        vSize(vSize) {}

const string &Client::getAlg() const {
    return alg;
}

void Client::setAlg(const string &alg) {
    Client::alg = alg;
}

const string &Client::getFileName() const {
    return fileName;
}

void Client::setFileName(const string &fileName) {
    Client::fileName = fileName;
}

int Client::getK() const {
    return k;
}

void Client::setK(int k) {
    Client::k = k;
}

const vector<TypeVector> &Client::getTv() const {
    return tv;
}

void Client::setTv(const vector<TypeVector> *tv) {
    Client::tv = *tv;
}

vector<TypeVector> &Client::getV() {
    return v;
}

void Client::setV(const vector<TypeVector> *v) {
    Client::v = *v;
}

const map<string, int> &Client::getNames() const {
    return names;
}

void Client::setNames(const map<string, int> &names) {
    Client::names = names;
}

int Client::getVSize() const {
    return vSize;
}

void Client::setVSize(int vSize) {
    Client::vSize = vSize;
}

int Client::getClientSock() const {
    return client_sock;
}

void Client::setClientSock(int clientSock) {
    client_sock = clientSock;
}


