#include "Autorepair.h"
#include <string>
using namespace std;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Tree<Vehicle>* inventory = new Tree<Vehicle>;

/* main()
 * 
 * Creates an Autorepair object and begins the program by printing the first menu.
 */
int main()
{
    Autorepair shop;
    cout << "\nWelcome to Ian's Auto Repair Shop!" << endl;
    cout << "----------------------------------\n" << endl; 
    shop.print_shop_menu();
}

/* Constructor, Autorepair()
 *
 * Initializes revenue to 0 and each job count (total_jobs[]) to 0.
 * */
Autorepair::Autorepair()
{
    revenue = 0;
    for(int i = 0; i < RANGE; i++)
        total_jobs[i] = 0;
}

/* print_shop_menu()
 * 
 * Prints the initial menu for the auto repair shop.
 * User can add vehicle, service a vehicle, see the services the shop offers,
 * view a vehicle, view every vehicle, and view statistics of the shop.
 * New day restarts the revenue and total jobs, as well as removes  all cars in the
 * shop.
 * */
void Autorepair::print_shop_menu()
{
    int selection;
    cout << "--------------------------" << endl;
    cout << "What would you like to do?" << endl;
    cout << "--------------------------\n" << endl; 
    cout << "1. Add Vehicle" << endl;
    cout << "2. Service Vehicle" << endl;
    cout << "3. View Services" << endl;
    cout << "4. View a Vehicle (Using Vehicle ID)" << endl;
    cout << "5. View all Vehicles" << endl;
    cout << "6. Check out a Vehicle" << endl;
    cout << "7. View Today's Statistics" << endl;
    cout << "8. New Day" << endl;
    cout << "9. Exit Auto Repair Shop" << endl;
    cout << "\nMake a selection: ";
    cin >> selection;
    switch(selection)
    {
        case 1: 
                cout << endl;
                print_vehicle_menu();
                break;
        case 2: 
                cout << endl;
                service_vehicle();
                break;
        case 3: 
                cout << "\nOur services include: " << endl;
                cout << "---------------------\n" << endl;
                cout << "Scheduled Maintenance: $750 (cost of labor only)" << endl;
                cout << "Brake Change: $150 (cost of parts) + $400 (cost of labor)" << endl;
                cout << "Tune-Up: $225 (cost of labor only)" << endl;
                cout << "Oil Change: $45 (cost of labor only)" << endl;
                cout << "Engine Repair: $325 (cost of parts) + $2675 (cost of labor)" << endl; 
                cout << endl;
                print_shop_menu();
                break;
        case 4: 
                print_one_vehicle(-1);
                cout << endl;
                cout << "Returning to shop menu." << endl;
                cout << endl;
                print_shop_menu();
                break;
        case 5: 
                print_all_vehicles(inventory->root);
                cout << endl;
                cout << "Returning to shop menu." << endl;
                cout << endl;
                print_shop_menu();
                break;
        case 6: 
                check_out_vehicle();
                cout << endl;
                print_shop_menu();
                break;
        case 7: 
                cout << "Today's Totals" << endl;
                cout << "--------------" << endl;
                cout << "\nTotal Revenue: $" << revenue << endl;
                cout << "Scheduled Maintenances Performed: " << total_jobs[0] << endl;
                cout << "Brake Changes Performed: " << total_jobs[1] << endl;
                cout << "Tune-Ups Performed: " << total_jobs[2] << endl;
                cout << "Oil Changes Performed: " << total_jobs[3] << endl;
                cout << "Engine Repairs Performed: " << total_jobs[4] << endl;
                cout << endl;
                cout << "Returning to shop menu." << endl;
                cout << endl;
                print_shop_menu();
                break;
        case 8: 
                revenue = 0;
                for(int i = 0; i < 5; i++)
                    total_jobs[i] = 0;
                destroy_shop(inventory->root);
                cout << "A new day has started! " << endl;
                cout << "Let's see our first customer: " << endl;
                cout << endl;
                print_shop_menu();
                break;
        case 9:
                break;
        default: 
                 cout << "Not an option." << endl;
                 cout << endl;
                 print_shop_menu();
    }
}

