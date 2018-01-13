
#include "compiler.hpp"
#include "instructionset.hpp"

void compiler_c::analyze(semantic_node_t * root, objectcode_t& byteCode)
{
	recFn(root, byteCode);
}

void compiler_c::recFn(semantic_node_t * root, objectcode_t& code)
{
	if (root)
	{
		if (root->content == "identifier")
		{
			code.push_back(instruction_string_list[VM_LOAD_MEMORY]);
			code.push_back(root->childList[0]->content);
		}
		else if (root->content == "literal")
		{
			if (root->childList[0]->content == "string")
				code.push_back(instruction_string_list[VM_LOAD_LITERAL_STRING]);
			else if (root->childList[0]->content == "number")
				code.push_back(instruction_string_list[VM_LOAD_LITERAL_NUMBER]);
			code.push_back(root->childList[1]->content);
		}
		else if (root->content == "function_call")
		{
			for (size_t i = 1; i < root->childList.size(); i++)
				recFn(root->childList[i], code);
			code.push_back(instruction_string_list[VM_NATIVE_CALL]);
			code.push_back(root->childList[0]->content);
		}
		else
		{
			for (auto &t : root->childList)
				recFn(t, code);
		}
	}
}
