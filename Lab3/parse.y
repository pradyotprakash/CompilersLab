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
// 1) pointer and array declaration, usage
// 2) pointer, array, references weirdness



translation_unit 
		:  struct_specifier
 		| function_definition {
 			// cout<<"--------------"<<endl;
 			// gst.print();
 		}
	 	| translation_unit function_definition {
	 		//cout<<"------------"<<endl;
	 		//gst.print();
	 	}
		| translation_unit struct_specifier
		;

struct_specifier 
		: STRUCT IDENTIFIER '{' {curStruct = "struct "+($2);} declaration_list '}' ';' {
			localSymbolTable lst;
			lst.symbols.clear();
			int offset = 0;
			for(unsigned int i=0;i<($5).size();++i){
				localSymbolTableRow lstr;
				variable temp = ($5)[i];
				// if(isBasic(temp.vtype) && temp.vtype.base.type=="struct "+$2){
				// 	showError("Declaring struct as member of itself");
				// }
				temp.offset=offset;
				temp.size=getSize(temp); 
				offset+=temp.size;
				lstr.v = temp;
				lst.symbols[lstr.v.vname] = lstr;
			}
			string sname = "struct "+$2;
			if(gst.symboltables.find(sname)!=gst.symboltables.end())
				showError("Struct redeclaration");
			gst.symboltables[sname]=lst;
			curStruct = "";
			gst.structsDefined.insert(sname);
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

			cout<<curFuncName<<" AST Starts Now:"<<endl;
			hasReturn=false;
		} 
		compound_statement {	
			localSymbolTable lst;
			lst.symbols.clear();
			int offset=0;
			
			if(($1).type!="void" && !hasReturn){
				showWarning("Non-void function does not have return statement");
			}

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
			string fname = "function "+($2).v.vname;
			if(!(gst.symboltables.find(fname)==gst.symboltables.end())){
				showError("Function redefinition");
			}
			gst.symboltables[fname]=lst;


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
	: IDENTIFIER  '(' {curFuncName="function "+($1);} parameter_list ')' {
		globalSymbolTableRow gstr;
		gstr.isFunction = true;
		baseType bt("FUNC", 0);
		vector<int> ve(0);
		type t(bt, ve);
		
		variable v(t, $1, 0, 0);
		gstr.v = v;
		gstr.args.clear();
		vector<variable> args;
		args = $4;
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
			showError("Array dimensions must be intconstants");
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
			identifier_astnode* temp = new identifier_astnode($1);
			if(curLocal.symbols.find($1)==curLocal.symbols.end()){
				showError("Variable not declared before");
			}
			else temp->expType = curLocal.symbols[($1)].v.vtype;
			temp->lvalue=true;
			temp->isLocal=true;
			($$)=temp;
		}
		| INT_CONSTANT {
			auto temp = new intconst_astnode($1);
			temp->canBeIndex=true;
			temp->expvalue = $1;
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
		} 
		| FLOAT_CONSTANT {
			auto temp = new floatconst_astnode($1);
			temp->expType = type(baseType("float", 0), vector<int>(0));
			($$)=temp;
		}
		| STRING_LITERAL {
			auto temp = new stringconst_astnode($1);
			temp->expType = type(baseType("string", 0), vector<int>(0));
			($$)=temp;
		}
		| '(' expression ')' {
			$$ = $2;
		}
		;

compound_statement
		: '{' '}' {
			auto temp = new seq_astnode(std::vector<stmt_astnode*>(1, new empty_astnode()));
			temp->print(0);
			cout<<"\n\n\n";
			($$)=temp;
		}
		| '{' {
			for(variable v: gst.symbols[curFuncName].args){
					localSymbolTableRow lstr;
					variable temp = v;
					lstr.v=temp;
					if(curLocal.symbols.find(lstr.v.vname) != curLocal.symbols.end()){
						showError("Variable redeclaration");
					}
					else curLocal.symbols[lstr.v.vname]=lstr;
				}

			}
			statement_list '}' {
			auto temp = new seq_astnode($3);
			temp->print(0);
			cout<<"\n\n\n";
			($$)=temp;
		}
		| '{' declaration_list {
				for(variable v: gst.symbols[curFuncName].args){
					localSymbolTableRow lstr;
					variable temp = v;
					lstr.v=temp;
					if(curLocal.symbols.find(lstr.v.vname) != curLocal.symbols.end()){
						showError("Variable redeclaration");
					}
					else{
						if(temp.vtype.base.type[0] == 's'){
							if(gst.symboltables.find(temp.vtype.base.type) == gst.symboltables.end()){
								showError("struct definition for \"" + temp.vtype.base.type + "\" does not exist in this declaration", -1);
							}
						}
						curLocal.symbols[lstr.v.vname]=lstr;
					}
				}
				for(unsigned int i = 0; i<($2).size(); i++){
					localSymbolTableRow lstr;
					variable temp = ($2)[i];
					lstr.v=temp;
					if(curLocal.symbols.find(lstr.v.vname) != curLocal.symbols.end()){
						showError("Variable redeclaration");
					}
					else{
						if(temp.vtype.base.type[0] == 's'){
							if(gst.symboltables.find(temp.vtype.base.type) == gst.symboltables.end()){
								showError("struct definition for \"" + temp.vtype.base.type + "\" does not exist in this declaration", -1);
							}
						}
						curLocal.symbols[lstr.v.vname]=lstr;
					}
				}
			}
			statement_list '}' {
				auto temp = new seq_astnode($4);
				temp->print(0);
				cout<<"\n\n\n";
				temp->declarations = $2;
				($$)=temp;
			}
		;

statement_list
		: statement {
			($$)=std::vector<stmt_astnode*>(1, $1);
		}
		| statement_list statement {
			auto temp=$1;
			temp.push_back($2);
			($$)=temp;
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
			if(($2)->isAddress){
				showError("Can't return reference to a local variable");
			}
			hasReturn=true;
			auto temp=new return_astnode($2);
			if(gst.symbols[curFuncName].v.vtype.base.type == "void")
				showError("void functions can't have a return type", -1);
			unaryTypeCheck(gst.symbols[curFuncName].v.vtype, $2);
			($$)=temp;
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
			// TODO: Unary typecheck
			if(($1)->expType.sizes.size()!=0){
				showError("Whole array assignments not allowed!");
			}
			unaryTypeCheck(($1)->expType, $3);
			if(!($1)->lvalue){
				showError("Cannot assign a value to a non-lvalue");	
			}
			$$ = new assign_exp_astnode($1, $3);
			
		};

logical_or_expression			// The usual hierarchy that starts here...
	: logical_and_expression {
		$$ = $1;
	}
		| logical_or_expression OR_OP logical_and_expression{
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "OR");
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
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
			auto temp=new op_astnode2(args, "AND");
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
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
			auto temp=new op_astnode2(args, "EQ_OP");
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
		}
		| equality_expression NE_OP relational_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "NE_OP");
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
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
			auto temp=new op_astnode2(args, "LT");
			binaryTypeCheck($1, $3);
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
		}
		| relational_expression '>' additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "GT");
			binaryTypeCheck($1, $3);
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
		}
		| relational_expression LE_OP additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "LE_OP");
			binaryTypeCheck($1, $3);
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
		}
		| relational_expression GE_OP additive_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "GE_OP");	
			binaryTypeCheck($1, $3);
			temp->expType = type(baseType("int", 0), vector<int>(0));
			($$)=temp;
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
			binaryTypeCheck($1, $3);
			auto temp=new op_astnode2(args, "PLUS");
			temp->expType = ($1)->expType;
			if(!isBasic(temp->expType)){
				showError("Cannot operate on non-numberic types");
			}
			if(temp->expType.base.type!="int" && temp->expType.base.type!="float"){
				showError("Cannot operate on non-numberic types");
			}
			($$)=temp;
		}
		| additive_expression '-' multiplicative_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "MINUS");
			binaryTypeCheck($1, $3);
			temp->expType = ($1)->expType;
			if(!isBasic(temp->expType)){
				showError("Cannot operate on non-numberic types");
			}
			if(temp->expType.base.type!="int" && temp->expType.base.type!="float"){
				showError("Cannot operate on non-numberic types");
			}
			($$)=temp;
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
			auto temp=new op_astnode2(args, "MULT");
			binaryTypeCheck($1, $3);
			temp->expType = ($1)->expType;
			if(!isBasic(temp->expType)){
				showError("Cannot operate on non-numberic types");
			}
			if(temp->expType.base.type!="int" && temp->expType.base.type!="float"){
				showError("Cannot operate on non-numberic types");
			}
			($$)=temp;
		}
		| multiplicative_expression '/' unary_expression {
			exp_astnode* args[2];
			args[0]=$1;
			args[1]=$3;
			auto temp=new op_astnode2(args, "DIV");
			binaryTypeCheck($1, $3);
			temp->expType = ($1)->expType;
			if(!isBasic(temp->expType)){
				showError("Cannot operate on non-numberic types");
			}
			if(temp->expType.base.type!="int" && temp->expType.base.type!="float"){
				showError("Cannot operate on non-numberic types");
			}
			($$)=temp;
		}
		;