/* print_one_vehicle(int id)
 *
 * Prints vehicle with the specified id.
 * If given -1, asks for the id from the user. (Needed for check_out)
 * Otherwise, prints the vehicle with given id.
 * */
void Autorepair::print_one_vehicle(int id) const
{
    Vehicle* v_print;
    if(id == -1)
    {
        cout << "Enter the id of the vehicle you would like to print: " << endl;
        cin >> id;
        v_print = inventory->MLH_Get(id);
        if(v_print == NULL)
        {
            cout << "Sorry, we do not have that car in our inventory." << endl;
        }
        else
        {
            cout << *v_print;
        }
    }
    else
    {
        Vehicle* v_print = inventory->MLH_Get(id);
        if(v_print == NULL)
        {
            cout << "Sorry, we do not have that car in our inventory." << endl;
        }
        else
        {
            cout << *v_print;
        }
    }
}

/* print_all_vehicles(Node<Vehicle>* n)
 * 
 * Prints all vehicles in the shop's inventory.
 * */
void Autorepair::print_all_vehicles(Node<Vehicle>* n) const
{
    int space_count = 1;
    if(n->is_stem())
    {
        for(int i = 0; i < 5; i++)
        {
            if(n->children[i] != NULL)
                print_all_vehicles(n->children[i]);
        }
    }
    else
    {
        for(int j = 0; j < n->num_keys; j++)
        {
            int id = n->data[j]->get_id();
            cout << "Parking Space " << space_count << ": " << endl;
            print_one_vehicle(id);
            cout << endl;
            cout << endl;
            space_count++;
        }
    }
}

/* check_out_vehicle()
 *
 * Prints the invoice, records revenue, and deletes vehicle with given id from the
 * shop's inventory.
 * */
void Autorepair::check_out_vehicle()
{
    int id;
    cout << "Which vehicle would you like to check out? (Enter id): " << endl;
    cin >> id; 
    Vehicle* v_check_out = inventory->MLH_Get(id);
    if(v_check_out == NULL)
    {
        cout << "Sorry, we do not have that car in our inventory." << endl;
        cout << "Returning to shop menu." << endl;
    }
    else
    {
        cout << "Before you head out, here's your invoice: " << endl;
        cout << "\nYour vehicle: \n" << endl;
        print_one_vehicle(id);
        cout << "\n" << endl;
        cout << "Services provided: \n" << endl;
        v_check_out->get_bill()->print_bill(); 
        revenue += v_check_out->get_bill()->get_revenue();
        cout << "\nThank you for choosing Ian's Auto Repair!" << endl;
        Vehicle* checked_out = inventory->MLH_Delete(id);
        delete checked_out;
    }
   
}

/* print_vehicle_menu()
 *
 * Prints selection menu to choose a desired vehicle.
 * Calls methods to insert each of the different vehicles.
 * */
void Autorepair::print_vehicle_menu()
{
    int selection;
    cout << "Which Vehicle would you like to add?" << "\n" << endl;
    cout << "1. Car" << endl;
    cout << "2. Hybrid" << endl;
    cout << "3. Motorcycle" << endl;
    cout << "4. Bus" << endl;
    cout << "\nChoose vehicle by number: ";
    cin >> selection;
    switch(selection)
    {
        case 1:
                cout << "You chose car." << endl;
                insert_car();
                cout << "Car added to shop." << endl;
                cout << "Returning to shop menu." << "\n" << endl;
                print_shop_menu();
                break;
        case 2: 
                cout << "You chose hybrid." << endl;
                insert_hybrid();
                cout << "Hybrid added to shop." << endl;
                cout << "Returning to shop menu." << "\n" << endl;
                print_shop_menu();
                break;
        case 3: 
                cout << "You chose motorcycle." << endl;
                insert_motorcycle();
                cout << "Motorcycle added to shop." <<endl;
                cout << "Returning to shop menu." << "\n" << endl;
                print_shop_menu();
                break;
        case 4:
                cout << "You chose bus." << endl;
                insert_bus();
                cout << "Bus added to shop." << endl;
                cout << "Returning to shop menu." << "\n" << endl;
                print_shop_menu();
                break;
    }
}
/* service_vehicle()
 *
 * Asks for a vehicle in order to add a task to its bill.
 * */
