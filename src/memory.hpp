
#pragma once

union memory_element_t
{
	char character;
	char *cString;
	double real;
	void *address;
};

using accumulator_t = char[128];

