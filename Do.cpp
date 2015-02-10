#include "Tree.h"
#include "random_op.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int main()
{
    Tree<int> tree;
    int total_ops;
    int seed;
    int range;
    char op;
    int print_op;
    cout << "Enter maximum range: " << endl;
    cin >> range;
    cout << "Number of operations: " << endl;
    cin >> total_ops;
    cout << "Enter seed: " <<  endl;
    cin >> seed;
    cout << "Enter print option (0 for no keys, 1 for keys): " << endl;
    cin >> print_op;
    cout << endl;
    tree.MLH_set_print_option(print_op);
    Random_operation random_op(seed, range);
    for(int i = 1; i < total_ops; i++)
    {
        int* deleted;
        int inserted;
        int* obtained;
        random_op.Randomize_next_op();
        op = random_op.Get_op();
        switch(op)
        {
            case 'G':
                    obtained = tree.MLH_Get(random_op.Get_key()); 
                    break;
            case 'D':
                    deleted = tree.MLH_Delete(random_op.Get_key());
                    delete deleted;
                    break;
            case 'I':
                    int* integer = new int(i);
                    inserted = tree.MLH_Insert(random_op.Get_key(), integer);
                    if(inserted == 0)
                    {
                        delete integer;
                    }
                    break;
        };

        if( i % (total_ops/10) == 0)
        {
            cout << "Printing after: " << i  << " operations." << endl;
            tree.print_tree();
        } 
    }
    cout << "Printing after: " << total_ops << " operations." << endl;
    tree.print_tree();
}
