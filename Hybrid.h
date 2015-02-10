#ifndef HYBRID_H
#define HYBRID_H
#include "Car.h"
#include "Bill.h"
class Hybrid;
ostream &operator<<(ostream &output, Hybrid &h); 
class Hybrid: public Car
{
friend ostream &operator<<(ostream &output, Hybrid &h); 
public:
    Hybrid(const int &, const int &, const string &, const double &, const double &, const string &, const double &, const double &, const double &, const double &);
    ~Hybrid();
    ostream& print_vehicle(ostream &output);
    double get_motor_power() const;
    double get_usage() const;
    double get_capacity() const;

private:
    double motor_power;
    double motor_usage;
    double battery_capacity;
};

#endif /* HYBRID_H */
