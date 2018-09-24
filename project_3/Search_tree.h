/*****************************************
 * UW User ID:  zxiaolia
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2018
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type() );

				void update_height();

				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );
				//Node *find_leftmost_node(Node *&to_this);
				//Node *find_rightmost_node(Node *&to_this);
		};

		Node *root_node;
		int tree_size;

		// Hint as to how to start your linked list of the nodes in order 
		Node *front_sentinel;
		Node *back_sentinel;

	public:
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;

			// Make the search tree a friend so that it can call the constructor
			friend class Search_tree;
		};

		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Search_tree();
		~Search_tree();

		bool empty() const;
		int size() const;
		int height() const;

		Type front() const;
		Type back() const;

		Iterator begin();
		Iterator end();
		Iterator rbegin();
		Iterator rend();
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
	//connect front sentinel and back sentinel
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	//delete front sentinel and back sentinel
	delete front_sentinel;
	delete back_sentinel;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return ( root_node == nullptr );
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj );
		tree_size = 1;
		//make the front sentinel and back sentinel to connect to the root node at first insertion
		front_sentinel->next_node = root_node;
		root_node->previous_node = front_sentinel;
		root_node->next_node = back_sentinel;
		back_sentinel->previous_node = root_node;
		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		++tree_size;
		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		--tree_size;
		return true;
	} else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {
	// does nothing
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return ( right_tree == nullptr ) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			left_tree = new Search_tree<Type>::Node( obj );
			//implement the iterator: connect the previous node and next node of each node
			//insert the left_tree between the previous node of current node and current node
			left_tree->next_node = this;
			left_tree->previous_node = this->previous_node;
			this->previous_node->next_node = left_tree;
			this->previous_node = left_tree;

			update_height();

			return true;
		} else {
			if ( left_tree->insert( obj, left_tree ) ) {
				update_height();
				//after update height, we check if the node is balanced, to see if the difference between its right tree height and its left tree height is equal to 2  
				if(this->left_tree->height() - this->right_tree->height() == 2){
					//determine if it is left left or left right
					if(obj > this->left_tree->node_value){//check if the obj is added to the right tree of the left tree of the current node
						
						//left right case, double rotation

						//create node b as the left tree of current node
						Search_tree<Type>::Node *b = this->left_tree;
						//create node d as the right tree of b
						Search_tree<Type>::Node *d = b->right_tree;
						//save the left tree of d as DL
						Search_tree<Type>::Node *DL = d->left_tree;
						//sve the right tree of d as DR
						Search_tree<Type>::Node *DR = d->right_tree;
						//promote d to the current node:
						//move DR to the left tree of the current node
						this->left_tree = DR;
						//move DL to the right tree of b
						b->right_tree = DL;
						//move bto the left tree of d
						d->left_tree = b;
						//move the current node to the right tree of d
						d->right_tree = this;
						//set to_this to d, in order to promote d
						to_this = d;
						//after all the rotation, update the height for b, current node and d, make sure d is updated lastly
						b->update_height();
						this->update_height();
						d->update_height();
					}
					else{
						//left left case, single rotation

						//save the left tree of the current node to b
						Search_tree<Type>::Node *b = this->left_tree;
						//save b's right tree to BR
						Search_tree<Type>::Node *BR = b->right_tree;
						//promote b to the current node
						//move current to the right tree of b 
						b->right_tree = this;
						//set to_this to b, in order to promote b
						to_this = b;
						//move BR ot the left tree of the current node
						this->left_tree = BR;
						//after all the rotation, update the height of the current node and b, make sure b is updated lastly
						this->update_height();
						b->update_height();
					}
				}
				
				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			right_tree = new Search_tree<Type>::Node( obj );
			right_tree->previous_node = this;
			right_tree->next_node = this->next_node;
			this->next_node->previous_node = right_tree;
			this->next_node = right_tree;
			update_height();

			return true;
		} else {
			if ( right_tree->insert( obj, right_tree ) ) {
				update_height();
				if(this->right_tree->height() - this->left_tree->height() == 2){
					//determine if it is right right or right left
					if(obj < this->right_tree->node_value){//check if the obj is added to the left tree of the right tree of the current node or not 
						//right left case

						//save the right tree of the current node to b
						Search_tree<Type>::Node *b = this->right_tree;
						//save the left tree of b to d
						Search_tree<Type>::Node *d = b->left_tree;
						//save the left tree of d to DL
						Search_tree<Type>::Node *DL = d->left_tree;
						//save the right tree of d to DR
						Search_tree<Type>::Node *DR = d->right_tree;
						//promote d to the current node
						//move DL to the right tree of this
						this->right_tree = DL;
						//move DR ot the left tree of b
						b->left_tree = DR;
						//move the current node to the left tree of d
						d->left_tree = this;
						//move b to the right tree of d
						d->right_tree = b;
						//set to_this to d, in order to promote d
						to_this = d;
						//after all the rotation, update the height for b, current node and d, make sure d is updated lastly
						b->update_height();
						this->update_height();
						d->update_height();
					}
					else{
						//right right case, single rotation

						//save the right tree of the current node to b
						Search_tree<Type>::Node *b = this->right_tree;
						//save the left tree of b to BL
						Search_tree<Type>::Node *BL = b->left_tree;
						//promote b to the current node
						//move the current node to the left tree of b
						b->left_tree = this;
						//set to_this to b, in order to promote b
						to_this = b;
						//move BL to the right tree of the current node
						this->right_tree = BL;
						//after all the rotation, update the height of the current node and b, make sure b is updated lastly
						this->update_height();
						b->update_height();
					}
				}
				
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
				update_height();
				//check if avl imbalance happened on this node,
				if(this->right_tree->height() - this->left_tree->height() == 2){
					//determine if it is right right or right left
					if(this->right_tree->left_tree->height() > this->right_tree->right_tree->height()){//we directly check which subtree of the right tree has larger height
						//right left case
						Search_tree<Type>::Node *b = this->right_tree;
						Search_tree<Type>::Node *d = b->left_tree;
						Search_tree<Type>::Node *DL = d->left_tree;
						Search_tree<Type>::Node *DR = d->right_tree;
						this->right_tree = DL;
						b->left_tree = DR;
						d->left_tree = this;
						d->right_tree = b;
						to_this = d;
						b->update_height();
						this->update_height();
						d->update_height();
					}
					else{
						//right right case, single rotation
						Search_tree<Type>::Node *b = this->right_tree;
						Search_tree<Type>::Node *BL = b->left_tree;
						b->left_tree = this;
						to_this = b;
						this->right_tree = BL;
						this->update_height();
						b->update_height();

						
					}
				}
				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
				update_height();
				//check if avl imbalance happened on this node,
				if(this->left_tree->height() - this->right_tree->height() == 2){
					//determine if it is left left or left right
					if(this->left_tree->right_tree->height() > this->left_tree->left_tree->height()){//we directly check which subtree of the left tree has larger height
						//left right case
						
						Search_tree<Type>::Node *b = this->left_tree;
						Search_tree<Type>::Node *d = b->right_tree;
						
						Search_tree<Type>::Node *DL = d->left_tree;
						
						Search_tree<Type>::Node *DR = d->right_tree;
						
						this->left_tree = DR;
						b->right_tree = DL;
						d->left_tree = b;
						d->right_tree = this;
						
						to_this = d;
						b->update_height();
						this->update_height();
						d->update_height();
						
						
					}
					else{
						
						//left left case, single rotation
						
						Search_tree<Type>::Node *b = this->left_tree;
						Search_tree<Type>::Node *BR = b->right_tree;
						b->right_tree = this;
						to_this = b;
						this->left_tree = BR;
						this->update_height();
						b->update_height();
						
					}
				}
				return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );

		if ( is_leaf() ) {
			//remove the node in the double linked list
			this->next_node->previous_node = this->previous_node;
			this->previous_node->next_node = this->next_node;
			to_this = nullptr;

			delete this;
			
		} else if ( left_tree == nullptr ) {
			//remove the node in the double linked list
			this->next_node->previous_node = this->previous_node;
			this->previous_node->next_node = this->next_node;
			to_this = right_tree;
			delete this;
		} else if ( right_tree == nullptr ) {
			//remove the node in the double linked list
			this->next_node->previous_node = this->previous_node;
			this->previous_node->next_node = this->next_node;
			to_this = left_tree;
			delete this;
		} else {
			node_value = right_tree->front()->node_value;
			right_tree->erase( node_value, right_tree );
			update_height();
			//check if avl imbalance happened on this node, we need to check it here, since we won't go back to this node again
			if(this->left_tree->height() - this->right_tree->height() == 2){
					//determine if it is left left or left right
					if(this->left_tree->right_tree->height() > this->left_tree->left_tree->height()){//we directly check which subtree of the left tree has larger height
						//left right case, single rotation
						Search_tree<Type>::Node *b = this->left_tree;
						Search_tree<Type>::Node *d = b->right_tree;
						Search_tree<Type>::Node *DL = d->left_tree;
						Search_tree<Type>::Node *DR = d->right_tree;
						this->left_tree = DR;
						b->right_tree = DL;
						d->left_tree = b;
						d->right_tree = this;
						to_this = d;
						b->update_height();
						this->update_height();
						d->update_height();
					}
					else{
						
						//left left case, single rotation
						Search_tree<Type>::Node *b = this->left_tree;
						Search_tree<Type>::Node *BR = b->right_tree;
						b->right_tree = this;
						to_this = b;
						this->left_tree = BR;
						this->update_height();
						b->update_height();
						
						
					}
				}
		}

		return true;
	}
}





//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing
	//check if the current iterator is the end of the tree
	if(*this == this->containing_tree->end()){
		//set is_end to true, although we never use it...
		this->is_end = true;
	}
	else{
		//set current node to its next node
		this->current_node = this->current_node->next_node;
	}

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing
	//check if the current iterator is the rend of the tree
	if(*this == this->containing_tree->rend()){
		//do nothing
	}
	else{
		//set current node to its previous node
		this->current_node = this->current_node->previous_node;
	}

	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
