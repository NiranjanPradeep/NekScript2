
#include "virtualmachine.hpp"
#include <iostream>

int main()
{
	std::cout << "\nProgram started.";
	
	virtual_machine_c vm;
	vm.ExecuteScript();

	std::cout << "\nProgram ended.";
	std::cin.get();
}
