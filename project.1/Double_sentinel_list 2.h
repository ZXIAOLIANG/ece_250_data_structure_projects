/*****************************************
 * UW User ID:  j795wang
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
public:
    class Double_node {
    public:
        Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );
        
        Type value() const;
        Double_node *previous() const;
        Double_node *next() const;
        
        Type         node_value;
        Double_node *previous_node;
        Double_node *next_node;
    };
    
    Double_sentinel_list();
    Double_sentinel_list( Double_sentinel_list const & );
    Double_sentinel_list( Double_sentinel_list && );
    ~Double_sentinel_list();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    Type front() const;
    Type back() const;
    
    Double_node *begin() const;
    Double_node *end() const;
    Double_node *rbegin() const;
    Double_node *rend() const;
    
    Double_node *find( Type const & ) const;
    int count( Type const & ) const;
    
    // Mutators
    
    void swap( Double_sentinel_list & );
    Double_sentinel_list &operator=( Double_sentinel_list );
    Double_sentinel_list &operator=( Double_sentinel_list && );
    
    void push_front( Type const & );
    void push_back( Type const & );
    
    void pop_front();
    void pop_back();
    
    int erase( Type const & );
    
private:
    Double_node *list_head;
    Double_node *list_tail;
    int list_size;
    //int nvalue_same_argu = 0;
    
    
    // List any additional private member functions you author here
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head(nullptr),
list_tail(nullptr),
list_size( 0 )
{
    Double_node *head_sentinel = new Double_node();
    Double_node *tail_sentinel = new Double_node();
    list_head = head_sentinel;
    list_tail = tail_sentinel;
    
    list_head -> previous_node = nullptr;
    list_head -> node_value = 0;
    list_head -> next_node = list_tail;
    
    list_tail -> next_node = nullptr;
    list_tail -> node_value = 0;
    list_tail ->previous_node = list_head;
    
    list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *head_sentinel = new Double_node();
    Double_node *tail_sentinel = new Double_node();
    list_head = head_sentinel;
    list_tail = tail_sentinel;
    
    list_head -> previous_node = nullptr;
    list_head -> node_value = 0;
    list_head -> next_node = list_tail;
    
    list_tail -> next_node = nullptr;
    list_tail -> node_value = 0;
    list_tail ->previous_node = list_head;
    
    Double_node *tmp = list.list_head -> next_node;
    for(int i = 0; i < list.list_size; i++)
    {
        this -> push_back(tmp -> node_value);
        tmp = tmp -> next_node;
        //this->list_size++;
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    Double_node *head_sentinel = new Double_node();
    Double_node *tail_sentinel = new Double_node();
    list_head = head_sentinel;
    list_tail = tail_sentinel;
    
    list_head -> previous_node = nullptr;
    list_head -> node_value = 0;
    list_head -> next_node = list_tail;
    
    list_tail -> next_node = nullptr;
    list_tail -> node_value = 0;
    list_tail ->previous_node = list_head;
    
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    while(!this -> empty())
    {
        this -> pop_front();
    }
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    
    return this->list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    
    if(list_head -> next_node == list_tail){
        return true;
    }else{
        return false;
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    //std::cout << "empty or die: " << this->empty() << std::endl;
    
    if(!this -> empty())
    {
        //std::cout << "empty!" << std::endl;
        return this -> begin() -> node_value ; // This returns the value of first Node
    }else{
        throw underflow();
    }
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    
    if(!this -> empty())
    {
        return this -> rbegin() -> node_value ; // This returns the value of last Node
    }else{
        throw underflow();
    }
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    
    return list_head ->next_node; //This returns the address of the first Node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    
    return list_tail; //This returns the address of the tail sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    
    return list_tail -> previous_node; //This returns the address of the last Node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    
    return list_head; //This returns the address of the head sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    
    for (                              // Returns the address of the first Node if there exists a value equals to the argument
         Double_node *ptr = list_head;
         ptr != 0;
         ptr = ptr -> next()
         ){
        if (ptr -> node_value == obj)
        {
            return this -> begin();
        }
    }
    //Otherwise returns end()
    return this -> end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    int counter = 0;
    for (        					// Returns the number of Nodes storing same value equal to the argument
         Double_node *ptr = this->begin();
         ptr != this->end();
         ptr = ptr -> next()
         ){
        if (ptr -> node_value == obj)
        {
            counter++;
        }
    }
    return counter;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    // This is done for you
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
    // This is done for you
    swap( rhs );
    
    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
    
    Double_node *tmp = new Double_node();
    tmp -> node_value = obj;
    tmp -> next_node = this -> begin(); //This stores a pointer that points to the first Node
    this -> begin() -> previous_node = tmp;
    tmp -> previous_node = this -> rend(); //This stores a pointer that points to the head sentinel
    this -> list_head -> next_node = tmp;
    this->list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
    Double_node *tmp = new Double_node();
    tmp -> node_value = obj;
    tmp -> next_node = this -> end(); //This stores a pointer that points to the tail sentinel
    tmp -> previous_node = this -> end()-> previous() ; //This stores a pointer that points to the last Node
    this -> list_tail -> previous() -> next_node = tmp;
    this -> end() -> previous_node = tmp;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
    if(!this->empty())
    {
        this -> rend() -> next_node = this -> begin() -> next_node; // Sync the Next pointer of the first Node
        // to the Next pointer of head sentinel
        delete this -> begin()->previous(); // This deletes the first Node after the head sentinel
        this -> begin() -> previous_node = this -> rend(); // Make the prev. pointer of the second Node
        // to be the address of the head sentinel
        list_size--;
    }else{
        throw underflow();
    }
    
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
    if(! this -> empty())
    {
        this -> list_tail -> previous_node = this -> list_tail -> previous_node -> previous_node; //
        delete this -> list_tail -> previous_node -> next_node; // This deletes the last Node before the tail sentinel
        this -> list_tail -> previous_node -> next_node = this -> list_tail ; //
        list_size--;
    }else{
        throw underflow();
    }
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    //Double_node *tmp = 0;
    int counter=0;
    for (        					// Returns the number of Nodes storing same value equal to the argument
         Double_node *ptr = this->begin();
         ptr != this->end();
         ){
        if (ptr -> node_value == obj)
        {
            Double_node *tmp = ptr;
            ptr -> previous_node -> next_node = ptr -> next_node;
            ptr -> next_node -> previous_node = ptr -> previous_node;
            ptr = ptr -> next();
            delete tmp;
            counter++;
            list_size--;
        }else{
            ptr = ptr -> next();
        }
    }
    return counter;
}


template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
                                                     Type const &nv,
                                                     typename Double_sentinel_list<Type>::Double_node *pn,
                                                     typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
    node_value = nv;
    previous_node = pn;
    next_node = nn;
    
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
    
    return this -> node_value; // This returns a value of Node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
    
    return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
    
    return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";
    
    for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.rend() || ptr == list.end() ) {
            out << "->S";
        } else {
            out << "->" << ptr->value();
        }
    }
    
    out << "->0" << std::endl << "tail";
    
    for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
        if ( ptr == list.rend() || ptr == list.end() ) {
            out << "->S";
        } else {
            out << "->" << ptr->value();
        }
    }
    
    out << "->0";
    
    return out;
}

#endif
