/*****************************************
 * UW User ID:  zxiaolia
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"
#include <iostream>

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables

		//the index of the front object
		int ifront;
		//the index of the back object
		int iback;
		//the number of element in the deque
		int deque_size;
		//the array capacity when initialization
		int initial_array_capacity;
		//the current array capacity
		int array_capacity;
		//A pointer to an instance of Type, Type *array, to be used as an array
		Type *array;

		// Any private member functions

		// the function used to double array size
		void double_deque_capacity();
		// the function used to half array size
		void half_deque_capacity();
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Default Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ):
ifront(0),//set ifront to the index of the first element of the array
iback(),
deque_size(0),
initial_array_capacity(),
array_capacity(),
array()
// Your initalization list
{
	// this is the default constructor, which initialize an empty deque with initial array capacity
	
	// check if the input parameter is greater than 16, if not, then set it to 16
	if(n < 16){
		n = 16;
	}

	this->initial_array_capacity = n;
	this->array_capacity = n;
	//set iback to the index of the last element of the array
	this->iback = this->array_capacity - 1;
	//allocate an empty array with size of n
	array = new Type[initial_array_capacity];
	
	// Enter your implementation here
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque ):
//in the initialization list, copy the value of deque's to current object, except array
ifront(deque.ifront),
iback(deque.iback),
deque_size(deque.deque_size),
initial_array_capacity(deque.initial_array_capacity),
array_capacity(deque.array_capacity),
array()

{
//the copy constructor will copy an existing deque to the current deque

	//allocate a new array with size of the capacity of deque
	array = new Type[this->array_capacity];
	//since in the array only part of the elements are in the deque, we dont need to copy
	//all of them, we only copy the ones in the deque
	//we will have two situations, ifront could be greater than iback,
	//in this case, deque is located at two sides of the array
	if(deque.ifront > deque.iback){
		//copy from 0 to ifront
		for(int i = 0; i < deque.iback + 1; ++i){
			this->array[i] = deque.array[i];
		}
		//copy from iback to the end of the array
		for(int i = deque.ifront; i < deque.array_capacity; ++i){
			this->array[i] = deque.array[i];
		}
	}
	// or ifront is smaller than iback, in this case, deque is not separated in the array
	else{
		//copy from ifront to iback
		for(int i = deque.ifront; i < deque.iback + 1; ++i){
			this->array[i] = deque.array[i];
		}
	}
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque ):
ifront(0),
iback(),
deque_size(0),
initial_array_capacity(),
array_capacity(),
array()

{
	//the move constructor will move an existing deque to the current deque

	//create an empty deque with capacity 15
	this->initial_array_capacity = 16;
	this->array_capacity = 16;
	this->iback = this->array_capacity - 1;
	array = new Type[initial_array_capacity];
	//use swap to move the deque
	this->swap(deque);

}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	//delete the array to deallocate memory
	delete [] this->array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// return the size of the deque
	return this->deque_size;;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// return the current capacity of the deque
	return this->array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// return true if the size of the array is 0, otherwise return false
	if(this->size() == 0){
		return true;
	}
	else{
		return false;
	}
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// if deque is empty, throw an underflow exception, otherwise return the element in the array of the index of ifront
	// which is the first element in the deque
	if ( this->empty() ) {
        throw underflow();
    }
	return this->array[this->ifront];
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// if deque is empty, throw an underflow exception, otherwise return the element in the array of the index of ifront
	// which is the last element in the deque
	if ( this->empty() ) {
        throw underflow();
    }
	return this->array[this->iback];
	
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );
	
	// swap the member variables of deque with the current object
	std::swap(this->ifront, deque.ifront);
	std::swap(this->iback, deque.iback);
	std::swap(this->deque_size, deque.deque_size);
	std::swap(this->initial_array_capacity, deque.initial_array_capacity);
	std::swap(this->array_capacity, deque.array_capacity);
	std::swap(this->array, deque.array);
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}


template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// this function push an element to the front of the deque, double the array capacity if the array is full
	
	// check whether the array is full, if so, double the capacity
	if(this->deque_size == this->array_capacity){
		this->double_deque_capacity();
	}
	// increment the deque size
	++this->deque_size;
	
	//move ifront 1 index left
	--this->ifront;
	//if ifront is -1. set ifront to the last index of array
	if (this->ifront < 0) {
		this->ifront = this->array_capacity - 1;
	}
	//set the value of index ifront to obj
	this->array[this->ifront] = obj;

}


template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
	// this function push an element to the back of the deque, double the array capacity if the array is full
	
	// check whether the array is full, if so, double the capacity
	if(this->deque_size == this->array_capacity){
		this->double_deque_capacity();
	}
	//increment the deque size
	++this->deque_size;

	//move iback one index right
	++this->iback;
	//if iback is equal to the array capacity, set iback to 0
	if (this->iback == this->array_capacity) {
	    this->iback = 0;
	}
	//set the value of index iback to obj
	this->array[this->iback] = obj;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	//this function remove the first element int the deque, half the array size if the deque size if 1/4 of array capacity
	
	//check if the deque is empty, if so, throw an underflow exception
	if ( this->empty() ) {
        throw underflow();
    }
	//decrement the deque size
	--this->deque_size;
	//move ifront 1 index right, so the first element doesn't exist in the deque, but we can remain the value in the array
	++this->ifront;
	//if ifront is equal to the array capacity, set it to 0
	if (this->ifront == this->array_capacity) {
	    this->ifront = 0;
	}
	//check if deque is 1/4 of array capacity, and current array capcaity is greater than the initial array capacity, if so, half the array capacity
	if(this->deque_size == (this->array_capacity/4) && this->array_capacity > this->initial_array_capacity){
		this->half_deque_capacity();
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
	//this function remove the last element int the deque, half the array size if the deque size if 1/4 of array capacity
	
	//check if the deque is empty, if so, throw an underflow exception
	if ( this->empty() ) {
        throw underflow();
    }
	//decrement the deque size
	--this->deque_size;
	//move iback 1 index left, so the last element doesn't exist in the deque, but we can remain the value in the array
	--this->iback;
	//check if iback smaller than 0, or we can say iback is -1. if so, set iback the the last index in the array
	if(this->iback < 0){
		this->iback = this->array_capacity - 1;
	}
	//check if deque is 1/4 of array capacity, and current array capcaity is greater than the initial array capacity, if so, half the array capacity
	if(this->deque_size == (this->array_capacity/4) && this->array_capacity > this->initial_array_capacity){
		this->half_deque_capacity();
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	//this function delete all the element in the deque

	//calling pop the last element continuously until the deque is empty
	while(!this->empty()){
		this->pop_back();
	}
	//reinitialize ifront and iback
	this->ifront = 0;
	this->iback = this->array_capacity - 1;
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here
template <typename Type>
void Resizable_deque<Type>::double_deque_capacity(){
	//this function double the array capacity by allocating a new array of doubled size and copying the values
	
	//double the array capacity value
	this->array_capacity *= 2; 
	//assign a new array with doubled size
	Type *temp_array = new Type[this->array_capacity]; 

	if(this->ifront < this->iback){
		//if ifront is to the left of iback, move the element within ifront and iback to the start of the array
		for(int i = this->ifront; i < this->iback + 1; ++i){
			temp_array[i] = this->array[i];
		}
		//since if the array is full and ifront smaller than iback, ifront must be 0, iback must at the end of the array, so we dont need to move them
	}
	else{
		//if ifront is to the right of iback, 
		//copy the elements from ifront to the end of the array to the end of the new array
		for(int i = this->ifront; i < this->array_capacity/2; ++i){
			temp_array[i + this->array_capacity/2] = this->array[i];
		}
		//copy the elements from 0 to iback to the start of the array
		for(int i = 0; i < this->iback + 1; ++i){
			temp_array[i] = this->array[i];
		}
		//set ifront to the right position by add half of the array capaity to it
		this->ifront += this->array_capacity/2; 
		//we dont need to move iback in this case
	}
	//delete the old array
	delete [] this->array;
	//assign the temp array to current array
	this->array = temp_array;

}


template <typename Type>
void Resizable_deque<Type>::half_deque_capacity(){
	//this functoin half the array capacity by allocating a new array with halved size and copy the values

	//half the array capacity value
	this->array_capacity = this->array_capacity/2;
	//assign a new array of halved size
	Type *temp_array = new Type[this->array_capacity];
	//check if ifront to the left of iback or to the right of iback
	if(this->ifront < this->iback){
		//if ifront is to the left of iback, move the element within ifront and iback to the start of the array
		for(int i = this->ifront; i < this->iback + 1; ++i){
			temp_array[i - this->ifront] = this->array[i];
		}
		//set ifront to 0
		this->iback = this->iback - this->ifront;
		this->ifront = 0;
	}
	else{
		//if ifront is to the right of iback, 
		//copy the elements from ifront to the end of the array to the end of the new array
		for(int i = this->ifront; i < 2 * this->array_capacity; ++i){
			temp_array[i - this->array_capacity] = this->array[i];
		}
		//copy the elements from 0 to iback to the start of the array
		for(int i = 0; i < this->iback + 1; ++i){
			temp_array[i] = this->array[i];
		}
		//set ifront to the right position by subtract the array capaity to it
		this->ifront -= this->array_capacity; 
		//we dont need to move iback in this case
	}
	//delete the old array
	delete [] this->array;
	//assign the temp array to current array
	this->array = temp_array;

}


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
