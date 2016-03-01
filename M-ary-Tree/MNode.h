#ifndef _MNODE_
#define _MNODE_
///////////////////////////////////////////////////////////////////////////////////
//																				 	
//	File name: MNode.h															 
//	About: Declaring template class MNode and it's member variables and methods	 
//	Author: Vishnu Dhanabalan													 
//	Email: vishnudhanabalan@outlook.com											 
//					
///////////////////////////////////////////////////////////////////////////////////

/*
Operation:
==========
	This file makes declarations for MNode class.
	It also declares the methods and variables for MNode class.

Maintenance history:
====================
	Version 1.1	| 1 March 2016
	--------------------------
		Details: 1) Declared methods FindByID and FindByIdHelper for finding[1] any unique[2] node.
				 2) Defined method returnID which returns an unique[2] ID of a node.

	Version 1.0 | Initial commit -- 29 February 2016.
	-------------------------------------------------
		Details: Created template class MNode and declared it's member variables and methods.

References:
===========
	[1] Uses Preorder traversal operation.
	[2]	No two nodes must have the same IDs. IDs are std::string type.

*/ 

#include <iostream>
#include <vector>
#include <memory>

template <class T>
class MNode {
public:
	using sPtr = std::shared_ptr<MNode<T>>;
	
	// Constructors and destructor.
	MNode();
	MNode(T value, std::string id);
	~MNode();

	// Add, get children methods.
	void AddChildren(const T& children, std::string id);
	std::vector<sPtr> GetNodeChildren();
	std::string returnID();
	
	// Finders.
	sPtr FindById(std::string id);

	// Overloaded operators.
	sPtr& operator[](const size_t childrenId);

private:
	// Private member variables.
	T _value;
	std::string _id;
	std::vector<sPtr> _children;
	std::vector<sPtr> _foundValues;
	sPtr _foundNodes;
	bool _hasParent;

	// Private member functions.
	void FindByIdHelper(sPtr childPtr, std::string ID);
};

#endif
