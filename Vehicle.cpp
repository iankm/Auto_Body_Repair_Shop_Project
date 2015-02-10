#include "Vehicle.h"

/* Contructor, Vehicle
 *
 * Initializes id, model_year, color, and mileage to given values.
 * Creates a new bill.
 * */
Vehicle::Vehicle(const int &i, const int &m_year, const string &c, const double &m):id(i), model_year(m_year), color(c), mileage(m)
{
    bill = new Bill();
}

/* Destructor, Vehicle
 *
 * Deletes bill.
 * */
Vehicle::~Vehicle()
{
    delete bill;
}

/* Overloaded << operator
 *
 * Prints the vehicle, calls print_vehicle.
 * */
ostream &operator<<(ostream &output, Vehicle &v)
{
    output << v.print_vehicle(output);
    return output;
}

/* print_vehicle(ostream &output)
 *
 * Prints the vehicle's id, model year, color, and mileage.
 * */
ostream& Vehicle::print_vehicle(ostream &output)
{
    output << "ID: " << get_id() << endl;
    output << "Model Year: " << get_model_year() << endl;
    output << "Color: " << get_color() << endl;
    output << "Mileage: " << get_mileage() << endl;
    return output;
}

/* get_bill()
 *
 * Returns bill.
 * */
Bill* Vehicle::get_bill() const
{
    return bill;
}

/* get_id()
 *
 * Returns id.
 * */
int Vehicle::get_id() const
{
    return id;
}

/* get_model_year()
 *
 * Returns model_year.
 * */
int Vehicle::get_model_year() const
{
    return model_year;
}


/* get_color()
 *
 * Returns color.
 * */
string Vehicle::get_color() const
{
    return color;
}

/* get_mileage()
 *
 * Returns mileage.
 * */
double Vehicle::get_mileage() const
{
    return mileage;
}
