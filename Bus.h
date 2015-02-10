#ifndef BUS_H
#define BUS_H
#include "Vehicle.h"
#include "Bill.h"
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
class Bus;
ostream &operator<<(ostream &output, Bus &b); 
class Bus: public Vehicle
{
friend ostream &operator<<(ostream &output, Bus &b); 
public:
    Bus(const int &, const int &, const string &, const double &, const int &);
    ~Bus();
    ostream& print_vehicle(ostream &output);
    int get_passenger_capacity() const;

private:
    int passenger_capacity;
};

#endif /* BUS_H */
