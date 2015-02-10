#include "Car.h"

/* Constructor, Car()
 *
 * Initializes variables for vehicle, as well as engine_size, gas, and
 * pollution_level for Car to given values.
 * */
Car::Car(const int &i, const int &m_year, const string &c, const double &m, const double &e_s, const string &g, const double &p_l):Vehicle(i, m_year, c, m)
{
    engine_size = e_s;
    gas = g;
    pollution_level = p_l;
}

/* Destructor, ~Car()
 *
 * Needed to trigger vehicle's destructor and delete bill.
 * */
Car::~Car()
{
}

/* Overloaded << operator
 *
 * Prints a car. Calls print_vehicle.
 * */
ostream &operator<<(ostream &output, Car &c)
{
    output << c.print_vehicle(output);
    return output;
}

/* Overloaded print_vehicle(ostream &output) from Vehicle class
 *
 * Calls print_vehicle for vehicle.
 * Prints engine_size, gas, and pollution level.
 * */
ostream& Car::print_vehicle(ostream &output)
{
    Vehicle::print_vehicle(output);
    output << "Engine Size: " << get_engine_size() << "cc" << endl;
    output << "Gas: " << get_gas() << endl;
    output << "Pollution Level: " << get_pollution_level() << "%" << endl;
    return output;
}

/* get_engine_size()
 * 
 * Returns engine_size.
 * */
double Car::get_engine_size() const
{
    return engine_size;
}

/* get_gas()
 *
 * Returns gas.
 * */
string Car::get_gas() const
{
    return gas;
}

/* get_pollution_level()
 *
 * Returns pollution_level.
 * */
double Car::get_pollution_level() const
{
    return pollution_level;
}
