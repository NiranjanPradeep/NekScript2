

#pragma once

#include <string>
#include <vector>

struct function_desc_t
{
	std::string name;
	std::string returnType;
	std::vector<std::string> argTypes;
};

struct function_desc_ex_t : function_desc_t
{
	std::vector<std::string> argNames;
	int address;
	bool native;
};
