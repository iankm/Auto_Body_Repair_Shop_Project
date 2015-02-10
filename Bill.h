#ifndef BILL_H
#define BILL_H

#include <string>
using namespace std;

#include <iostream>
using std::ostream;

typedef struct dummy_type {
    string name;
    double cost_of_parts;
    double cost_of_labor;
} data_type;

class Task
{
    friend class Bill;
public:
    Task( data_type *data );
    data_type* get_data();

private:
    data_type* content;
    Task *next_task;
};

class Bill
{

friend ostream operator<<( ostream &, const Task* task);

public:
    Bill();
    ~Bill();
    void insert_task(int index);
    void print_bill() const;
    double get_revenue() const;
private:
    Task *first_ptr;
    string names[5];
    double cost_of_parts[5];
    double cost_of_labor[5];
    double revenue;
};

#endif
