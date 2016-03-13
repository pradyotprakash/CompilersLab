%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT RETURN LE_OP GE_OP EQ_OP NE_OP OR_OP AND_OP INC_OP IF ELSE WHILE FOR INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL IDENTIFIER STRUCT PTR_OP

%polymorphic STRING: std::string; EXP_ASTNODE: exp_astnode*; STMT_ASTNODE: stmt_astnode*; REF_ASTNODE: ref_astnode*; STMT_LIST: std::vector<stmt_astnode*>; EXP_LIST: std::vector<exp_astnode*>; INT_CONST: intconst_astnode*; FLOAT_CONST: floatconst_astnode*; STRING_LITERAL: stringconst_astnode*; IDENTIFIER_ASTNODE: identifier_astnode*; OP_ASTNODE1: op_astnode1*; OP_ASTNODE2: op_astnode2*; FUNCALL_ASTNODE: funcall_astnode*; SEQ_ASTNODE: seq_astnode*; RETURN_ASTNODE: return_astnode*; IF_ASTNODE: if_astnode*; EMPTY_ASTNODE: empty_astnode*; WHILE_ASTNODE: while_astnode*; FOR_ASTNODE: for_astnode*; ARRAYREF_ASTNODE: arrayref_astnode*; POINTER_ASTNODE: pointer_astnode*; DEREF_ASTNODE: deref_astnode*; INT: int; FLOAT: float; VARIABLE : variable; BASETYPE: baseType; VVARIABLE: vector<variable>; GLOBALSYMBOLTABLEROW: globalSymbolTableRow;

%type <STRING> unary_operator IDENTIFIER STRING_LITERAL
%type <INT> INT_CONSTANT
%type <FLOAT> FLOAT_CONSTANT

%type <EXP_ASTNODE> expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression unary_expression postfix_expression primary_expression logical_or_expression

%type <STMT_ASTNODE> compound_statement statement assignment_statement selection_statement iteration_statement

%type <EXP_LIST> expression_list
%type <STMT_LIST> statement_list

%type <VARIABLE> declarator parameter_declaration
%type <VVARIABLE> declarator_list declaration declaration_list parameter_list
%type <BASETYPE> type_specifier
%type <GLOBALSYMBOLTABLEROW> fun_declarator

%%

// TODO
// 1) +, < for int and float
// 2) typecasting = and to function parameters
// 3) compatibility of two types
// 4) return type of body of statements
// 5) give types to each expression
// 6) pointer, array, references weirdness
// 7) errors!


translation_unit 
		:  struct_specifier
 		| function_definition {
 			cout<<"--------------"<<endl;
 			gst.print();
 		}
	 	| translation_unit function_definition {
	 		cout<<"------------"<<endl;
	 		gst.print();
	 		// cout<<d__lineNr<<endl;
	 	}
		| translation_unit struct_specifier
		;

struct_specifier 
		: STRUCT IDENTIFIER '{' declaration_list '}' ';' {
			localSymbolTable lst;
			lst.symbols.clear();
			int offset = 0;
			for(unsigned int i=0;i<($4).size();++i){
				localSymbolTableRow lstr;
				variable temp = ($4)[i];
				temp.offset=offset;
				temp.size=getSize(temp); 
				offset+=temp.size;
				lstr.v = temp;
				lst.symbols[lstr.v.vname] = lstr;
			}
			gst.symboltables["struct "+$2]=lst;
			// TODO assign $$?

		}
		;

function_definition
	: type_specifier fun_declarator 
		{
			curFuncName=($2).v.vname; 
			curLocal.symbols.clear(); 
			($2).v.vtype.base.type = ($1).type;
			gst.symbols[($2).v.vname]=($2);
		} 
		compound_statement {
		
		localSymbolTable lst;
		lst.symbols.clear();
		int offset=0;
		
		vector<variable> args = gst.symbols[($2).v.vname].args;
		for(unsigned int i = 0; i<args.size(); i++){
			localSymbolTableRow lstr;
			variable temp = args[i];
			temp.offset = offset;
			temp.size = getSize(temp); 
			offset+=temp.size;
			lstr.v=temp;
			lst.symbols[lstr.v.vname]=lstr;
		}

		for(unsigned int i = 0; i<($4)->declarations.size(); i++){
			localSymbolTableRow lstr;
			variable temp = ($4)->declarations[i];
			temp.offset = offset;
			temp.size = getSize(temp); 
			offset+=temp.size;
			lstr.v=temp;
			lst.symbols[lstr.v.vname]=lstr;
		}
		gst.symboltables["function "+($2).v.vname]=lst;
		// TODO assign $$?

	}
	;

