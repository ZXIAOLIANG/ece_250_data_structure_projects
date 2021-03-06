/*************************************************
 * Search_tree_tester
 * A class for testing search trees.
 *
 * Author:  Douglas Wilhelm Harder
 * Copyright (c) 2006-8 by Douglas Wilhelm Harder.  All rights reserved.
 *
 * DO NOT EDIT THIS FILE
 *************************************************/

#ifndef SEARCH_TREE_TESTER_H
#define SEARCH_TREE_TESTER_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "Tester.h"
#include "Search_tree.h"
#include "Search_tree_iterator_tester.h"

#include <iostream>
#include <cmath>

template <typename Type>
class Search_tree_tester:public Tester< Search_tree<Type> > {
	using Tester< Search_tree<Type> >::object;
	using Tester< Search_tree<Type> >::command;

	public:
		Search_tree_tester( Search_tree<Type> *obj = 0 ):Tester< Search_tree<Type> >( obj ) {
			// empty
		}

		void process();
};

/****************************************************
 * void process()
 *
 * Process the current command.  For search trees, these include:
 *
 *  Constructors
 *
 *   new             constructor     create a new empty search tree
 *   delete          destructor      remove a search tree from memory
 *
 *  Accessors
 *
 *   size n          size            the size equals n
 *   height n        height          the height equals n
 *   empty b         empty           the result is the Boolean value b
 *   front n         front           n is the first element in the search tree
 *   front!          front           the underflow exception is thrown
 *   back n          back            n is the last element in the search tree
 *   back!           back            the underflow exception is thrown
 *
 *  Iterators
 * 
 *   begin           begin           begin is not 'nullptr' and starts a Search_tree_Search_tree_iterator_tester on that
 *                                   iterator until the 'exit' command is typed
 *   end             end             end is not 'nullptr' and starts a Search_tree_Search_tree_iterator_tester on that
 *                                   iterator until the 'exit' command is typed
 *   rbegin          rbegin          rbegin is not 'nullptr' and starts a Search_tree_Search_tree_iterator_tester on that
 *                                   iterator until the 'exit' command is typed
 *   rend            rend            rend is not 'nullptr' and starts a Search_tree_Search_tree_iterator_tester on that
 *                                   iterator until the 'exit' command is typed
 *   find n          find            finds the first node containing the value n and starts a
 *                                   Search_tree_Search_tree_iterator_tester on its iterator until the 'exit' command is typed
 * 
 *  Mutators
 *
 *   insert n b   	insert      insert element and checks boolean output
 *   erase n b    	erase      deletes element and checks boolean output
 *   clear    		clear      clears everything
 *
 *  Others
 *
 *   summary                         prints the amount of memory allocated
 *                                   minus the memory deallocated
 *   details                         prints a detailed description of which
 *                                   memory was allocated with details
 *   !!                              use the previous command, e.g.  5 push_front 3
 *                                                                   6 !! 7         // same as push_front 7
 *   !n                              use the command used in line n  7 front 7
 *                                                                   8 !7 9         // same as push_front 9
 *
 ****************************************************/

