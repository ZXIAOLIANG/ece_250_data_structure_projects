#include <iostream>
#include "Double_sentinel_list.h"

// Every C++ Project in Visual Studio and other IDEs can only have one file with a main() function.
// Thus, if you want this to compile, you must change the name to 'main()' and change the name of
// the 'main()' function in the driver to something else.
int main() {
	Double_sentinel_list<int> list;
	int *i = 0;

	std::cout << "The list should be empty (1): " << list.empty() << std::endl;
	std::cout << "The size should be 0: " << list.size() << std::endl;
	std::cout << "The next pointer of begin should be the null pointer: " << list.begin()->next() << std::endl;
	std::cout << "The begin should equal end: " << (list.begin() == list.end()) << std::endl;
	std::cout << "counter: " << list.count(*i) << std::endl;
	//std::cout << "exception: " << list.front() << std::endl;

	list.push_front( 5 );

	std::cout << "The value of the node returned by begin should be 5: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 5: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 5: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 5: " << list.back() << std::endl;

	Double_sentinel_list<int>::Double_node *node = list.find(7);
	std::cout << "The value of the node returned by find(): " << node->node_value << std::endl;


	list.push_front( 7 );
	std::cout << "The value of the node returned by begin should be 7: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 5: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 5: " << list.back() << std::endl;
	std::cout << "counter: " << list.count(5) << std::endl;

	list.push_back(7);
	std::cout << "erase() returned: " << list.erase(7);
	//Double_sentinel_list<int>::Double_node *node2 = list.find(7);
	//Double_sentinel_list<int>::Double_node *node3 = list.find(5);
	//std::cout << "The value of the node returned by find()2: " << node2->node_value << std::endl;
	//std::cout << "The value of the node returned by find()3: " << node3->node_value << std::endl;

	list.push_back(8);
	std::cout << "The value of the node returned by begin should be 7: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 7: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 7: " << list.back() << std::endl;
    std::cout << "counter: " << list.count(7) << std::endl;

	Double_sentinel_list<int> list2 = Double_sentinel_list<int>(list);

	std::cout <<  std::endl;
	std::cout << "The value of the node returned by begin should be 7: " << list2.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list2.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 7: " << list2.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 7: " << list2.back() << std::endl;
    std::cout << "counter: " << list2.count(7) << std::endl;

	std::cout <<  std::endl;
	std::cout << "The value of the node returned by begin should be 7: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 7: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 7: " << list.back() << std::endl;
    std::cout << "counter: " << list.count(7) << std::endl;

	Double_sentinel_list<int> list3 = Double_sentinel_list<int>(std::move(list));
	std::cout <<  std::endl;
	std::cout << "after move!" << std::endl;
	std::cout << "The value of the node returned by begin should be 7: " << list3.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list3.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 7: " << list3.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 7: " << list3.back() << std::endl;
    std::cout << "counter: " << list3.count(7) << std::endl;

	std::cout <<  std::endl;
	std::cout << "The value of the node returned by begin should be 7: " << list.begin()->value() << std::endl;
	std::cout << "The value of the front should be 7: " << list.front() << std::endl;
	std::cout << "The value of the node returned by rbegin should be 7: " << list.rbegin()->value() << std::endl;
	std::cout << "The value of the back should be 7: " << list.back() << std::endl;
    std::cout << "counter: " << list.count(7) << std::endl;




	return 0;
}
