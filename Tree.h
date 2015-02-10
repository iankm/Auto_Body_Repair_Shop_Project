#ifndef TREE_H
#define TREE_H
#include <iostream>
using std::cout;
using std::endl;
#include "Node.h"

template< typename T >
class Tree
{

public:
    friend class Autorepair;
    friend class Node< T >;
    template< typename U >
    friend ostream &operator<<( ostream &, Tree<U>* t ); 
    Tree();
    ~Tree();
    void MLH_set_print_option( int num );
    void print_tree();
    T* MLH_Get( int key );
    int MLH_Insert( int key, T* data );
    T* MLH_Delete( int key );
    void increment_num_keys( Node<T>* n );
    void decrement_num_keys( Node<T>* n );
    void destroy_tree( Node<T>* n );
private:
    int num_steps;
    int max_level;
    int print_option;
    int num_nodes;
    Node<T>* previous;
    Node<T>* root;
    T* node_get( int key, int level, Node<T>* n );
    int node_insert( int key, T* data, int level, Node<T>* n );
    T* node_delete( int key, int level, Node<T>* n );
};


/* The constructor, Tree()
 *
 * initializes num_steps, root, previous, and print_option. 
 * num_steps is initialized to 0
 * the root node is created and its parent is set to NULL
 * previous (for use in delete and insert) is set to NULL
 * print_option is set to 0 (by default, no keys are printed.)
 * */
template< typename T >
Tree<T>::Tree()
{
    num_steps = 0;
    num_nodes = 1;
    root = new Node<T>();
    previous = NULL;
    root->parent = NULL;
    print_option = 0;
    max_level = 0;
}

/* Overloaded << operator.
 * 
 * Prints the deepest level, total number of steps taken, and total objects in the tree.
 * */
template< typename T >
ostream &operator<<(ostream &output, Tree<T>* t)
{
    output << "Deepest level: " << t->max_level << endl;
    output << "Number of steps taken: " << t->num_steps << endl;
    output << "Number of nodes: " << t->num_nodes << endl;
    return output;
}

/* print_tree()
 * 
 * By default, prints out the tree's deepest level, total steps taken, and 
 * number of objects by calling the overloaded << operator.
 * Passes print_nodes a print_option of 1, which prints all nodes in the array.
 * */
template< typename T >
void Tree<T>::print_tree()
{ 
    root->Node<T>::print_nodes(print_option, &max_level); 
    cout << this;
    cout << endl;
}

/* node_get(int key, int level, Node<T>* n)
 * 
 * Attempts to acquire an object T with a given key from the repository.
 * Begins at root node at level 0 (passed in by MLH_Get).
 * If key is found, returns T.
 * Otherwise, returns NULL (0).
 * */
template< typename T >
T* Tree<T>::node_get(int key, int level, Node<T>* n)
{    
    if((n != NULL) && (n->is_stem()))
    {
        int index = ML_hash(level + 1, key) - 1;
        num_steps++;
        return node_get(key, level + 1, n->children[index]);
    }
    else if(n != NULL)
    {
        for(int i = 0; i < RANGE; i++)
        {
            if(n->keys[i] == key)
                return n->data[i];
            num_steps++;
        }
    }
    return NULL;
}

/* MLH_Get(int key)
 *
 * Calls node_get.
 * Exists to allow user to only input key, and to gain access to private variable root.
 * */
template< typename T >
T* Tree<T>::MLH_Get(int key)
{
    return node_get(key, 0, root);
}

/* node_insert(int key, T* data, int level, Node<T>* n)
 *
 * Attempts to insert an object T with key "key" into the repository.
 * Begins at root node at level 0 (passed in b MLH_Insert).
 * If successful, returns 1.
 * Otherwise, returns 0.
 * */
template< typename T >
int Tree<T>::node_insert(int key, T* data, int level, Node<T>* n)
{
    //If a stem and not NULL, recurse
    if((n !=  NULL) && (n->is_stem()))
    {
        int index = ML_hash(level + 1, key) - 1;
        num_steps++;
        previous = n;
        return node_insert(key, data, level + 1, n->children[index]);
    }
    //If is full and is not NULL, explode
    else if((n != NULL) && (n->is_full()))
    {
        for(int i = 0; i < RANGE; i++)
        {
            if(n->keys[i] == key)
                return 0;
        num_steps++;
        }
        n->explode(key, data, level, &num_steps, &num_nodes);
        increment_num_keys(n->parent);
        return 1;
    }
    //If parent has null pointer at children[index], make new node.
    else if(n == NULL)
    {
        int index = ML_hash(level, key) - 1; 
        Node<T>* new_child = new Node<T>();
        new_child->keys[0] = key;
        new_child->data[0] = data;
        new_child->parent = previous;
        num_nodes++;
        previous->children[index] = new_child;
        increment_num_keys(new_child);
        return 1;
    }
    //If child exists, insert into first spot.
    else
    {
        for(int i = 0; i <= n->num_keys; i++)
        {
            if(n->keys[i] == key)
            {
                return 0;
            }
            else if(n->keys[i] == 0)
            {
                n->keys[i] = key;
                n->data[i] = data;
                increment_num_keys(n);
                return 1;
            }
        num_steps++;
        }
    }
    return 0;
}

