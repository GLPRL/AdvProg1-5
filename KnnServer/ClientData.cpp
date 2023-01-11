//
// Created by gp on 1/11/23.
//

#include "ClientData.h"

const vector<TypeVector> &ClientData::getTv() const {
    return tv;
}

const string &ClientData::getFileName() const {
    return fileName;
}

int ClientData::getK() const {
    return k;
}

const vector<double> &ClientData::getV() const {
    return v;
}

const map<string, int> &ClientData::getNames() const {
    return names;
}

int ClientData::getVSize() const {
    return vSize;
}

void ClientData::setFileName(const string &fileName) {
    ClientData::fileName = fileName;
}

void ClientData::setK(int k) {
    ClientData::k = k;
}

void ClientData::setTv(const vector<TypeVector> &tv) {
    ClientData::tv = tv;
}

void ClientData::setV(const vector<double> &v) {
    ClientData::v = v;
}

void ClientData::setNames(const map<string, int> &names) {
    ClientData::names = names;
}

void ClientData::setVSize(int vSize) {
    ClientData::vSize = vSize;
}

const