type_specifier
		: VOID {
			baseType v;
			v.type = "void";
			v.pointers=0;
			$$ = v;
		}
		| INT {
			baseType v;
			v.type = "int";
			v.pointers=0;
			$$ = v;
		}   
		| FLOAT {
			baseType v;
			v.type = "float";
			v.pointers=0;
			$$ = v;
		}
		| STRUCT IDENTIFIER {
			baseType v;
			v.type = "struct "+$2;
			v.pointers=0;
			$$ = v;
		}
		;

fun_declarator
	: IDENTIFIER '(' parameter_list ')' {
		globalSymbolTableRow gstr;
		gstr.isFunction = true;
		baseType bt("FUNC", 0);
		vector<int> ve(0);
		type t(bt, ve);
		variable v(t, $1, 0, 0);
		gstr.v = v;
		gstr.args.clear();
		vector<variable> args;

		args = $3;
		gstr.args = args;
		$$ = gstr;
	}
	| IDENTIFIER '(' ')' {
		
		globalSymbolTableRow gstr;
		gstr.isFunction = false;
		baseType bt("FUNC", 0);
		vector<int> ve(0);
		type t(bt, ve);
		variable v(t, $1, 0, 0);
		gstr.v = v;
		gstr.args.clear();
		$$ = gstr;
	}
	| '*' fun_declarator {
		($2).v.vtype.base.pointers++;
		$$ = $2;
	}
	;					  


parameter_list
	: parameter_declaration {
		vector<variable> v(1, $1);
		$$ = v;
	}
	| parameter_list ',' parameter_declaration {
		($1).push_back($3);
		$$ = $1;	
	}
	;

parameter_declaration
	: type_specifier declarator {
		($2).vtype.base.type = ($1).type;
		$$ = $2;
	}
	;

declarator
	: IDENTIFIER {
		baseType b("", 0);
		vector<int> ve(0);
		type t(b, ve);
		variable v(t, $1, 0, 0);
		$$ = v;
	}
	| declarator '[' primary_expression']' {
		if(!($3)->canBeIndex){
			cerr<<"Only integers allowed!\n";
		}
		else
			($1).vtype.sizes.push_back(($3)->expvalue);
		$$ = $1;
	}
	| '*' declarator {
		($2).vtype.base.pointers++;
		$$ = $2;
	}
	;

primary_expression	  
		: IDENTIFIER {
			$$ = new identifier_astnode($1);
			($$)->expType = curLocal.symbols[($1)].v.vtype;
		}
		| INT_CONSTANT {
			$$ = new intconst_astnode($1);
			($$)->canBeIndex=true;
			($$)->expvalue = $1;
			($$)->expType = type(baseType("int", 0), vector<int>(0));
		} 
		| FLOAT_CONSTANT {
			$$ = new floatconst_astnode($1);
			($$)->expType = type(baseType("float", 0), vector<int>(0));
		}
		| STRING_LITERAL {
			$$ = new stringconst_astnode($1);
			($$)->expType = type(baseType("string", 0), vector<int>(0));
		}
		| '(' expression ')' {
			$$ = $2;
		}
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
		| '{' declaration_list {
				for(unsigned int i = 0; i<($2).size(); i++){
				localSymbolTableRow lstr;
				variable temp = ($2)[i];
				lstr.v=temp;
				curLocal.symbols[lstr.v.vname]=lstr;
				}
			}
			 statement_list '}' {
				$$ = new seq_astnode($4);
				($$)->print(0);
				($$)->declarations = $2;
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
			if(gst.symbols[curFuncName].v.vtype.base.type == "void")
				cerr<<"void functions can't have a return type"<<endl;
		}
		;

assignment_statement
	: ';' {
		($$)=new empty_astnode();
	}								
	|  expression ';'  {
		($$) = new assign_stmt_astnode($1);
	}
	;

