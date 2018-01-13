

#pragma once

#include <vector>
#include <string>

static const char *instruction_string_list[] = {
	"native_function_call",
	"load_memory",
	"load_string",
	"load_number",
	"store_memory",
};

enum : unsigned char
{
	VM_NATIVE_CALL,
	VM_LOAD_MEMORY,
	VM_LOAD_LITERAL_STRING,
	VM_LOAD_LITERAL_NUMBER,
	VM_STORE_MEMORY,
};

using objectcode_t = std::vector<std::string>;
using bytecode_t = std::vector<unsigned char>;
