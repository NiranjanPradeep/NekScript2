

#pragma once

#include <vector>
#include <string>
#include <iostream>

struct semantic_node_t
{
	std::string 			content;
	std::vector<semantic_node_t *>  childList;
	std::string				typeId;
	bool					isLiteral;
	bool					isFunction;
	bool					isIdentifier;
	bool					isFunctionCall;
	semantic_node_t() :
		isLiteral(false),
		isFunction(false),
		isIdentifier(false),
		content(),
		childList(),
		typeId()
	{

	}
	~semantic_node_t()
	{
		ClearChildren();
	}
	void Display(int depth = 0)
	{
		std::cout << "\n";
		while (depth--) std::cout.put('\t');
		std::cout << content << " <" << typeId << ">\t";
		if (isLiteral) std::cout << "isLiteral";
		if (isFunction) std::cout << "isFunction";
		if (isIdentifier) std::cout << "isIdentifier";
	}
	void DisplayAll(int depth = 0)
	{
		Display(depth);
		for (auto &t : childList)
			t->DisplayAll(depth + 1);
	}
	void ClearChildren()
	{
		for (auto &t : childList)
			delete t;
		childList.clear();
	}
};