template <typename Type>
void Search_tree_tester<Type>::process() {
	if ( command == "new" ) {
		object = new Search_tree<Type>();
		std::cout << "Okay" << std::endl;
	} else if ( command == "size" ) {
		// check if the size equals the next entry read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if ( actual_size == expected_size ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	} else if ( command == "height" ) {
		// check if the capacity equals the next entry read

		int expected_capacity;

		std::cin >> expected_capacity;

		int actual_capacity = object->height();

		if ( actual_capacity == expected_capacity ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in height(): expecting the value '" << expected_capacity << "' but got '" << actual_capacity << "'" << std::endl;
		}
	} else if ( command == "empty" ) {
		// check if the empty status equals the next Boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if ( actual_empty == expected_empty ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	} else if ( command == "front" ) {
		// checks if the first entry in the deque equals the next entry read

		Type expected_front;

		std::cin >> expected_front;

		Type actual_front = object->front();

		if ( actual_front == expected_front ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in front(): expecting the value '" << expected_front << "' but got '" << actual_front << "'" << std::endl;
		}
	} else if ( command == "front!" ) {
		// front of an empty deque - catch an exception

		Type actual_front;

		try {
			actual_front = object->front();
			std::cout << "Failure in front(): expecting to catch an exception but got '" << actual_front << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in front(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "back" ) {
		// checks if the last entry in the deque equals the next entry read

		Type expected_back;

		std::cin >> expected_back;

		Type actual_back = object->back();

		if ( actual_back == expected_back ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in back(): expecting the value '" << expected_back << "' but got '" << actual_back << "'" << std::endl;
		}
	} else if ( command == "back!" ) {
		// front of an empty deque - catch an exception

		Type actual_back;

		try {
			actual_back = object->back();
			std::cout << "Failure in back(): expecting to catch an exception but got '" << actual_back << "'" << std::endl;
		} catch( underflow ) {
			std::cout << "Okay" << std::endl;
		} catch (...) {
			std::cout << "Failure in back(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	} else if ( command == "begin" ) {
		std::cout << "Okay" << std::endl;
		auto begin_iterator = object->begin();
		Search_tree_iterator_tester<Type> tester(object, &begin_iterator );
		tester.run();
	} else if ( command == "end" ) {
		std::cout << "Okay" << std::endl;
		auto end_iterator = object->end();
		Search_tree_iterator_tester<Type> tester(object, &end_iterator );
		tester.run();
	} else if ( command == "rbegin" ) {
		std::cout << "Okay" << std::endl;
		auto rbegin_iterator = object->rbegin();
		Search_tree_iterator_tester<Type> tester(object, &rbegin_iterator );
		tester.run();
	} else if ( command == "rend" ) {
		std::cout << "Okay" << std::endl;
		auto rend_iterator = object->rend();
		Search_tree_iterator_tester<Type> tester(object, &rend_iterator );
		tester.run();
	}
	else if (command == "loop"){
		Type val;
		for (auto i=object->begin(); i!=object->end(); ++i){
			std::cin >> val;
			if (*i != val){
				std::cout << "Failure in loop: expected to find " << val << " but got " << *i << " instead." << std::endl;
			}
		}
		std::cout << "Okay" << std::endl;
	}
	else if (command == "rloop"){
		Type val;
		for (auto i=object->rbegin(); i!=object->rend(); --i){
			std::cin >> val;
			if (*i != val){
				std::cout << "Failure in rloop: expected to find " << val << " but got " << *i << " instead." << std::endl;
			}
		}
		std::cout << "Okay" << std::endl;
	}
	else if (command == "perfect"){
		int height;
		std::cin >> height;
		for (int i=1; i < 1<<(height+1); i++){
			object->insert(i);
		}
		std::cout << "Okay" << std::endl;
	}
	else if (command == "rperfect"){
		int height;
		std::cin >> height;
		for (int i = (1<<(height+1))-1; i>0; i--){
			object->insert(i);
		}
		std::cout << "Okay" << std::endl;
	}
	else if ( command == "find" ) {
		Type value;
		std::cin >> value;

		std::cout << "Okay" << std::endl;
		auto found_item_iterator = object->find( value );
		Search_tree_iterator_tester<Type> tester(object, &found_item_iterator );
		tester.run();

	} else if ( command == "insert" ) {
		// push the next entry read to the front of the deque

		Type obj;
		bool expected_insert;
		bool actual_insert;

		std::cin >> obj;
		std::cin >> expected_insert;

		actual_insert = object->insert( obj );

		if ( actual_insert == expected_insert ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in insert(): expecting the response '" << expected_insert << "' but got '" << actual_insert << "'" << std::endl;
		}
	} else if ( command == "erase" ) {
		// push the next entry read to the front of the deque

		Type obj;
		bool expected_erase;
		bool actual_erase;
		std::cin >> obj;
		std::cin >> expected_erase;

		actual_erase = object->erase( obj );

		if ( actual_erase == expected_erase ) {
			std::cout << "Okay" << std::endl;
		} else {
			std::cout << "Failure in erase(): expecting the response '" << expected_erase << "' but got '" << actual_erase << "'" << std::endl;
		}
	} else if ( command == "clear" ) {
			object->clear();
			std::cout << "Okay" << std::endl;
	} else if ( command == "cout" ) {
		std::cout << *object << std::endl;
	} else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif
