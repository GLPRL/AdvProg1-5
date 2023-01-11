//
// Created by gp on 1/11/23.
//

#include "Client.h"

ClientData::ClientData(const string &alg, const string &fileName, int k, const vector<TypeVector> &tv,
                       const vector<double> &v, const map<string, int> &names, int vSize) : alg(alg),
                                                                                            fileName(fileName), k(k),
                                                                                            tv(tv), v(v), names(names),
                                                                                            vSize(vSize) {}

const string &ClientData::getAlg() const {
    return alg;
}

void ClientData::setAlg(const string &alg) {
    ClientData::alg = alg;
}

const string &ClientData::getFileName() const {
    return fileName;
}

void ClientData::setFileName(const string &fileName) {
    ClientData::fileName = fileName;
}

int ClientData::getK() const {
    return k;
}

void ClientData::setK(int k) {
    ClientData::k = k;
}

const vector<TypeVector> &ClientData::getTv() const {
    return tv;
}

void ClientData::setTv(const vector<TypeVector> &tv) {
    ClientData::tv = tv;
}

const vector<double> &ClientData::getV() const {
    return v;
}

void ClientData::setV(const vector<double> &v) {
    ClientData::v = v;
}

const map<string, int> &ClientData::getNames() const {
    return names;
}

void ClientData::setNames(const map<string, int> &names) {
    ClientData::names = names;
}

int ClientData::getVSize() const {
    return vSize;
}

void ClientData::setVSize(int vSize) {
    ClientData::vSize = vSize;
}

