/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  zxiaolia @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		int occupied_count; //counter for occupied bins
		int unoccupied_count; //counter for unoccupied bins
		int erased_count; //counter for erased bins
		Type *array;
		bin_state_t *occupied;

		int hash( Type const & ) const;

	public:
		Quadratic_hash_table( int = 5 );
		~Quadratic_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool erase( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Quadratic_hash_table<T> const & );
};

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table( int m ):
count( 0 ), power(),
array_size(),
mask(),
array(),
occupied_count(),
unoccupied_count(),
erased_count(),
occupied() {
	if(m < 0){
		m = 5;
	}//when m is nagative, set m to 5
	power = m;
	array_size = 1 << power; //array size is 2 to the power of 'power'
	mask = array_size - 1;
	array = new Type[array_size];
	occupied = new bin_state_t[array_size];

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = UNOCCUPIED;
	}
	unoccupied_count = array_size; //initialize unoccupied count to the size of the array
	occupied_count = 0; //initialize occupied count to 0
	erased_count = 0; //initialize erased count to 0
}

//destructor
template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table(){
	delete [] this->array;//delete the array
	delete [] this->occupied;//delete the occupied array
}

template <typename Type>
int Quadratic_hash_table<Type>::size() const{
	//return how many elements in the hashtable
	return this->count; //return count
}

template <typename Type>
int Quadratic_hash_table<Type>::capacity() const{
	//return the capacity of the hashtable
	return this->array_size; //return array size
}

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const{
	// load factor is the number of occupied bins plus the number of erased bins devided by the capacity of the hashtable
	return (static_cast<double>(this->occupied_count) + static_cast<double>(this->erased_count))/static_cast<double>(this->array_size); //we need to cast integers to double in order to generate a double
}

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const{
	//check if the hashtable is empty
	if(this->count == 0){
		//if there is no element in the hashtable return true
		return true;
	}
	else{
		//otherwise return false
		return false;
	}
}

template <typename Type>
bool Quadratic_hash_table<Type>::member( Type const &obj ) const{
	//check if the obj is a member of the hashtable
	int bin = this->hash(obj);//use hash function to get the initial bin
	for(int i = 1; i < this->array_size + 1; ++i){
		if(this->occupied[bin] == OCCUPIED && this->array[bin] == obj){
			//if we find the object, which means the the bin is occupied and the value is object
			return true;
		}
		else if(this->occupied[bin] == UNOCCUPIED){
			//otherwise if the bin is unoccupied, return false, it means the object is not in the hashtable
			return false;
		}
		//based on quadratic probing, check next possible bin (add i to the current bin) 
		bin = (bin + i) % this->array_size;
		
	}
	//we didb't find the object, return false
	return false;

}


template <typename Type>
Type Quadratic_hash_table<Type>::bin( int binNum) const{
	//return the object in the specified bin
	return this->array[binNum];
}


template <typename Type>
void Quadratic_hash_table<Type>::print() const{
	//for debug purpose
	return;
}

//void insert( Type const & );
template <typename Type>
void Quadratic_hash_table<Type>::insert( Type const &obj ){
	// if the array full, throw underflow exception
	if(this->count == this->array_size){
		throw overflow();
	}
	int bin = this->hash(obj);//get the initial bin using the hash function
	for(int i = 1; i < this->array_size+1; ++i){
		if(this->member(obj) == true){
			//if the object already in the hashtable do nothing
			return;
		}
		else if(this->occupied[bin] == UNOCCUPIED){
			//if the bin is unoccupied
			//insert the obj
			this->array[bin] = obj;
			//set the bin to occupied
			this->occupied[bin] = OCCUPIED;
			//modify the counters
			count++;
			occupied_count++;
			unoccupied_count--;
			return;
		}
		else if(this->occupied[bin] == ERASED){
			//if the bin is erased
			//insert the obj
			this->array[bin] = obj;
			//set the bin to occupied
			this->occupied[bin] = OCCUPIED;
			//modify the counters
			count++;
			occupied_count++;
			erased_count--;
			return;
		}
		//based on quadratic probing, check next possible bin (add i to the current bin)
		bin = (bin + i) % this->array_size;
	}
}


template <typename Type>
bool Quadratic_hash_table<Type>::erase( Type const &obj ){
	//this function erase the obj from the hashtable
	int bin = this->hash(obj); //get the initial bin of the obj using hash function
	for(int i = 1; i < this->array_size + 1; ++i){
		if(this->occupied[bin] == OCCUPIED && this->array[bin] == obj){
			//in the bin is occupied and the value of the bin is obj, we erase the obj by setting the bin to ERASED
			this->occupied[bin] = ERASED;
			//modify the counter
			count--;
			occupied_count--;
			erased_count++;
			return true;
		}
		else if(this->occupied[bin] == UNOCCUPIED){
			//obj not in hashtable
			return false;
		}
		//update the bin based on quadratic probing
		bin = (bin + i) % this->array_size;
	}
	//we didn't find the obj in the bin, return false
	return false;
}


template <typename Type>
void Quadratic_hash_table<Type>::clear(){
	//this function clear all elements in the hash table
	for(int i = 0; i < this->array_size; ++i){
		if(this->occupied[i] == OCCUPIED){
			//we clear the bin by setting the bin to unoccupied, when the bin is occupied
			this->occupied[i] = UNOCCUPIED;
			//update counter
			unoccupied_count++;
			occupied_count--;
			count--;
		}
		else if(this->occupied[i] == ERASED){
			//we clear the bin by setting the bin to unoccupied, when the bin is erased
			this->occupied[i] = UNOCCUPIED;
			//update counter
			unoccupied_count++;
			erased_count--;
		}
	}
}


template <typename Type>
int Quadratic_hash_table<Type>::hash( Type const &obj ) const{
	//this is hash function of the hash table
	int cast_value = static_cast<int>(obj); // we first cast the obj to an integer
	int initial_bin  = cast_value % this->array_size; // we get the hash value by module the array_size 
	if(initial_bin < 0){
		// if the hash value is negative, add array_size to it to make it positive
		initial_bin = initial_bin + this->array_size;
	}
	//return the hash value
	return initial_bin;
}




template <typename T>
std::ostream &operator<<( std::ostream &out, Quadratic_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == UNOCCUPIED ) {
			out << "- ";
		} else if ( hash.occupied[i] == ERASED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif