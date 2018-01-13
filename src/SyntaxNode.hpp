
#pragma once

#include <vector>
#include <string>
#include <iostream>

struct syntax_node_t
{		
    std::string 			content;
    std::vector<syntax_node_t *>  childList;

    syntax_node_t() : content(), childList() {}
	syntax_node_t(std::string content) : content(content), childList() {}
	~syntax_node_t()
	{
		for (auto &t : childList)
			delete t;
	}
    void Display(int depth = 0)
    {
        std::cout << "\n";
        while(depth--) std::cout.put('\t');
        std::cout << content;
    }
    void DisplayAll(int depth = 0)
    {
        Display(depth);
        for(auto &t : childList)
            t->DisplayAll(depth+1);
    }
};
