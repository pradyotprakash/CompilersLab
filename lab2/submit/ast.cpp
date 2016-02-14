ast.h                                                                                               0000664 0001750 0001750 00000006541 12660041526 011756  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                #include <iostream>
#include <vector>
using namespace std;
#ifndef ASTH

class abstract_astnode{
public:
	virtual void print(int)=0;
};

class stmt_astnode: public abstract_astnode{
public:
	virtual void print(int);
};

class exp_astnode: public abstract_astnode{
public:
	virtual void print(int);
};

class ref_astnode: public exp_astnode{
public:
	virtual void print(int);
};

class empty_astnode: public stmt_astnode{
public:
	empty_astnode();
	void print(int);
};

class seq_astnode: public stmt_astnode{
protected:
	std::vector<stmt_astnode*> nodes;
public:
	seq_astnode(std::vector<stmt_astnode*>);
	void print(int);
};

class assign_astnode: public stmt_astnode{
protected:
	ref_astnode* l;
	exp_astnode* r;
public:
	assign_astnode(ref_astnode*, exp_astnode*);
	void print(int);
};

class return_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
public:
	return_astnode(exp_astnode*);
	void print(int);
};

class if_astnode: public stmt_astnode{
protected:
	exp_astnode *node;
	stmt_astnode *nodes[2];
public:
	if_astnode(exp_astnode*, stmt_astnode**);
	void print(int);
};

class while_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
	stmt_astnode *node2;
public:
	while_astnode(exp_astnode*, stmt_astnode*);
	void print(int);
};

class for_astnode: public stmt_astnode{
protected:
	exp_astnode* nodes[3];
	stmt_astnode* node;
public:
	for_astnode(exp_astnode**, stmt_astnode*);
	void print(int);
};

class op_astnode2: public exp_astnode{
protected:	
	exp_astnode* nodes[2];
	std::string op;
public:
	op_astnode2(exp_astnode**, std::string);
	void print(int);
};

class op_astnode1: public exp_astnode{
protected:
	exp_astnode* node;
	std::string op;
public:
	op_astnode1(exp_astnode*, std::string);
	void print(int);
};

class funcall_astnode: public exp_astnode{
	std::string funcName;
	std::vector<exp_astnode*> nodes;
public:
	funcall_astnode(std::string, std::vector<exp_astnode*>);
	void print(int);
};

class floatconst_astnode: public exp_astnode{
protected:
	float val;
public:
	floatconst_astnode(float);
	void print(int);
};

class intconst_astnode: public exp_astnode{
protected:
	int val;
public:
	intconst_astnode(int);
	void print(int);
};

class stringconst_astnode: public exp_astnode{
protected:
	std::string val;
public:
	stringconst_astnode(std::string);
	void print(int);
};

class refast_astnode: public exp_astnode{
protected:
	ref_astnode* ref;
public:
	refast_astnode(ref_astnode*);
	void print(int);
};

class identifier_astnode: public ref_astnode{
protected:
	std::string name;
public:
	identifier_astnode(std::string);
	void print(int);
};

class arrayref_astnode: public ref_astnode{
protected:
	ref_astnode* base;
	exp_astnode* offset;
public:
	arrayref_astnode(ref_astnode*, exp_astnode*);
	void print(int);
};

class pointer_astnode: public ref_astnode{
protected:
	ref_astnode* node;
public:
	pointer_astnode(ref_astnode*);
	void print(int);
};

class deref_astnode: public ref_astnode{
protected:
	ref_astnode* node;
public:
	deref_astnode(ref_astnode*);
	void print(int);
};

class member_astnode: public ref_astnode{
protected:
	ref_astnode* node;
	identifier_astnode* id;
public:
	member_astnode(ref_astnode*, identifier_astnode*);
	void print(int);
};

class arrow_astnode: public ref_astnode{
protected:
	ref_astnode* node;
	identifier_astnode* id;
public:
	arrow_astnode(ref_astnode*, identifier_astnode*);
	void print(int);
};


