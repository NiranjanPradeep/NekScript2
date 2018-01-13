
#include "virtualmachine.hpp"

void virtual_machine_c::ExecuteScript()
{
	syntax_node_t *root = m_syntax_analyzer.process();
	if (root == nullptr)
	{
		std::cin.get();
		return;
	}
	root->DisplayAll();

	semantic_node_t *root2 = m_semantic_analyzer.analyze(root);
	delete root;
	if (root2 == nullptr)
	{
		std::cin.get();
		return;
	}
	root2->DisplayAll();

	objectcode_t objectCode;
	bytecode_t byteCode;

/*
	m_compiler.analyze(root2, objectCode);

	m_linker.analyze(objectCode, byteCode);

	std::cout << "\n\n";
	for (auto &t : byteCode) 
		std::cout << t << std::endl;

	m_interpretor.executeAll(byteCode);*/
}
