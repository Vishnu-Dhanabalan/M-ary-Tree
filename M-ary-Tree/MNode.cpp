///////////////////////////////////////////////////////////////////////////
//																		 	
//	File name: MNode.cpp												 
//	About: Implementating M-tree structure using MNode.h and testing	 
//	Author: Vishnu Dhanabalan											 
//	Email: vishnudhanabalan@outlook.com									 
//																	     
///////////////////////////////////////////////////////////////////////////

/*
Operation:
==========
	This file implements M-tree structure by using MNode.h header file.
	It also defines the methods that are being declared in MNode.h file.
	
Maintenance history:
====================
	Version 1.1	| 1 March 2016
	--------------------------
		Details: 1) Defined methods FindByID and FindByIDHelper for finding[1] any unique[2] node.
				 2) Defined method returnID which returns an unique[2] ID of a node.
	
	Version 1.0 | Initial commit -- 29 February 2016.
	------------------------------------------------
		Details: Implemented basic tree structure methods, tested with few examples.

References:
===========
	[1] Uses Preorder traversal operation.
	[2]	No two nodes must have the same IDs. IDs are std::string type.

*/

#include <iostream>
#include <string>
#include "MNode.h"

//<---- Default constructor ---->
template <class T>
MNode<T>::MNode() : _id("--"), _hasParent(false) {
	std::cout << "A new node has been created.\n";
}

//<---- Parameterized constructor ---->
template <class T>
MNode<T>::MNode(T value, std::string id) : _value(value), _id(id), _hasParent(false) {
	std::cout << "Node " << id << " has been created.\n";
}

//<---- Default destructor ---->
template <class T>
MNode<T>::~MNode() {
	std::cout << "Node " << this->_id << " has been deleted.\n";
}

//<---- Method for add children to any node ---->
template <class T>
void MNode<T>::AddChildren(const T& templateVal, std::string id) {
	std::shared_ptr<MNode<T>> tempChild(new MNode<T>(templateVal, id));
	tempChild->_hasParent = true;
	this->_children.push_back(tempChild);
}

//<---- Getter for any children ---->
template <class T>
std::vector<std::shared_ptr<MNode<T>>> MNode<T>::GetNodeChildren() {
	return this->_children;
}

//<---- Return ID of any node ---->
template <class T>
std::string MNode<T>::returnID() { 
	return this->_id;
}

//<---- Method for overloading []. Helps in indexing through node's children ---->
template <class T>
std::shared_ptr<MNode<T>>& MNode<T>::operator[](const size_t childrenId) {
	if (childrenId < 0)
		throw (std::invalid_argument("Invalid indexing number passed.\n"));

	return this->_children[childrenId];
}

//<---- Method to find and return children as vector, using their ID ---->
template <class T>
std::shared_ptr<MNode<T>> MNode<T>::FindById(std::string ID) {
	_foundNodes = nullptr;
	for (auto pChild : _children) {
		FindByIdHelper(pChild, ID);
	}
	return _foundNodes;
}

//<---- Helper method for finding children by it's ID ---->
template <class T>
void MNode<T>::FindByIdHelper(sPtr childPtr, std::string ID) {
	if (_foundNodes != nullptr) {
		return;
	}
	else if (childPtr->returnID() == ID) {
		_foundNodes = childPtr;
	}
	else {
		for (auto pChild : childPtr->_children)
			FindByIdHelper(pChild, ID);
	}
}

#ifdef _MNODE_MAIN_

int main(void) {

	//<---- Define the data type of your nodes here ---->
	struct element {		// Here I'm gonna deal with struct as data type.
		std::string firstName;
		std::string lastName;
		unsigned int age;
	};

	using genNode = MNode<element>;		// Just to make things easier.
	using sPtr = std::shared_ptr<genNode>;	// sPtr = shared pointer of MNode objects of data type of your own.

	//<---- Create something for node ---->
	element e1;
	e1.firstName = "John";
	e1.lastName = "Deer";
	e1.age = 25;

	//<---- Create a simple root node ---->	
	sPtr rootNode(new genNode(e1, "1"));

	//<---- Create and children for your root node ---->
	element e1_1;
	e1_1.firstName = "Alex";
	e1_1.lastName = "Madman";
	e1_1.age = 14;
	rootNode->AddChildren(e1_1, "1_1");

	element e1_2;
	e1_2.firstName = "Jack";
	e1_2.lastName = "Butland";
	e1_2.age = 14;
	rootNode->AddChildren(e1_2, "1_2");

	//<---- Create grandchildren for your root node ---->
	element e1_2_1;
	e1_2_1.firstName = "John";
	e1_2_1.lastName = "Deer Jr.";
	e1_2_1.age = 5;

	genNode& secondGeneration = *rootNode;		// Creating a raw pointer of rootNode to traverse through it's children.
	secondGeneration[1]->AddChildren(e1_2_1, "1_2_1");		// Use overloaded [] operator for indexing and add the child.

	sPtr foundNode = rootNode->FindById("1_2_1");		// Find a node with ID "1_2_1"

	return 0;
}

#endif
