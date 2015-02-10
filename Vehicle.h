#ifndef VEHICLE_H
#define VEHICLE_H
#include "Bill.h"
#include <string>
using namespace std;
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;
class Vehicle;
ostream &operator<<(ostream &output, Vehicle &v); 
class Vehicle
{
friend ostream &operator<<(ostream &output, const Vehicle &v); 
friend class Autorepair;
public:
    Vehicle(const int &, const int &, const string &, const double &);
    virtual ~Vehicle();
    virtual ostream& print_vehicle(ostream &output);
    Bill* get_bill() const;
    int get_id() const;
    int get_model_year() const;
    string get_color() const;
    double get_mileage() const;
    Bill* bill; 
private:
    int id; 
    int model_year;
    string color;
    double mileage;
};

#endif /* VEHICLE_H */
