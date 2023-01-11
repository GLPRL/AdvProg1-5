

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
    string getType();
    vector<double> getVector();
    bool operator<(TypeVector v)const;
    double getDistance();
};
#endif //ADVPROG1_2_TYPEVECTOR_H