/* MLH_Insert(int key, T* data)
 *
 * Calls node_insert().
 * Exists to allow the user to only insert desired identification and data.
 * Also has access to the private variable root.
 * */
template< typename T>
int Tree<T>::MLH_Insert(int key, T* data)
{
    return node_insert(key, data, 0, root);
}

/* node_delete(int key, int level, Node<T>* n)
 * 
 * Attempts to remove data with a specific key from the repository.
 * If successful, returns the data to be deleted.
 * Otherwise, returns NULL.
 * */

template< typename T >
T* Tree<T>::node_delete(int key, int level, Node<T>* n)
{
    //If node is not NULL but is stem, recurse
    if((n != NULL) && (n->is_stem()))
    {
        int index = ML_hash(level + 1, key) - 1;
        num_steps++;
        return node_delete(key, level + 1, n->children[index]);
    }
    //If not null and not stem, check for key.
    else if(n != NULL)
    {
        for(int i = 0; i < RANGE; i++)
        {
            if(n->keys[i] == key)
            {
                // Fill hole in key and data arrays
                n->keys[i] = n->keys[n->num_keys - 1];
                T* temp = n->data[i];
                n->data[i] = n->data[n->num_keys - 1];
                n->keys[n->num_keys - 1] = 0;
                n->data[n->num_keys - 1] = NULL;
                decrement_num_keys(n);
                //If the parent is only responsible for 5 keys, collect it.
                if((n->parent != NULL) && (n->parent->num_keys <= 5))
                {
                    n->parent->collect(&num_steps, &num_nodes);
                }
                //If the node is empty after the key is deleted, delete it.
                else if((n != root) && (n->is_empty()))
                {
                    int index = ML_hash(level, key) - 1;
                    n->parent->children[index]= NULL;
                    delete n;
                    n = NULL;
                    num_nodes--;
                }
                return temp;
            }
        num_steps++;
        } 
    }
    return NULL;   
}

/* MLH_Delete(int key)
 *
 * Calls node_delete().
 * Exists to allow the user to only delete data with the given key.
 * Also has access to the private variable root.
 * */
template< typename T >
T* Tree<T>::MLH_Delete(int key)
{
    return node_delete(key, 0, root);
}

/* increment_num_keys(Node<T>* n)
 * 
 * Increases a given string of nodes' num_keys by one.
 * Starts at the given node, and traverses each parent to update num_keys.
 * Stops at root (root's parent == NULL)
 * */
template< typename T >
void Tree<T>::increment_num_keys(Node<T>* n)
{
    Node<T>* pnode = n;
    while(pnode != NULL)
    {
        pnode->num_keys++;
        pnode = pnode->parent;
    }
}

/* decrement_num_keys(Node<T>* n)
 * 
 * Decreases of a given string of nodes' num_keys by one.
 * Starts at the given node, and traverses each parent to update num_keys.
 * Stops at root (root's parent == NULL)
 * */
template< typename T >
void Tree<T>::decrement_num_keys(Node<T>* n)
{
    Node<T>* pnode = n;
    while(pnode != NULL)
    {
        pnode->num_keys--;
        pnode = pnode->parent;
    }
}

/* MLH_set_print_option(int num)
 *
 * Sets print_option to the given number.
 * */
template< typename T >
void Tree<T>::MLH_set_print_option(int num)
{
    print_option = num;
}

/* destroy_tree(Node<T>* n)
 *
 * Starts at n and calls itself on n's children. This spans the entire tree
 * starting from a given point.
 * Deletes the data in every n before deleting n itself.
 * */
template< typename T >
void Tree<T>::destroy_tree(Node<T>* n)
{
    if(n == NULL)
    return ;
    if(n->is_stem())
    {
        for(int i = 0; i < RANGE; i++)
            destroy_tree(n->children[i]);
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

/* Destructor, ~Tree()
 *
 * Calls destroy_tree on the root. Effectively deletes all nodes in the tree 
 * */
template< typename T >
Tree<T>::~Tree()
{
    destroy_tree(root);
}

#endif /* TREE_H */