#define ASTH
#endif                                                                                                                                                               enums                                                                                               0000664 0001750 0001750 00000000313 12660036524 012061  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                enum Tokens{
VOID=0x100,
INT,
FLOAT,
RETURN,
LE_OP,
GE_OP,
EQ_OP,
NE_OP,
OR_OP,
AND_OP,
INC_OP,
IF,
ELSE,
WHILE,
FOR,
INT_CONSTANT,
FLOAT_CONSTANT,
STRING_LITERAL,
IDENTIFIER,
COMMENT,
STRUCT,
PTR_OP
};
                                                                                                                                                                                                                                                                                                                     lex.l                                                                                               0000664 0001750 0001750 00000002231 12660036524 011755  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                %%

[ \t] 			// skip
void 			return Parser::VOID;
int				return Parser::INT;
float 			return Parser::FLOAT;

return			return Parser::RETURN;
"<="			return Parser::LE_OP;
">="			return Parser::GE_OP;
"=="			return Parser::EQ_OP;
"!="			return Parser::NE_OP;
"||"			return Parser::OR_OP;
"&&"			return Parser::AND_OP;
"++"			return Parser::INC_OP;
if 				return Parser::IF;
else			return Parser::ELSE;
while			return Parser::WHILE;
for				return Parser::FOR;
struct 			return Parser::STRUCT;
"->"			return Parser::PTR_OP;