expression								   
	:  logical_or_expression{
			$$ = $1;
		}
		|  unary_expression '=' expression {
			$$ = new assign_exp_astnode($1, $3);
			if(!($1)->valid || !($1)->lvalue){
				($$)->valid=false;
				($$)->lvalue=false;
			}

			// TODO: Unary typecheck


		};

logical_or_expression			// The usual hierarchy that starts here...
	: logical_and_expression {
		$$ = $1;
	}
		| logical_or_expression OR_OP logical_and_expression{
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "OR");

			($$)->expType = type(baseType("int", 0), vector<int>(0));
		}
	;
logical_and_expression:
		equality_expression {
			($$)=$1;
		}
		| logical_and_expression AND_OP equality_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "AND");
			($$)->expType = type(baseType("int", 0), vector<int>(0));
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

			($$)->expType = type(baseType("int", 0), vector<int>(0));
		}
		| equality_expression NE_OP relational_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "NE_OP");
			($$)->expType = type(baseType("int", 0), vector<int>(0));
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
			binaryTypeCheck($1, $3);
			($$)->expType = type(baseType("int", 0), vector<int>(0));
		}
		| relational_expression '>' additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "GT");
			binaryTypeCheck($1, $3);
			($$)->expType = type(baseType("int", 0), vector<int>(0));
		}
		| relational_expression LE_OP additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "LE_OP");
			binaryTypeCheck($1, $3);
			($$)->expType = type(baseType("int", 0), vector<int>(0));
		}
		| relational_expression GE_OP additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "GE_OP");	
			binaryTypeCheck($1, $3);
			($$)->expType = type(baseType("int", 0), vector<int>(0));
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

			binaryTypeCheck($1, $3);
			($$)->expType = ($1)->expType;
		}
		| additive_expression '-' multiplicative_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "MINUS");

			binaryTypeCheck($1, $3);
			($$)->expType = ($1)->expType;
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
			binaryTypeCheck($1, $3);
			($$)->expType = ($1)->expType;
		}
		| multiplicative_expression '/' unary_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			($$)=new op_astnode2(args, "DIV");
			binaryTypeCheck($1, $3);
			($$)->expType = ($1)->expType;
		}
		;

unary_expression
		: postfix_expression {
			($$)=$1;
		}
		| unary_operator postfix_expression {
			($$)=new op_astnode1($2, $1);
			$$->lvalue = $2->lvalue;
			$$->valid = $2->valid;
		}
		;

postfix_expression
	: primary_expression
		| IDENTIFIER '(' ')' {
			($$) = new funcall_astnode($1, std::vector<exp_astnode*>(0));
			($$)->expType = gst.symbols[($1)].v.vtype;
		}
		| IDENTIFIER '(' expression_list ')' {
			($$) = new funcall_astnode($1, $3);
			($$)->expType = gst.symbols[($1)].v.vtype;
		}
		| postfix_expression '[' expression ']' {
			($$) = new arrayref_astnode($1, $3);
			type t = ($1).expType;
			if(type.base.type != "int"){
				cerr<<"Array index not integer"<<endl;
			}
			t = 
			($$)->expType = ;
		}
		| postfix_expression '.' IDENTIFIER {
			($$) = new member_astnode($1, new identifier_astnode($3)); 
		}
		| postfix_expression PTR_OP IDENTIFIER {
			($$) = new arrow_astnode($1, new identifier_astnode($3));
		}
		| postfix_expression INC_OP {
			($$) = new op_astnode1($1, "PP");
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
		| '&' {
			($$) = "ADDRESSOF";
		}
		| '*' {
			($$) = "DEREF";
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
		: declaration {
			$$ = $1;
		}					
		| declaration_list declaration {
			vector<variable> v;
			v = $1;
			v.insert(v.end(), ($2).begin(), ($2).end());
			$$ = v;
		}
		;

declaration
	: type_specifier declarator_list';' {
		for(int i=0;i<($2).size();++i){
			($2)[i].vtype.base.type = ($1).type;
		}
		$$ = $2;
	}
	;

declarator_list
	: declarator {
		vector<variable> v(1, $1);
		$$ = v;
	}
	| declarator_list ',' declarator {
		vector<variable> v = $1;
		v.push_back($3);
		$$ = v;
	}
 	;