void Autorepair::service_vehicle()
{
    int id;
    Vehicle* v;
    cout << "Which car would you like to service?" << endl;
    cout << "Enter vehicle id number: " << endl;
    cin >> id;
    v = inventory->MLH_Get(id);
    if(v == NULL)
    {
        cout << "Sorry, we do not have that car in our inventory." << endl;
        cout << "Returning to shop menu." << endl;
        print_shop_menu();
    }
    else
    {
        cout << endl;
        cout << "What did you come in for?" << endl;
        cout << "-------------------------\n" << endl;
        new_task(v);
    }
}

/* new_task(Vehicle *v)
 *
 * Prints possible tasks at the auto repair shop.
 * Adds specified task to the vehicle's bill.
 * */
void Autorepair::new_task(Vehicle* v)
{
    int selection;
    string another;
    cout << "1. Scheduled Maintenance" << endl;
    cout << "2. Brake Change" << endl;
    cout << "3. Tune-Up" << endl;
    cout << "4. Oil Change" << endl;
    cout << "5. Engine Repair" << endl;
    cout << "\nMake a selection: " << endl;
    cin >> selection; cout << endl;
    v->get_bill()->insert_task(selection - 1);
    total_jobs[selection - 1]++;
    if(selection == 1)
    {
        cout << "Alright, we'll take it around back.\n" << endl;
        cout << "Take a seat in the waiting room, your car will be read in a half hour or so." << endl;
    }
    else if(selection == 2)
    {
        cout << "Wait here a few minutes, we'll change those breaks for ya." << endl;
    }
    else if(selection == 3)
    {
        cout << "Came in for a tune-up, huh? We'll get right on that" << endl;
    }
    else if(selection == 4)
    {
        cout << "Lemme get my dipstick and we'll have a looksee." << endl;
    }
    else
    {
        cout << "Ooo. That's a big job. Come back in a day or so. We'll take care of everything." << endl;
    }
    cout << endl;
    cout << "Is there anything else you came for (yes or no)?" << endl;
    cin >> another;
    if((another == "yes") || (another == "y"))
    {
        cout << "What else can we do for you?" << endl;
        cout << "----------------------------\n" << endl;
        new_task(v);
    }
    else
    {
        cout << "Thank you for your patronage.\n" << endl;
        print_shop_menu();
    }

}

/* insert_vehicle(int &v_id, int &m_string, string &c, double &m)
 *
 * Asks user for vehicle's id, model year, color, and mileage.
 * Color can not have spaces in it.
 * */
void Autorepair::insert_vehicle(int &v_id, int &m_year, string &c, double &m) const
{
    while(true)
    {
        cout << "\nEnter your vehicle's id (1-100000): ";
        cin >> v_id; cout << endl;
        if(v_id < 1 || v_id > 100000)
        {
            cout << "Invalid id." << endl;
        }
        else
        {
            if(inventory->MLH_Get(v_id) != NULL)
            {
                cout << "A car with that id already exists in our inventory." << endl;
            }
            else
            {
                break;
            }
        }
    }
    while(true)
    {
        cout << "\nEnter model year (2000-2014): ";
        cin >> m_year;
        if(m_year < 2000 || m_year > 2014)
        {
            cout << "Invalid year." << endl; 
        }
        else
        {
            break;
        }   
    }
    cout << "\nEnter color: ";
    cin >> c;
    cout << "\nEnter mileage: ";
    cin >> m;
}

/* insert_car()
 *
 * Calls insert_vehicle and asks user for stats for a car.
 * */
void Autorepair::insert_car() const
{
    int v_id;
    int year;
    string color;
    double mileage;
    double e_size;
    string gas;
    double p_level;
    string okay;
    insert_vehicle(v_id, year, color, mileage);
    cout << "\nEnter engine size (cc): ";
    cin >> e_size;
    cout << "\nEnter gas type: " << endl;
    cout << "(Regular, Plus, Premium)" << endl;
    cin >> gas;
    cout << "\nEnter pollution level: ";
    cin >> p_level; cout << endl;
    cout << "\nAre you okay with these options (yes or no)?" << endl;
    cin >> okay;
    if((okay == "yes") || (okay == "y"))
    {
        Car* car = new Car(v_id, year, color, mileage, e_size, gas, p_level); 
        inventory->MLH_Insert(v_id, car);
    }
    else
    {
        cout << "Car not added to shop." << endl;
    }
}

