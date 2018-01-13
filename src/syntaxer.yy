
// compile with 
// yacc -d main.yy && lex main.ll && g++ main.tab.cc lex.yy.c -std=gnu++11

%{
	#include "SyntaxNode.hpp"
	#include <iostream>
	#include <vector>
	#include <cstdio>

	using std::cout;

 	int yywrap() {return 1;}
 	int yylex(void);
	inline void yyerror(const char *s) { std::cout << s; }

	syntax_node_t *SyntaxRoot;

	syntax_node_t *Parse();
%}

%code requires {
	#include "SyntaxNode.hpp"
	#include <cstring>
	#include <string>

	typedef union Yaccsyntax_node_t
	{
    	syntax_node_t *node;
		char buffer[128];
		Yaccsyntax_node_t()
		{
			memset( this, 0, sizeof(Yaccsyntax_node_t) );
			//std::cout << "\nYaccsyntax_node_t::Yaccsyntax_node_t()";
		}
    } YYSTYPE;

	static syntax_node_t *OperatorNode(char op)
	{
		syntax_node_t *node = new syntax_node_t;
		node->content = "identifier";
		syntax_node_t *node2 = new syntax_node_t;
		node2->content = std::string("operator_") + op;
		node->childList.push_back(node2);
		return node;
	}

	syntax_node_t *Parse();
}

%token          END_OF_FILE
%token<buffer>	STRING_LITERAL
%token<buffer>	NUMBER_LITERAL
%token<buffer>	IDENTIFIER
 
%%
translation_unit:
    baselevel_statement_seq_opt END_OF_FILE
    {
        cout << "\nSuccessful parsing.\n";

		SyntaxRoot = $<node>$;

        YYACCEPT;
    }
;

baselevel_statement_seq_opt:
	/* empty */
	{
		auto n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "baselevel_statements_opt : empty";
	}
	|  baselevel_statement_seq
;

baselevel_statement_seq:
	baselevel_statement	
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		// std::cout << "hello";
		n0->content = "baselevel_statement_seq";
		n0->childList.push_back($<node>1);
	}
	| baselevel_statement_seq baselevel_statement
	{
		auto &n1 = $<node>1;
		n1->childList.push_back($<node>2);
	}
;

baselevel_statement:
	statement
	| function_definition
;

statement:
    expression_statement
	// | compound_statement
;

	/*
	compound_statement:
		'{' statement_seq_opt '}'
		{
			$<node>$ = $<node>2;
		}
	;
	*/

expression_statement:
	expression_opt ';'
	{
		$<node>$ = $<node>1;
	}
;

expression_opt:
	/* epsilon */
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		n0->content = "empty";
	}
	| expression
;

expression:
	assignment_expression
;

statement_seq_opt:
	/* epsilon */
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		n0->content = "empty";
	}
	| statement_seq
;

statement_seq:
	statement
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		// std::cout << "hello";
		n0->content = "statement_seq";
		n0->childList.push_back($<node>1);
	}
	| statement_seq statement
	{
		auto &n1 = $<node>1;
		n1->childList.push_back($<node>2);
	}
;

primary_expression:
	literal
	| identifier
;

argument_list_opt:
	 // empty
	 {
		 auto &n0 = $<node>$;
		 n0 = new syntax_node_t;
		 n0->content = "argument_list";
	 }
	 | argument_list
;
 
argument_list:
	assignment_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		n0->content = "argument_list";
		n0->childList.push_back($<node>1);		
	}
	| argument_list ',' assignment_expression
	{
		auto &n1 = $<node>1;
		n1->childList.push_back($<node>3);
	}
;

function_call:
	primary_expression
	{

	}
	| identifier '(' argument_list_opt ')'
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back($<node>1);
		for(auto &t: $<node>3->childList)
			n0->childList.push_back(t);
	}
;

parameter_list_opt:
	/* empty */
	{
		 auto &n0 = $<node>$;
		 n0 = new syntax_node_t;
		 n0->content = "parameter_list";		
	}
	| parameter_list
;

parameter_list:
	literal literal
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		n0->content = "parameter_list";
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>2);
	}
	| parameter_list ',' literal literal
	{
		auto &n1 = $<node>1;
		n1->childList.push_back($<node>3);
		n1->childList.push_back($<node>4);
	}
;

function_definition:
	literal literal '(' parameter_list_opt ')' '{' statement_seq_opt '}'
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t();
		n0->content = "function_def";
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>2);
		n0->childList.push_back($<node>4);
		n0->childList.push_back($<node>7);
	}
;

cast_expression:
	function_call
	// | '(' "asd" ')' cast_expression
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
assignment_expression:
	additive_expression
	| assignment_expression '=' additive_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('='));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);
	}
    ;

multiplicative_expression:
	cast_expression
	| multiplicative_expression '*' cast_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('*'));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);
	}
	| multiplicative_expression '/' cast_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('/'));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);
	}
	| multiplicative_expression '%' cast_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('%'));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);
	}
;

additive_expression:
	multiplicative_expression
	| additive_expression '+' multiplicative_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('+'));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);
	}
	| additive_expression '-' multiplicative_expression
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t;
		n0->content = "function_call";
		n0->childList.push_back(OperatorNode('-'));
		n0->childList.push_back($<node>1);
		n0->childList.push_back($<node>3);		
	}
;

literal:
    STRING_LITERAL
	{
		//std::cout << "\nLITERAL = " << $1;
		auto &n0 = $<node>$;
		n0 = new syntax_node_t("literal");
		n0->childList.push_back(new syntax_node_t("string"));
		n0->childList.push_back(new syntax_node_t($1));
	}
	| NUMBER_LITERAL
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t("literal");
		n0->childList.push_back(new syntax_node_t("number"));
		n0->childList.push_back(new syntax_node_t($1));
	}
;

identifier:
	IDENTIFIER
	{
		auto &n0 = $<node>$;
		n0 = new syntax_node_t("identifier");
		n0->childList.push_back(new syntax_node_t($1));
	}
;

%%

extern int yylex();
extern int yyparse();

syntax_node_t *Parse()
{ 
	std::cout << "\nParser started.";

	extern FILE *yyin;
	fopen_s(&yyin, "res\\script.txt", "r");
	yyparse(); 

	std::cout << "\nParser  ended.";

	return SyntaxRoot;
}

// CHANGE LITERAL DEFINITION
