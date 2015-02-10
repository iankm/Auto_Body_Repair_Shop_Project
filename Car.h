#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
#include "Bill.h"
#include <string>
using namespace std;
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
class Car;
ostream &operator<<(ostream &output, Car &c); 
class Car: public Vehicle 
{
friend ostream &operator<<(ostream &output, Car &c); 
public:
    Car(const int &, const int &, const string &, const double &, const double &, const string &, const double &);
    ~Car();
    virtual ostream& print_vehicle(ostream &output);
    double get_engine_size() const;
    string get_gas() const;
    double get_pollution_level() const;
private:
    double engine_size;
    string gas;
    double pollution_level;
};


#endif /* CAR_H */