/* insert_hybrid()
 *
 * Calls insert_vehicle and insert_car and asks user for stats for a hybrid.
 * */
void Autorepair::insert_hybrid() const
{
    int v_id;
    int year;
    string color;
    double mileage;
    double e_size;
    string gas;
    double p_level;
    double m_pow;
    double usage;
    double cap;
    string okay;
    insert_vehicle(v_id, year, color, mileage);
    cout << "\nEnter engine size (cc): ";
    cin >> e_size;
    cout << "\nEnter gas type: " << endl;
    cout << "(Regular, Plus, Premium)" << endl;
    cin >> gas;
    cout << "\nEnter pollution level: ";
    cin >> p_level;
    cout << "Enter motor power: ";
    cin >> m_pow;
    cout << "\nEnter overall usage: ";
    cin >> usage;
    cout << "\nEnter battery capacity: ";
    cin >> cap;
    cout << "Are you okay with these options (yes or no)?" << endl;
    cin >> okay;
    if((okay == "yes") || (okay == "y"))
    {
        Hybrid* hybrid = new Hybrid(v_id, year, color, mileage, e_size, gas, p_level, m_pow, usage, cap); 
        inventory->MLH_Insert(v_id, hybrid); 
    }
    else
    {
        cout << "Hybrid not added to shop." << endl;
    }
}

/* insert_motorcycle()
 *
 * Calls insert_vehicle and asks use for stats for a motorcycle.
 * */
void Autorepair::insert_motorcycle() const
{
    int v_id;
    int year;
    string color;
    double mileage;
    double e_size;
    double f_w_s;
    double b_w_s;
    string okay;
    insert_vehicle(v_id, year, color, mileage);
    cout << "\nEnter engine size (cc): ";
    cin >> e_size;
    cout << "\nEnter front wheel size (radius): ";
    cin >> f_w_s;
    cout << "\nEnter back wheel size (radius): ";
    cin >> b_w_s;
    cout << "Are you okay with these options (yes or no)?" << endl;
    cin >> okay;
    if((okay == "yes") || (okay == "y"))
    {
        Motorcycle* mc = new Motorcycle(v_id, year, color, mileage, e_size, f_w_s, b_w_s); 
        inventory->MLH_Insert(v_id, mc); 
    }
    else
    {
        cout << "Motorcycle not added to shop." << endl;
    }

}

/* insert_bus()
 *
 * Calls insert_vehicle() and asks user for stats for a bus.
 * */
void Autorepair::insert_bus() const
{
    int v_id;
    int year;
    string color;
    double mileage;
    int passenger_capacity;
    string okay;
    insert_vehicle(v_id, year, color, mileage);
    cout << "\nEnter passenger capacity: ";
    cin >> passenger_capacity;
    cout << "Are you okay with these options (yes or no)?" << endl;
    cin >> okay;
    if((okay == "yes") || (okay == "y"))
    {
        Bus* bus = new Bus(v_id, year, color, mileage, passenger_capacity);
        inventory->MLH_Insert(v_id, bus);
    }
    else
    {
        cout << "Bus not added to shop." << endl;
    }
}

/* destroy_shop(Node<Vehicle>* n)
 *
 * Goes through the shop's repository and destroys all vehicles and nodes.
 * */
void Autorepair::destroy_shop(Node<Vehicle>* n)
{
    if(n == NULL)
    return ;
    if(n->is_stem())
    {
        for(int i = 0; i < RANGE; i++)
            destroy_shop(n->children[i]);
    }
    else
    {
        for(int i = 0; i < (n->num_keys); i++)
        {
            delete n->data[i];
            n->data[i] = NULL;
        }
    }
    delete n;
    n = NULL;
}

/* Destructor, ~Autorepair()
 *
 * Calls destroy_shop
 * */
Autorepair::~Autorepair()
{
    destroy_shop(inventory->root); 
}