unary_expression
		: postfix_expression {
			($$)=$1;
		}
		| unary_operator postfix_expression {
			auto temp=new op_astnode1($2, $1);
			temp->expType = ($2)->expType;
			if(($1)=="ADDRESSOF"){
				temp->expType.base.pointers++;
				if(!($2)->lvalue){
					showError("Cannot take adress of nonlvalue");
				}
				temp->isAddress=true;
			}
			if(($1)=="DEREF"){
				if(temp->expType.base.pointers != 0 && temp->expType.base.type == "void")
					showError("Can't dereference a 'void' variable");

				temp->expType.base.pointers--;
				if(temp->expType.base.pointers < 0){
					showError("Dereferencing non pointer type");
				}
				temp->lvalue=true;
			}
			($$)=temp;
		}
		;

postfix_expression
	: 	primary_expression {
			($$) = $1;
		}
		| IDENTIFIER '(' ')' {
			auto temp = new funcall_astnode($1, std::vector<exp_astnode*>(0));
			if(gst.symbols.find($1)==gst.symbols.end()){
				showError("Function not defined");
			}
			temp->expType = gst.symbols[($1)].v.vtype;
			if(gst.symbols[($1)].args.size()!=0){
				showError("Incorrect number of arguments");
			}
			($$)=temp;
		}
		| IDENTIFIER '(' {
				parameterTypes.clear();
				if(gst.symbols.find($1)==gst.symbols.end()){
					showError("Function not defined");
				}
				for(auto x: gst.symbols[($1)].args){
					parameterTypes.push_back(x.vtype);
				}
			}
			expression_list ')' {
				auto temp = new funcall_astnode($1, $4);
				temp->expType = gst.symbols[($1)].v.vtype;
				if(parameterTypes.size()!=0){
					showError("Incorrect number of arguments");
				}
				($$)=temp;
			}
		| postfix_expression '[' expression ']' {
			auto temp = new arrayref_astnode($1, $3);
			type t = ($3)->expType;
			if(t.base.type != "int"){
				showError("Array index not integer", 0);
			}
			if(($1)->expType.sizes.size()==0){
				showError("[ ] operator not defined", -1);
			}
			else {
				($1)->expType.sizes.erase(($1)->expType.sizes.begin());
			}
			temp->expType = ($1)->expType;
			temp->lvalue=true;
			($$)=temp;
		}
		| postfix_expression '.' IDENTIFIER {
			type b;
			type t = ($1)->expType;
			if(t.base.pointers!=0 || t.sizes.size()!=0 || t.base.type[0]!='s'){
				showError("DOT operator not on a struct type");
			}
			else{
				if(gst.symboltables.find(t.base.type)==gst.symboltables.end()){
					showError("struct has not been declared");
				}
				localSymbolTable lst = gst.symboltables[t.base.type];
				if(lst.symbols.find($3)==lst.symbols.end()){
					showError("member variable not declared in struct");
				}
				else b=lst.symbols[$3].v.vtype;
			}
			auto temp = new member_astnode($1, new identifier_astnode($3));
			if(b.base.type!="")
				temp->expType=b;
			temp->lvalue=true;
			($$)=temp;
		}
		| postfix_expression PTR_OP IDENTIFIER {
			type b;
			type t = ($1)->expType;
			if(!((t.base.pointers==1 && t.sizes.size()==0) || 
				(t.base.pointers==0 && t.sizes.size()==1))
				)
				 {
				showError("PTROP operator not on a struct* type");
			}
			else if(t.base.type[0]!='s'){
				showError("PTROP operator not on a struct* type");	
			}
			else{
				localSymbolTable lst = gst.symboltables[t.base.type];
				if(lst.symbols.find($3)==lst.symbols.end()){
					showError("member variable not declared in struct");
				}
				else b=lst.symbols[$3].v.vtype;
			}
			auto temp = new arrow_astnode($1, new identifier_astnode($3));
			if(b.base.type!="")
				temp->expType=b;	
			temp->lvalue=true;
			($$)=temp;
		}
		| postfix_expression INC_OP {
			op_astnode1* temp = new op_astnode1($1, "PP");
			temp->expType = ($1)->expType;
			temp->lvalue=false;
			if(!($1)->lvalue){
				showError("Can't perform ++ on non-lvalue");
			}
			if(!isBasic(temp->expType) ){
				showError("Can't perform ++ on not numeric type");
			}
			($$)=temp;
			
		}
	;

