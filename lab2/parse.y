%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT RETURN LE_OP GE_OP EQ_OP NE_OP OR_OP AND_OP INC_OP IF ELSE WHILE FOR INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL IDENTIFIER STRUCT PTR_OP

%polymorphic STRING: std::string; EXP_ASTNODE: exp_astnode*; STMT_ASTNODE: stmt_astnode*; REF_ASTNODE: ref_astnode*; STMT_LIST: std::vector<stmt_astnode*>; EXP_LIST: std::vector<exp_astnode*>; INT_CONST: intconst_astnode*; FLOAT_CONST: floatconst_astnode*; STRING_LITERAL: stringconst_astnode*; IDENTIFIER_ASTNODE: identifier_astnode*; OP_ASTNODE1: op_astnode1*; OP_ASTNODE2: op_astnode2*; FUNCALL_ASTNODE: funcall_astnode*; SEQ_ASTNODE: seq_astnode*; RETURN_ASTNODE: return_astnode*; ASS_ASTNODE: ass_astnode*; IF_ASTNODE: if_astnode*; EMPTY_ASTNODE: empty_astnode*; WHILE_ASTNODE: while_astnode*; FOR_ASTNODE: for_astnode*; ARRAYREF_ASTNODE: arrayref_astnode*; POINTER_ASTNODE: pointer_astnode*; DEREF_ASTNODE: deref_astnode*; INT: int; FLOAT: float;

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
			($$)->print();
		}		
		| '{' statement_list '}' {
			$$ = new seq_astnode($2);
			($$)->print();
		}
        | '{' declaration_list statement_list '}' {
        	$$ = new seq_astnode($3);
        	($$)->print();
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
			($$)=new ass_astnode($1, $3);
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
        	($$)=new op_astnode2(args, "ASSIGN");
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
        	//($$) = new arrayref_astnode($1, vector<exp_astnode*>(1, $3));
        }
        | '*' l_expression {
        	($$) = new deref_astnode($2);
        }
        | '&' l_expression {
        	($$) = new pointer_astnode($2);
        }
        | l_expression '.' IDENTIFIER {
        	($$) = new dotref_astnode($1, new identifier_astnode($3)); 
        }
        | l_expression PTR_OP IDENTIFIER {
        	($$) = new ptrop_astnode($1, new identifier_astnode($3));
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
	 	;