#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H
#include "Vehicle.h"
#include "Bill.h"
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
class Motorcycle;
ostream &operator<<(ostream &output, Motorcycle &mc); 
class Motorcycle: public Vehicle
{
friend ostream &operator<<(ostream &output, Motorcycle &mc); 
public:
    Motorcycle(const int &, const int &, const string &, const double &, const double &, const double &, const double &);
    ~Motorcycle();
    ostream& print_vehicle(ostream &);
    double get_engine_size() const;
    double get_front() const;
    double get_back() const;

private:
    double engine_size;
    double front_wheel_size;
    double back_wheel_size;
};


#endif /* MOTORCYCLE_H */
