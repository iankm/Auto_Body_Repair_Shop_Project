#include "Bill.h"

//Combination of pricelist and stack for the shop's tasks.

/* Constructor, Task()
 *
 * Initializes data to given value.
 * */
Task::Task( data_type* data)
    : content( data )
{

}


/* get_data()
 *
 * Gets a task's data, "content"
 * */
data_type* Task::get_data()
{
    return content;
}

/* Contructor, Bill()
 *
 * Initalizes first pointer in the stack (first_ptr) to NULL.
 * Initializes names, cost_of_parts, and cost_of_labor arrays.
 * */
Bill::Bill()
{
    first_ptr = NULL;

    names[0] = "Scheduled Maintenance";
    names[1] = "Brake Change";
    names[2] = "Tune-Up";
    names[3] = "Oil Change";
    names[4] = "Engine Repair";

    cost_of_parts[0] = 0;
    cost_of_parts[1] = 150.00;
    cost_of_parts[2] = 0;
    cost_of_parts[3] = 0;
    cost_of_parts[4] = 325.00;

    cost_of_labor[0] = 750.00;
    cost_of_labor[1] = 400.00;
    cost_of_labor[2] = 225.00;
    cost_of_labor[3] = 45.00;
    cost_of_labor[4] = 2675.00;
}

/* Destructor, ~Bill()
 *
 * Deletes all tasks in the stack.
 * Makes all strings the empty string.
 * */
Bill::~Bill()
{
    Task *ptask;

    while( first_ptr != NULL)
    {
        ptask = first_ptr;
        first_ptr = ptask->next_task;
        delete ptask;
    }
    for(int i = 0; i < 5; i++)
    {
        names[i] = "";
    }
}

/* insert_task(int index)
 *
 * Creates a new task and adds it to the stack.
 * */
void Bill::insert_task(int index)
{
    data_type* new_data = new data_type;
    new_data->name = names[index];
    new_data->cost_of_parts = cost_of_parts[index];
    new_data->cost_of_labor = cost_of_labor[index];
    revenue += (new_data->cost_of_parts + new_data->cost_of_labor);
    Task* ptask = new Task(new_data);
    ptask->next_task = first_ptr;
    first_ptr = ptask;
}


/* print_bill()
 *
 * Prints the bill, giving an invoice of all the tasks and their total prices.
 * */
void Bill::print_bill() const
{
    int count = 1;
    double total= 0;
    Task* ptask = first_ptr;
    while( ptask != NULL)
    {
        double total_cost = ptask->content->cost_of_parts + ptask->content->cost_of_labor;
        total += total_cost;
        cout << count << ") " << ptask->content->name << ": $" << total_cost << endl;
        ptask = ptask->next_task;
        count++;
    }
    cout << "Total: $" << total << endl;
}

/* get_revenue()
 *
 * Returns revenue. (Added to shop's total revenue)
 * */
double Bill::get_revenue() const
{
    return revenue;
}
