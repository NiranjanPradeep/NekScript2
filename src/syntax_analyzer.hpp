
#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "syntaxer.hpp"
//#include "SyntaxNode.hpp"

class syntax_analyzer_c
{
public:
	syntax_node_t *process()
	{
		return ::Parse();
	}

private:

};
