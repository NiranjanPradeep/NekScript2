/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_SYNTAXER_HPP_INCLUDED
# define YY_YY_SRC_SYNTAXER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2058 of yacc.c  */
#line 22 "src/syntaxer.yy"

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


/* Line 2058 of yacc.c  */
#line 76 "src/syntaxer.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_FILE = 258,
     STRING_LITERAL = 259,
     NUMBER_LITERAL = 260,
     IDENTIFIER = 261
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SRC_SYNTAXER_HPP_INCLUDED  */
