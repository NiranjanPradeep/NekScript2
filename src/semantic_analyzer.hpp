

#pragma once

#include "SyntaxNode.hpp"
#include "semanticnode.hpp"

class semantic_analyzer_c
{
public:
	semantic_node_t *analyze(syntax_node_t *root)
	{
		semantic_node_t *newRoot = nullptr;
		convert(root, newRoot);
		recFn(newRoot);
		return newRoot;
	}
	void convert(syntax_node_t *&root, semantic_node_t *&newRoot)
	{
		if(root)
		{
			newRoot = new semantic_node_t;
			newRoot->content = root->content;
			for (auto &t : root->childList)
			{
				newRoot->childList.push_back({});
				convert(t, newRoot->childList.back());
			}
		}
	}
	void recFn(semantic_node_t *&root)
	{
		/*
	        function_call
                identifier
                        print
                function_call
                        -
                        function_call
                                +
                                literal
                                        number
                                        1
                                function_call
                                        *
                                        literal
                                                number
                                                2
                                        literal
                                                number
                                                3
                        literal
                                number
                                4
		*/
		if (root == nullptr)
			return;
		if (root->content == "function_call")
		{
			root->isFunctionCall = true;
			root->content = root->childList[0]->childList[0]->content;
			root->childList.erase(root->childList.begin(), root->childList.begin() + 1);
			for (int i = 0; i < root->childList.size(); i++)
				recFn(root->childList[i]);
		}
		else if (root->content == "identifier")
		{
			root->isIdentifier = true;
			root->content = root->childList[0]->content;
			root->ClearChildren();
		}
		else if (root->content == "literal")
		{
			root->isLiteral = true;
			if(root->childList[0]->content == "number")
				root->typeId = "number";
			if (root->childList[0]->content == "string")
				root->typeId = "string";
			root->ClearChildren();
		}
		else
		{
			for(auto &t : root->childList)
				recFn(t);
		}
	}
private:

};