"/*"[^*]*(\*([^/*][^*]*)?)*"*/" // skip return Parser::COMMENT;

([0-9]+)|(0[bB][01]*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*) {Parser::d_val__ = stoi(std::string(matched())); return Parser::INT_CONSTANT;}

([0-9]+\.([0-9]*([eE]([+\-]?)[0-9]+)?))|([0-9]*\.([0-9]+([eE]([+\-]?)[0-9]+)?)) {Parser::d_val__ = stof(std::string(matched())); return Parser::FLOAT_CONSTANT;}

\"[[:alpha:][:digit:]( )(\t)(\n)(\\)(\")]*\" {Parser::d_val__ = std::string(matched()); return Parser::STRING_LITERAL;}

[[:alpha:]_][[:alpha:][:digit:]_]*	{Parser::d_val__ = std::string(matched()); return Parser::IDENTIFIER;}
.				{Parser::d_val__ = std::string(matched()); return matched()[0];}
                                                                                                                                                                                                                                                                                                                                                                       main.cc                                                                                             0000664 0001750 0001750 00000000233 12660036524 012243  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                #include <iostream>
#include "Scanner.h"
#include "Parser.h"
using namespace std;
int main (int argc, char** arg)
{
  Parser parser;
  parser.parse();
}


                                                                                                                                                                                                                                                                                                                                                                     makefile                                                                                            0000664 0001750 0001750 00000001706 12660036524 012516  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                all: clean    Scanner.ih Scanner.h Scannerbase.h lex.cc parse.cc main.cc Parser.h Parserbase.h Parser.ih
	g++   --std=c++0x lex.cc parse.cc main.cc -o parser
	./parser < test.c > junk

        
Scanner.ih: lex.l
	if [ ! -e Scanner.ih ]; then \
		flexc++ lex.l;\
                sed -i '/include/a #include "Parserbase.h"' Scanner.ih; \
	fi

parse.cc Parser.h Parserbase.h Parser.ih: parse.y
	bisonc++  --construction parse.y; 
	sed -i '/insert preincludes/a #include "ast.h"' Parserbase.h;
	sed -i '\|STYPE__     d_val__;| d' Parserbase.h;
	sed -i '\|typedef Meta__::SType STYPE__;| a \\tpublic: static STYPE__  d_val__; ' Parserbase.h;
	sed -i '/include "Parser.ih"/a #include "ast.cpp"' parse.cc;
	sed -i '\|void Parser::print__()| i Meta__::SType ParserBase::d_val__; ' parse.cc


.PHONY: clean     
clean:
	$(RM) -f Parser.ih Parser.h Parserbase.h parse.cc Scanner.ih Scanner.h Scannerbase.h lex.cc a.out graph.ps junk *~ parse.y.output parser ast.h.gch ast.o
	
                                                          parse.y                                                                                             0000664 0001750 0001750 00000020324 12660045553 012321  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                %scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT RETURN LE_OP GE_OP EQ_OP NE_OP OR_OP AND_OP INC_OP IF ELSE WHILE FOR INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL IDENTIFIER STRUCT PTR_OP

%polymorphic STRING: std::string; EXP_ASTNODE: exp_astnode*; STMT_ASTNODE: stmt_astnode*; REF_ASTNODE: ref_astnode*; STMT_LIST: std::vector<stmt_astnode*>; EXP_LIST: std::vector<exp_astnode*>; INT_CONST: intconst_astnode*; FLOAT_CONST: floatconst_astnode*; STRING_LITERAL: stringconst_astnode*; IDENTIFIER_ASTNODE: identifier_astnode*; OP_ASTNODE1: op_astnode1*; OP_ASTNODE2: op_astnode2*; FUNCALL_ASTNODE: funcall_astnode*; SEQ_ASTNODE: seq_astnode*; RETURN_ASTNODE: return_astnode*; ASS_ASTNODE: assign_astnode*; IF_ASTNODE: if_astnode*; EMPTY_ASTNODE: empty_astnode*; WHILE_ASTNODE: while_astnode*; FOR_ASTNODE: for_astnode*; ARRAYREF_ASTNODE: arrayref_astnode*; POINTER_ASTNODE: pointer_astnode*; DEREF_ASTNODE: deref_astnode*; INT: int; FLOAT: float;

%type <STRING> unary_operator IDENTIFIER STRING_LITERAL
%type <INT> INT_CONSTANT
%type <FLOAT> FLOAT_CONSTANT

%type <EXP_ASTNODE> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression postfix_expression primary_expression

%type <STMT_ASTNODE> compound_statement statement assignment_statement selection_statement iteration_statement

%type <REF_ASTNODE> l_expression

%type <EXP_LIST> expression_list
%type <STMT_LIST> statement_list

%%

translation_unit 
        : struct_specifier
	 	| function_definition
	 	| translation_unit function_definition 
        | translation_unit struct_specifier
        ;

struct_specifier
        : STRUCT IDENTIFIER '{' declaration_list '}' ';'
        ;

function_definition
		: type_specifier fun_declarator compound_statement 
		;

type_specifier
        : base_type
        | type_specifier '*'
        ;

base_type 
        : VOID 	
        | INT   
		| FLOAT 
        | STRUCT IDENTIFIER 
        ;

fun_declarator
		: IDENTIFIER '(' parameter_list ')' 
		| IDENTIFIER '(' ')' 
		;

parameter_list
		: parameter_declaration 
		| parameter_list ',' parameter_declaration 
		;

parameter_declaration
		: type_specifier declarator 
        ;

declarator
		: IDENTIFIER 
		| declarator '[' constant_expression ']' 
        ;
constant_expression 
        : INT_CONSTANT 
        | FLOAT_CONSTANT 
        ;

compound_statement
		: '{' '}' {
			$$ = new seq_astnode(std::vector<stmt_astnode*>(1, new empty_astnode()));
			($$)->print(0);
		}		
		| '{' statement_list '}' {
			$$ = new seq_astnode($2);
			($$)->print(0);
		}
        | '{' declaration_list statement_list '}' {
        	$$ = new seq_astnode($3);
        	($$)->print(0);
        }
		;

statement_list
		: statement {
			($$)=std::vector<stmt_astnode*>(1, $1);
		}
        | statement_list statement {
        	($$)=$1;
        	($$).push_back($2);
        }
		;

statement
        : '{' statement_list '}' {
        	($$)=new seq_astnode($2);
        }
        | selection_statement 	{
        	($$)=$1;
        }
        | iteration_statement 	{
        	($$)=$1;
        }
		| assignment_statement	{
			($$)=$1;
		}
        | RETURN expression ';'	{
        	($$)=new return_astnode($2);
        }
    	;

assignment_statement
		: ';' {
			($$)=new empty_astnode();
		}
		|  l_expression '=' expression ';'	{
			($$)=new assign_astnode($1, $3);
		}
		;

expression
		: logical_and_expression {
			($$)=$1;
		}
	    | expression OR_OP logical_and_expression{
	    	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
	    	($$)=new op_astnode2(args, "OR");
	    }
		;

logical_and_expression
        : equality_expression {
        	($$)=$1;
        }
        | logical_and_expression AND_OP equality_expression {
        	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "AND");
        }
		;

equality_expression
		: relational_expression {
			($$)=$1;
		}
	    | equality_expression EQ_OP relational_expression {
	    	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "EQ_OP");	
	    }
		| equality_expression NE_OP relational_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "NE_OP");
		}
		;

