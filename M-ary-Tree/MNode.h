#ifndef _MNODE_
#define _MNODE_
///////////////////////////////////////////////////////////////////////////////////
//																				 //	
//	File name: MNode.h															 //
//	About: Declaring template class MNode and it's member variables and methods	 //
//	Author: Vishnu Dhanabalan													 //
//	Email: vishnudhanabalan@outlook.com											 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////

/*
Operation:
----------
	This file makes declarations for MNode class.
	It also declares the methods and variables for MNode class.

Maintenance history:
--------------------
	Version 1.0 | Initial commit -- 29 February 2016.
		Details: Created template class MNode and declared it's member variables and methods.
		 
*/ 

#include <iostream>
#include <vector>
#include <memory>

template <class T>
class MNode {
public:
	using sPtr = std::shared_ptr<MNode<T>>;
	MNode();
	MNode(T value, std::string id);
	~MNode();
	void AddChildren(const T& children, std::string id);
	std::vector<sPtr> GetNodeChildren();
	sPtr& operator[](const size_t childrenId);

private:
	T _value;
	std::string _id;
	std::vector<sPtr> _children;
	bool _hasParent;
};

#endif