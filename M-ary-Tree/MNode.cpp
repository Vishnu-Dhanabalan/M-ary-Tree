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
	Version 1.2 | 1 March 2016
	--------------------------
		Details: 1) Modified constructors and AddChildren method to work with "_name" variable.
				 2) Added methods show and ShowHelper for printing trees. 
				 3) Added few example statements in main function.

	Version 1.1	| 29 Feb 2016
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
#include <typeinfo>
#include "MNode.h"

//<---- Default constructor ---->
template <class T>
MNode<T>::MNode() : _name("Original node"), _id("--"), _hasParent(false) {}

//<---- Parameterized constructor ---->
template <class T>
MNode<T>::MNode(T value, std::string name, std::string id) : _value(value), _name(name), _id(id), _hasParent(false) {}

//<---- Default destructor ---->
template <class T>
MNode<T>::~MNode() {}

//<---- Method for add children to any node ---->
template <class T>
void MNode<T>::AddChild(const T& templateVal, std::string name, std::string id) {
	std::shared_ptr<MNode<T>> tempChild(new MNode<T>(templateVal, name, id));
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
std::string MNode<T>::ReturnID() { 
	return this->_id;
}

template <class T>
std::string MNode<T>::ReturnName() {
	return this->_name;
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
	else if (childPtr->ReturnID() == ID) {
		_foundNodes = childPtr;
	}
	else {
		for (auto pChild : childPtr->_children)
			FindByIdHelper(pChild, ID);
	}
}

template <class T>
void MNode<T>::Show() {
	std::cout << "Showing the tree in pre-order traversal.\n";
	std::cout << "========================================" << std::endl << std::endl;
	std::cout << "Root node: \n";
	std::cout << "========== \n";
	std::cout << this->_name << std::endl;		// Prints the root node.
	size_t count = 1;
	for (auto pChild : this->_children) {
		PutIndentation(count);
		ShowHelper(pChild, count);
	}
	std::cout << "\n\n" << "*** End of tree ***\n";
}

template <class T>
void MNode<T>::ShowHelper(sPtr childPtr, size_t count) {
	std::cout << childPtr->ReturnName() << "\n";
	for (auto pChild : childPtr->_children) {
		count++;
		PutIndentation(count);
		ShowHelper(pChild, count);
		count--;
	}
}

template <class T>
void MNode<T>::PutIndentation(size_t count) {
	for (size_t i = 0; i < count; i++)
		std::cout << "\t";
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
	sPtr rootNode(new genNode(e1, "John_Deer","1"));

	//<---- Create and children for your root node ---->
	element e1_1;
	e1_1.firstName = "Alex";
	e1_1.lastName = "Madman";
	e1_1.age = 14;
	rootNode->AddChild(e1_1, "Alex_Madman", "1_1");

	element e1_2;
	e1_2.firstName = "Jack";
	e1_2.lastName = "Butland";
	e1_2.age = 14;
	rootNode->AddChild(e1_2, "Jack_Butland", "1_2");

	element e1_3;
	e1_3.firstName = "Mr.";
	e1_3.lastName = "Glenfiddich";
	e1_3.age = 17;
	rootNode->AddChild(e1_3, "Glenfiddich", "1_3");

	std::vector<sPtr> foundChildren = rootNode->GetNodeChildren();	// Get any node's children.

	//<---- Create grandchildren for your root node ---->
	element e1_2_1;
	e1_2_1.firstName = "John";
	e1_2_1.lastName = "Deer Jr.";
	e1_2_1.age = 5;

	genNode& secondGeneration = *rootNode;		// Creating a raw pointer of rootNode to traverse through it's children.
	secondGeneration[1]->AddChild(e1_2_1, "John_Deer_Jr.","1_2_1");		// Use overloaded [] operator for indexing and add the child.

	sPtr foundNode = rootNode->FindById("1_2_1");		// Find a node with ID "1_2_1"
	
	element e1_2_1_1;		
	e1_2_1_1.firstName = "Jack";
	e1_2_1_1.lastName = "Daniels";
	e1_2_1_1.age = 2;

	foundNode->AddChild(e1_2_1_1, "Jack_Daniels","1_2_1_1");	// Added a new child to a node which was found by ID.
	
	rootNode->Show();		// Print the entire tree.

	std::cout << "\n\n";
	return 0;
}

#endif