relational_expression
		: additive_expression {
			($$)=($1);
		}
	    | relational_expression '<' additive_expression {
	    	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "LT");
	    }
		| relational_expression '>' additive_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "GT");
		}
		| relational_expression LE_OP additive_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "LE_OP");
		}
	    | relational_expression GE_OP additive_expression {
	    	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "GE_OP");	
	    }
		;

additive_expression 
		: multiplicative_expression {
			($$)=$1;
		}
		| additive_expression '+' multiplicative_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "PLUS");
		}
		| additive_expression '-' multiplicative_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "MINUS");
		}
		;

multiplicative_expression
		: unary_expression {
			($$)=$1;
		}
		| multiplicative_expression '*' unary_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "MULT");
		}
		| multiplicative_expression '/' unary_expression {
			exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "DIV");
		}
		;

unary_expression
		: postfix_expression {
			($$)=$1;
		}
		| unary_operator postfix_expression {
			($$)=new op_astnode1($2, $1);
		}
		;

postfix_expression
		: primary_expression {
			($$)=$1;
		}
	    | IDENTIFIER '(' ')' {
	    	($$) = new funcall_astnode($1, std::vector<exp_astnode*>(0));
	    }
		| IDENTIFIER '(' expression_list ')' {
			($$) = new funcall_astnode($1, $3);
		}
		| l_expression INC_OP {
			($$) = new op_astnode1($1, "PP");
		}
		;

primary_expression
		: l_expression {
			($$)=$1;
		}
	    | l_expression '=' expression {
	    	exp_astnode* args[2];
	    	args[0]=$1;
	    	args[1]=$3;
        	($$)=new op_astnode2(args, "ASSIGN_EXP");
	    }
	    | INT_CONSTANT {
	    	($$) = new intconst_astnode($1);
	    }
		| FLOAT_CONSTANT {
			($$) = new floatconst_astnode($1);
		}
	    | STRING_LITERAL {
	    	($$) = new stringconst_astnode($1);
	    }
		| '(' expression ')' {
			($$) = $2;
		}
		;

l_expression
        : IDENTIFIER {
        	($$) = new identifier_astnode($1);
        }
        | l_expression '[' expression ']' {
        	($$) = new arrayref_astnode($1, $3);
        }
        | '*' l_expression {
        	($$) = new deref_astnode($2);
        }
        | '&' l_expression {
        	($$) = new pointer_astnode($2);
        }
        | l_expression '.' IDENTIFIER {
        	($$) = new member_astnode($1, new identifier_astnode($3)); 
        }
        | l_expression PTR_OP IDENTIFIER {
        	($$) = new arrow_astnode($1, new identifier_astnode($3));
        }
        ;

expression_list
        : expression {
        	($$) = vector<exp_astnode*>(1, $1);
        }
        | expression_list ',' expression {
        	($$) = $1;
        	($$).push_back($3);
        }
		;

unary_operator
        : '-' {
        	($$) = "UMINUS";
        }
		| '!' {
			($$) = "NOT";
		}
		;

selection_statement
        : IF '(' expression ')' statement ELSE statement {
        	stmt_astnode* args[2];
        	args[0]=$5;
        	args[1]=$7;
        	($$) = new if_astnode($3, args);
        }
		;

iteration_statement
		: WHILE '(' expression ')' statement {
			($$) = new while_astnode($3, $5);
		}
		| FOR '(' expression ';' expression ';' expression ')' statement {
			exp_astnode* args[3];
			args[0]=$3;
			args[1]=$5;
			args[2]=$7;
			($$) = new for_astnode(args, $9);
		}
		;

declaration_list
        : declaration  					
        | declaration_list declaration
		;

declaration
		: type_specifier declarator_list';' 
		;

declarator_list
		: declarator
		| declarator_list ',' declarator 
	 	;                                                                                                                                                                                                                                                                                                            test.c                                                                                              0000664 0001750 0001750 00000000141 12660043304 012123  0                                                                                                    ustar   pradyot                         pradyot                                                                                                                                                                                                                struct t{
	int x;
	int y;
};

int main(){
	struct t p;
	p -> u = y;
	&l = 2.4;
	a[i] = b[j][k];
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               