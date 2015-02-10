#include "Motorcycle.h"

/* Constructor, Motorcycle()
 * 
 * Initializes values for vehicle
 * Initializes engine_size, front_wheel_size, and back_wheel_size with given values
 * */
Motorcycle::Motorcycle(const int &i, const int &m_year, const string &c, const double &m, const double &e_s, const double &f_w, const double &b_w):Vehicle(i, m_year, c, m)
{
    engine_size = e_s;
    front_wheel_size = f_w;
    back_wheel_size = b_w;
}

/* Destructor, ~Motorcycle()
 *
 * Needed to trigger ~Vehicle() and delete bill.
 * */
Motorcycle::~Motorcycle()
{
}

/* Overloaded << operator
 * 
 * Calls print_vehicle for a motorcycle.
 * */
ostream &operator<<(ostream &output, Motorcycle &mc)
{
    output << mc.print_vehicle(output);
    return output;
}

/* Overloaded print_vehicle(ostream &operator) from Vehicle class
 *
 * Calls print_vehicle for vehicle, 
 * and prints engine_size, front_wheel_size, and back_wheel_size
 * */
ostream& Motorcycle::print_vehicle(ostream &output)
{
    Vehicle::print_vehicle(output);
    output << "Engine Size: " << get_engine_size() << "cc" << endl;
    output << "Front Wheel Size: " << get_front() << " m" << endl;
    output << "Back Wheel Size: " << get_back() << " m" << endl;
    return output;
}

/* get_engine_size()
 *
 * Returns engine_size.
 * */
double Motorcycle::get_engine_size() const
{
    return engine_size;
}

/* get_front()
 *
 * Returns front_wheel_size.
 * */
double Motorcycle::get_front() const
{
    return front_wheel_size;
}

/* get_back()
 *
 * Returns back_wheel_size.
 * */
double Motorcycle::get_back() const
{
    return back_wheel_size;
}
