#include "Bus.h"

/* Constructor, Bus()
 *
 * Initializes values for vehicle.
 * Initializes passenger_capacity.
 * */
Bus::Bus(const int &i, const int &m_year, const string &c, const double &m, const int &p_c):Vehicle(i, m_year,c,m)
{
    passenger_capacity = p_c;
}

/* Destructor, ~Bus()
 *
 * Needed to trigger ~Vehicle() and delete bill.
 * */
Bus::~Bus()
{

}

/* Overloaded << operator
 *
 * Calls print_vehicle for a bus.
 * */
ostream &operator<<(ostream &output, Bus &b)
{
    output << b.print_vehicle(output);
    return output;
}

/* Overloaded print_vehicle(ostream &output) from Vehicle class
 *
 * Calls print_vehicle for a vehicle,
 * and prints passenger_capacity.
 * */
ostream& Bus::print_vehicle(ostream &output)
{
    Vehicle::print_vehicle(output);
    cout << "Passenger Capacity: " << get_passenger_capacity() << endl;
    return output;
}

/* get_passenger_capacity()
 *
 * Returns passenger_capacity.
 * */
int Bus::get_passenger_capacity() const
{
    return passenger_capacity;
}
