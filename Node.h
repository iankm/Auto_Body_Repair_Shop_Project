#ifndef NODE_H
#define NODE_H
#include "ML_hash.h"
#include "Tree.h"
#include <iostream>
using std::cout;
using std::ostream;

//Creates a constant for the size of all arrays in the nodes. Cleans up code
const int RANGE = 5;

template< typename T > class Tree;

template< typename T >
class Node
{
    friend class Tree< T >;
    friend class Autorepair;
    template< typename U >
    friend ostream &operator<<( ostream &, const Node<U>* n );
    public:
    Node();
    int keys[5];
    T* data[5];
    Node* children[5];
    bool is_empty();
    bool is_stem();
    bool is_full();
    
    void explode(int key, T* data, int level, int* num_steps, int* num_nodes);
    void collect(int* num_steps, int* num_nodes);
    void print_nodes(int print_option, int* max_level);

    private:
    int level;
    int num_keys;
    Node<T>* parent;
};

/* Constructor, Node()
 *
 * Initializes keys to 0, data to NULL, and pointers to children to NULL.
 * Level, num_keys, and are initialized to 0.
 * */
template< typename T >
Node<T>::Node()
{
    for(int i = 0; i < RANGE; i++)
    {
        keys[i] = 0;        
    }

    for(int i = 0; i < RANGE; i++)
    {
        data[i] = NULL;
    }

    for(int i = 0; i < RANGE; i++)
    {
        children[i]= NULL;
    }

    level = 0;
    num_keys = 0;
}

/* is_empty()
 *
 * Checks if the number of keys in the node is 0.
 * If it is, returns true.
 * Otherwise, returns false.
 * */
template< typename T >
bool Node<T>::is_empty()
{
    if(num_keys == 0)
        return true;
    return false;
}

/* is_stem()
 *
 * Checks if the node is responsible for more than 5 keys.
 * If so, returns true.
 * Otherwise, returns false.
 * */
template< typename T >
bool Node<T>::is_stem()
{
    if(num_keys > RANGE)
        return true;
    return false;
}

/* is_full()
 *
 * Checks if the node is responsible for 5 kes.
 * If so, returns treu.
 * Otherwise, returns false.
 * */
template< typename T >
bool Node<T>::is_full()
{
    if(num_keys == RANGE)
        return true;
    return false;
}

/* Overloaded << operator
 *
 * Prints the node's level, number keys, and its key-data pairs.
 * */
template< typename T >
ostream &operator<<(ostream &output, const Node<T>* n)
{
    output << "Level: " << n->level << ", Number of Keys: " << n->num_keys << endl;
    for(int i = 0; i < RANGE; i++)
    {
        if(n->keys[i] != 0)
        {
            output << i << ": [ " << n->keys[i] << ", " << *n->data[i] << " ]" << endl ; 
        }
    }
    return output;
}

/* print_nodes()
 *
 * Prints all the nodes in the tree.
 * Starts at the root (passed by Tree) and traverses to the bottom through
 * recursive calls.
 * Increments max_level upon traversing to children.
 * Decrements if child's level is smaller than max_level.
 * */
template< typename T >
void Node<T>::print_nodes(int print_option, int* max_level)
{  
    if(is_stem())
    {
        for(int i = 0; i < RANGE; i++)
        {
            if(children[i] != NULL)
            {
                if(children[i]->level > *max_level)
                    *max_level = children[i]->level;
                children[i]->print_nodes(print_option, max_level);
            }
        }
    }
    else if((print_option == 1) && (!is_stem()))
    {
        cout << this;
    }
    else if(!is_stem())
    {
        if(level < *max_level)
        *max_level = level;
    }
}

/* explode(int key, T* d, int level, int* num_steps, int* num_nodes)
 *
 * Called by insert if a node is full and key needs to be added to the tree.
 * Hashes each key and creates children at the given index, moves each key.
 * Lastly, inserts the new key into its specified child.
 * */
template< typename T >
void Node<T>::explode(int key, T* d, int level, int* num_steps, int* num_nodes)
{
    //Hashes each key. Inserts key into that index.
    int i = 0;
    while(i < RANGE)
    {
        int index = ML_hash(level + 1, keys[i]) - 1;
        (*num_steps)++;
        //If the index of the array does not point to a child, make a new one.
        if(children[index] == NULL)
        {
            Node<T>* new_node = new Node();
            new_node->level = level + 1;
            new_node->keys[0] = keys[i];
            new_node->data[0] = data[i];
            new_node->parent = this;
            children[index] = new_node; 
            children[index]->num_keys++;    
            (*num_nodes)++;
        }
        //If the child already exists, insert a key into the next open spot.
        else
        {
            int j = 0;
            j = children[index]->num_keys;
            children[index]->keys[j] = keys[i];
            children[index]->data[j] = data[i];
            children[index]->num_keys++;
        }
    (*num_steps)++;
    i++;
    }
    //Insert the newest key.
    int index = ML_hash(level + 1, key) - 1;
    //If the index of the array does not point to a child, make a new one.
    if(children[index] == NULL)
    {
        Node<T>* new_node = new Node();
        new_node->level = level + 1;
        new_node->keys[0] = key;
        new_node->data[0] = d;
        new_node->parent = this;
        children[index] = new_node;
        children[index]->num_keys++; 
        (*num_nodes)++;
    }
    //If the child exists but is full, explode that child.
    else if(children[index]->is_full())
    {
        children[index]->explode(key, d, level + 1, num_steps, num_nodes);
    }
    //Otherwise, insert a key into the next open spot.
    else
    {
        int j = 0;
        j = children[index]->num_keys;
        children[index]->keys[j] = key;
        children[index]->data[j] = d;
        children[index]->num_keys++;
    }
    num_keys++;
}

/* collect(int* num_steps, int* num_nodes)
 *
 * Called by delete.
 * If the number of keys in a parent's children is 5, then the parent 
 * collects it's children.
 * */
template< typename T >
void Node<T>::collect(int* num_steps, int* num_nodes)
{
    int current_index = 0;
    //For each of the children, take their keys and place them back in the parent.
    for(int i = 0; i < RANGE; i++)
    {
        if(children[i] != NULL)
        {
            for(int j = 0; j < children[i]->num_keys; j++)
            {
                if(children[i]->keys[j] != 0)
                {
                    keys[current_index] = children[i]->keys[j];
                    data[current_index] = children[i]->data[j];
                    children[i]->data[j] = NULL;
                    current_index++;
                }
            (*num_steps)++;
            }
            delete children[i];
            children[i] = NULL;
            (*num_nodes)--;
        }
    (*num_steps)++;
    }
    //If the parent's parent is responsible for only 5 keys now, 
    //collect its children
    if((parent != NULL) && (parent->num_keys <= RANGE))
    {
        parent->collect(num_steps, num_nodes);
    }

}

#endif /* NODE_H */
