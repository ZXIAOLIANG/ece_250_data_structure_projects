/*****************************************
 * UW User ID:  uwuserid
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
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	//create sentinel nodes
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	this->list_head->next_node = head_sentinel;
	this->list_tail->previous_node = tail_sentinel;
	//store the value of the address of sentinel nodes
	//this->list_head->node_value = head_sentinel;
	//this->list_tail->node_value = tail_sentinel;
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	
}

//copy constructer
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	//create sentinel nodes
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	this->list_head->next_node = head_sentinel;
	this->list_tail->previous_node = tail_sentinel;
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	for ( Double_node *ptr = list.begin(); ptr != list.end(); ptr = ptr->next()) {
		this->push_back(ptr->value());
	}
}

//move constructer
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( new Double_node() ),
list_tail( new Double_node() ),
list_size( 0 )
{
	//create sentinel nodes
	Double_node *head_sentinel = new Double_node();
	Double_node *tail_sentinel = new Double_node();
	this->list_head->next_node = head_sentinel;
	this->list_tail->previous_node = tail_sentinel;
	head_sentinel->next_node = tail_sentinel;
	tail_sentinel->previous_node = head_sentinel;
	//what does rvalue reference do?
	this->swap(list);

}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	while ( !empty() ) {
 		pop_front();
 	}
	delete this->rend();
	delete this->end();
	//do we need to delete head and tail?
	delete this->list_head;
	delete this->list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return this->list_size;
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	if(this->list_size == 0){
		return true;
	}
	else{
		return false;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if(this->empty()){
		//throw exception
		throw underflow::exception();
	}
	else{
		//Retrieves the object stored in the node pointed to by the next pointer of the head sentinel
		return this->list_head->next()->next()->node_value;
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if(this->empty()){
		//throw exception
		throw underflow::exception();
	}
	else{
		//Retrieves the object stored in the node pointed to by the previous pointer of the tail sentinel
		return this->list_tail->previous()->previous()->node_value;
	}
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	//return the next node of head sentinel node
	return this->list_head->next()->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	//return the address of the tail sentinel node
	return this->list_tail->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	//Returns the value of the previous pointer of the tail sentinel node.	
	return this->list_tail->previous()->previous();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	//Returns the address of the head sentinel node
	return this->list_head->next();
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	for ( auto *ptr = this->begin(); ptr != this->end(); ptr = ptr->next() ) {
            if(ptr->node_value == obj){
				return ptr;
			}
        }
	return this->end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	int counter = 0;
	for ( auto *ptr = this->begin(); ptr != this->end(); ptr = ptr->next() ) {
            if(ptr->node_value == obj){
				++counter;
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
	Double_node *new_node = new Double_node();
	new_node->node_value = obj;
	new_node->next_node = this->begin();
	new_node->previous_node = this->rend();
	this->rend()->next_node = new_node;
	this->begin()->next_node->previous_node = new_node;
	++this->list_size;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	Double_node *new_node = new Double_node();
	new_node->node_value = obj;
	new_node->next_node = this->end();
	new_node->previous_node = this->end()->previous();
	this->list_tail->previous()->previous()->next_node = new_node;
	this->end()->previous_node = new_node;
	++this->list_size;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	if(this->empty() == 0){
		this->list_head->next_node->next_node = this->begin()->next();
		delete this->begin()->previous();
		this->begin()->previous_node = this->list_head->next();
		--this->list_size;
	}
	else{
		throw underflow::exception();
	}
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	if(this->empty() == 0){
		this->list_tail->previous_node->previous_node = this->rbegin()->previous();
		delete this->rbegin()->next();
		this->rbegin()->next_node = this->end();
		--this->list_size;
	}
	else{
		throw underflow::exception();
	}
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	int counter = 0;
	while(this->find(obj)!=end()){
		Double_node *pointer = this->find(obj);
		if(pointer != this->end()){
			pointer->previous()->next_node = pointer->next();
			pointer->next()->previous_node = pointer->previous();
			++counter;
			--this->list_size;
		}
		delete pointer;
	}
	// Enter your implementation here
	/*
	int counter = 0;
	for ( auto *ptr = this->begin(); ptr != this->end();) {
            if(ptr->node_value == obj){
				auto *temp = ptr->next();
				std::cout << "ptr address: "<< ptr << std::endl;
				std::cout << "temp address: "<< temp << std::endl;
				//delete the node
				ptr->previous()->next_node = ptr->next();
				ptr->next()->previous_node = ptr->previous();
				delete ptr;
				//auto *ptr = temp;
				ptr = temp;
				//delete temp;
				//std::cout << "temp address: "<< temp; 
				++counter;
				--this->list_size;
			}
			else{
				ptr = ptr->next();
			}
        }*/
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
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return this->node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return this->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
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
