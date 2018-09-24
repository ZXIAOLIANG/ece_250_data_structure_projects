/*****************************************
 * UW User ID:  zxiaolia
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2018
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

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

//default constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),//initialize the list head to null pointer
list_tail( nullptr ),//initialize the list tail to null pointer
list_size( 0 )//initialize the list size to 0
{
	//this is the default constructor which create an empty list
	//create head sentinel and tail sentinel nodes
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	//point list_head and list_tail to the sentinel nodes respectively
	this->list_head = head_sentinel;
	this->list_tail = tail_sentinel;
	//initialize an empty list, connect head sentinel and tail sentinel
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	
}

//copy constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),//initialize the list head to null pointer
list_tail( nullptr ),//initialize the list tail to null pointer
list_size( 0 )//initialize the list size to 0
{
	//this is the copy constructor, which copy over an existing list to a new list, and doesn't change the value of the old list
	//construct an empty list
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	this->list_head = head_sentinel;
	this->list_tail = tail_sentinel;
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	//iterate through list that passed in, copy every actual node to the list newly created
	for ( Double_node *ptr = list.begin(); ptr != list.end(); ptr = ptr->next()) {
		this->push_back(ptr->value());//using push_back to ensure the order remains the same
	}
}

//move constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),//initialize the list head to null pointer
list_tail( nullptr ),//initialize the list tail to null pointer
list_size( 0 )//initialize the list size to 0
{
	// this function is the move constructor, which create a new list and move the given list to the new list, 
	//the distructor of the old will be called afterwards
	//construct an empty list
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	this->list_head = head_sentinel;
	this->list_tail = tail_sentinel;
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	//using swap to move the list/
	this->swap(list);

}

//distructor
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	//this is the distructor of the Double_sentinel_list class, which delete every node in the list, including the head sentinel and tail sentinel
	//when the list is not empty, calling pop_front to remove every actual node
	while ( !empty() ) {
 		pop_front();
 	}
	//remove head sentinel and tail sentinel
	delete this->list_head;
	delete this->list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	//this function check the size of the list
	//return the list size
	return this->list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	//this function check if the list empty
	//if the list size is not equal to 0, which means the list is not empty, return true
	//otherwise, return false
	if(this->list_size == 0){
		//the list is node empty
		return true;
	}
	else{
		//the list is not empty
		return false;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	//this function returns the value of the first actual node in the list
	//if the list is empty return an underflow exception
	if(this->empty()){
		//throw exception
		throw underflow();
	}
	else{
		//Retrieves the object stored in the node pointed to by the next pointer of the head sentinel
		return this->list_head->next()->node_value;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	//this function returns the value of the last actual node of the list
	//if the list is empty return an underflow exception
	if(this->empty()){
		//throw exception
		throw underflow();
	}
	else{
		//Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel
		return this->list_tail->previous()->node_value;
	}
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	//return the next node of head sentinel node
	return this->list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	//return the address of the tail sentinel node
	return this->list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	//Returns the value of the previous pointer of the tail sentinel node.	
	return this->list_tail->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	//Returns the address of the head sentinel node
	return this->list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	// this function is returning the first node containing a certain value, if cannot find it, return head sentinel node
	//using for loop to ietrate through the list, from the first actual node to the last actual node
	for ( auto *ptr = this->begin(); ptr != this->end(); ptr = ptr->next() ) {
			//if the value of the node is equal to the value we want to find, return the node address
            if(ptr->node_value == obj){
				return ptr;//we are returning the first node we find
			}
        }
	//if we didn't find the value in the list, return the tail sentinel node
	return this->end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// this function is to count a certain value in the list
	//initialize the counter to 0
	int counter = 0;
	////using for loop to ietrate through the list, from the first actual node to the last actual node
	for ( auto *ptr = this->begin(); ptr != this->end(); ptr = ptr->next() ) {
			//if the node value is equal to the value we want to count, increment the counter
            if(ptr->node_value == obj){
				//increment counter
				++counter;
			}
        }
	//return the counter value
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
	// this function add a new node to the front of the list
	//create new node
	Double_node *new_node = new Double_node();
	//set the value of the new node
	new_node->node_value = obj;
	//set the next node of the new node to the next node of the head sentinel
	new_node->next_node = this->begin();
	//set the previous node of the new node to head sentinel
	new_node->previous_node = this->rend();
	//set the next node of head sentinel to the new node
	this->rend()->next_node = new_node;
	//set the previous node of the second actual node to the new node
	this->begin()->next_node->previous_node = new_node;
	//increment the list size by 1
	++this->list_size;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// this function add a new node to the end of the list
	//create a new node
	Double_node *new_node = new Double_node();
	//set the value of the new node
	new_node->node_value = obj;
	//set the next node of the new node to tail sentinel
	new_node->next_node = this->list_tail;
	//set the previous node of the new node to the previous node of tail sentinel
	new_node->previous_node = this->list_tail->previous();
	//set the next node of the second last node to the new node
	this->list_tail->previous_node->next_node = new_node;
	//set the previous node of the tail sentinel to the new node
	this->list_tail->previous_node = new_node;
	//increment the list size by 1
	++this->list_size;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	//this function remove the first node of the list when the list is not empty, otherwise throw an underflow exception
	if(this->empty() == 0){
		//set the next node of head sentinel to the second node in the list
		this->list_head->next_node = this->begin()->next();
		// delete the previous node of the second node, which has been assign to begin in the first statement
		delete this->begin()->previous();
		//set the previous node of the new first node to the head sentinel
		this->begin()->previous_node = this->list_head;
		//decrement the list size by 1
		--this->list_size;
	}
	else{
		//throw an underflow exception if the list is empty
		throw underflow();
	}
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	//this function remove the last node of the list when the list is not empty, otherwise throw an underflow exception
	if(this->empty() == 0){
		//set the previous node of the tail sentinel to the second last node
		this->list_tail->previous_node = this->rbegin()->previous();
		//delte the next node of the second last node, which has been assigned to rbegin() in the first statement
		delete this->rbegin()->next();
		//set the next of the new last actual node to tail sentinel
		this->rbegin()->next_node = this->end();
		//decrement the list size by 1
		--this->list_size;
	}
	else{
		//throw an underflow exception if the list is empty
		throw underflow();
	}
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	//this function remove all the node of a certain value obj, and return the number of nodes removed
	//initialize a counter to 0
	int counter=0;
	//create a new node
	Double_node *delete_node = nullptr;
	//using a for loop to iterate the list from the first actual node to the last actual node
	//initialize a new pointer pointed to the first actual node
    for (auto *pointer = this->begin(); pointer != this->end();){
		//check if the value of the node equal to the given value or not
        if (pointer -> node_value == obj)
        {
			//create a new node point to the current pointer that need to be deleted
            delete_node = pointer;
			//set the next node of the previous node of the pointer to the next node of pointer
            pointer -> previous() -> next_node = pointer -> next();
			//set the previous node of the next node of the pointer to the previous node of the pointer
            pointer -> next() -> previous_node = pointer -> previous();
			//point the delete pointer to the current node, before we move the pointer
            delete_node = pointer;
			//point the pointer to the next node before delete the node
            pointer = pointer -> next();
			//delete the current node
            delete delete_node;
			//decrement the list size, since we delete a node
			--this->list_size;
			//increment the counter
            counter++;
        }
		else{
			//simply point the pointer to the next node, if the current node value is not the given value
            pointer = pointer -> next();
        }
    }
	//return the value of counter
	return counter;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),//initialize the previous node to null pointer
next_node( nullptr )//initialize the next node to null pointer
{
	// this is the constructor of Double_node 
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	//return the node value of the current node
	return this->node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	//return the previous node of the current node
	return this->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	//return the next node of the current node
	return this->next_node;
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
