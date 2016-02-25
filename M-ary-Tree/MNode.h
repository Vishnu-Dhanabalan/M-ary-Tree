#pragma once

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