expression_list
		: expression {
			if(parameterTypes.size()==0){
				showError("Incorrect number of arguments", -1); // TODO
			}
			else{
				unaryTypeCheck(parameterTypes[0], $1);
				auto temp = vector<exp_astnode*>(1, $1);
				parameterTypes.erase(parameterTypes.begin());
				($$)=temp;
			}
		}
		| expression_list ',' expression {
			if(parameterTypes.size()==0){
				showError("Incorrect number of arguments", -1); // TODO
			}
			else{
				unaryTypeCheck(parameterTypes[0], $3);
				auto temp = $1;
				temp.push_back($3);
				parameterTypes.erase(parameterTypes.begin());
				($$)=temp;
			}
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
		
		type temp(($1), vector<int>(0));
		if(($1).type==curStruct){
			for(auto v: ($2)){
				if(v.vtype.base.pointers==0)
					showError("Declaring struct as member of itself");
			}
			
		}
				
		for(int i=0;i<($2).size();++i){
			($2)[i].vtype.base.type = ($1).type;
			if(($2)[i].vtype.base.type == "void" && ($2)[i].vtype.base.pointers == 0){
				showError("variable can't be of type void");
			}
		}

		// if(($1).type[0]=='s' && gst.symboltables.find("struct "+($1).type)==gst.symboltables.end())
		// 	showError("Struct not defined");

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