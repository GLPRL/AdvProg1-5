

#ifndef ADVPROG1_2_TYPEVECTOR_H
#define ADVPROG1_2_TYPEVECTOR_H
using namespace std;
#include <string>
#include <vector>
class TypeVector {
    vector<double> v;
    string type;
    double distance;
public:
    void calculateDistance(vector<double> v1, string distanceType);
    TypeVector(vector<double> v, string type);
    TypeVector();
    string getType();
    vector<double> getVector();
    bool operator<(TypeVector v)const;
    void setV(const vector<double> &v);
    double getDistance();
    void setType(const string &type);
};
#endif //ADVPROG1_2_TYPEVECTOR_H