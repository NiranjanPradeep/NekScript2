

#pragma once

#include "syntax_analyzer.hpp"
#include "memory.hpp"
#include "compiler.hpp"
#include "interpreter.hpp" 
#include "semantic_analyzer.hpp"

class virtual_machine_c
{
public:
	void ExecuteScript();
private:
	compiler_c			m_compiler;
	syntax_analyzer_c	m_syntax_analyzer;
	interpreter_c		m_interpretor;
	semantic_analyzer_c m_semantic_analyzer;
};
