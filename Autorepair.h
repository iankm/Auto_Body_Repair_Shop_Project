#ifndef AUTOREPAIR_H
#define AUTOREPAIR_H
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Hybrid.h"
#include "Bus.h"
#include "Tree.h"
#include "Bill.h"
class Autorepair
{
public:
    Autorepair();
    ~Autorepair();
    void print_shop_menu();
    void print_one_vehicle(int id) const;
    void print_all_vehicles(Node<Vehicle>* n) const;
    void print_vehicle_menu();
    void service_vehicle();
    void new_task(Vehicle* v); 
    void check_out_vehicle();
    void insert_vehicle(int &, int &, string &, double &) const;
    void insert_car() const;
    void insert_hybrid() const;
    void insert_motorcycle() const;
    void insert_bus() const;
    void destroy_shop(Node<Vehicle>* n);

private:
    double revenue;
    int total_jobs[5];
};

#endif /* AUTOREPAIR_H */
