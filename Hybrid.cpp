#include "Hybrid.h"

/* Contructor, Hybrid()
 *
 * Initializes values for vehicle and car.
 * Initializes motor_power, motor_usage, battery_capacity to given values.
 * */
Hybrid::Hybrid(const int &i, const int &m_year, const string &c, const double &m, const double &e_s, const string &g, const double &p_l, const double &m_p, const double &m_u, const double &b_c ):Car(i, m_year, c, m, e_s, g, p_l)
{
    motor_power = m_p;
    motor_usage = m_u;
    battery_capacity = b_c;
}

/* Destructor, ~Hybrid()
 *
 * Needed to trigger ~Vehicle() and delete bill.
 * */
Hybrid::~Hybrid()
{
}

/* Overloaded << operator
 *
 * Prints a hybrid. Calls print_vehicle.
 * */
ostream &operator<<(ostream &output, Hybrid &h)
{
    output << h.print_vehicle(output);
    return output;
}

/* Overloaded print_vehicle(ostream &output) from Vehicle class
 *
 * Calls print_vehicle for car, 
 * and prints motor_power, motor_usage, and battery_capacity.
 * */
ostream& Hybrid::print_vehicle(ostream &output)
{
    Car::print_vehicle(output);
    output << "Motor Power: " << get_motor_power() << "hp" << endl;
    output << "Motor Usage: " << get_usage() << "hours" << endl;
    output << "Battery Capacity: " << get_capacity() << "Ah" << endl;
    return output;
}

/* get_motor_power()
 *
 * Returns motor_power.
 * */
double Hybrid::get_motor_power() const
{
    return motor_power;
}

/* get_usage()
 *
 * Returns motor_usage.
 * */
double Hybrid::get_usage() const
{
    return motor_usage;
}

/* get_capacity()
 *
 * Returns battery_capacity.
 * */
double Hybrid::get_capacity() const
{
    return battery_capacity;
}
