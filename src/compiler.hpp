
#pragma once

#include "semanticnode.hpp"
#include "instructionset.hpp"

#include <vector>
#include <string>

class compiler_c
{
public:
	void analyze(semantic_node_t *root, objectcode_t &byteCode);
	void recFn(semantic_node_t *root, objectcode_t &code);
private:

};
