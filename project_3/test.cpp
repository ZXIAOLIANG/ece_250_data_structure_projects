#include <iostream>
#include "Search_tree.h"

int main() {
	Search_tree<int> tree;
	//std::cout << "Height:  " <<std::endl;

	for ( int i = 1; i <= 30; ++i ) {
		std::cout << "hey" <<i<< std::endl;
		std::cout << tree.insert( i );
	}
	std::cout << "yoo"<< std::endl;
	
	tree.erase(7);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(8);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(10);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(11);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(16);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(19);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(20);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(22);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(24);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(26);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(28);
	std::cout << "Height1:  " << tree.height() << std::endl;
	tree.erase(29);
	std::cout << "Height2:  " << tree.height() << std::endl;
	tree.erase(13);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(15);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(5);
	std::cout << "Height3:  " << tree.height() << std::endl;
	
	tree.erase(12);
	std::cout << "Height3:  " << tree.height() << std::endl;
	
	tree.erase(9);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(1);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(2);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(3);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(14);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(17);
	std::cout << "Height3:  " << tree.height() << std::endl;
	tree.erase(18);
	std::cout << "Height3:  " << tree.height() << std::endl;
	
	tree.clear();
	tree.clear();

	for ( int i = 1; i <= 10; ++i ) {
		std::cout << tree.insert( i );
	}

	tree.erase(7);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(8);
	std::cout << "Height:  " << tree.height() << std::endl;
	tree.erase(2);
	std::cout << "Height:  " << tree.height() << std::endl;

	tree.clear();
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	std::cout << "Heightjjj:  " << tree.height() << std::endl;
	tree.insert(5);
	std::cout << "Heightjjj:  " << tree.height() << std::endl;
	tree.insert(4);
	std::cout << "Heightjjj:  " << tree.height() << std::endl;
	tree.clear();
	tree.insert(5);
	tree.insert(6);
	tree.insert(3);
	std::cout << "Heightkkk:  " << tree.height() << std::endl;
	tree.insert(1);
	std::cout << "Heightkkk:  " << tree.height() << std::endl;
	tree.insert(2);
	std::cout << "Heightkkk:  " << tree.height() << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "Front:   " << tree.front()   << std::endl;
	std::cout << "Back:    " << tree.back()    << std::endl;
	std::cout << "Height:  " << tree.height()  << " <- this will change for an AVL tree" << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	std::cout << "--> ";

	for ( Search_tree<int>::Iterator itr = tree.rbegin(); itr != tree.rend(); --itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	tree.clear();

	std::cout << "--> ";
	

	for ( Search_tree<int>::Iterator itr = tree.begin(); itr != tree.end(); ++itr ) {
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	return 0;
}