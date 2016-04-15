#include <typeinfo>
#include "ast.h"
#ifndef ASTCPP

string curFuncName;
localSymbolTable curLocal;
vector<type> parameterTypes;
string curStruct;
bool hasReturn;

int tempOffsets;

globalSymbolTable gst;

vector<stmt_astnode*> functions;

int getSize(variable v){
	string type = v.vtype.base.type;
	int baseSize=0;
	if(type == "int") baseSize=4;
	else if(type == "float") baseSize=4;
	else if(type == "void") baseSize=0;
	else if(type[0]=='s'){
		int sum = 0;
		localSymbolTable lst = gst.symboltables[type];
		for(auto l: lst.symbols){
			variable vv = l.second.v;
			sum+=getSize(vv);
		}
		baseSize=sum;
	}
	if(v.vtype.base.pointers!=0) baseSize=4;
	int mul = 1;
	for(auto i: v.vtype.sizes){
		mul*=i;
	}

	return baseSize*mul;
}

bool isBasic(type t){
	if(t.sizes.size() == 0 && t.base.pointers == 0 && t.base.type != "void")
		return true;
	return false;
}

void showError(string s, int lineNumber = -1){
	cerr<<"Error in line number: "<<lineno<<": "<<s<<endl;
	exit(0);
}

void showWarning(string s, int lineNumber = -1){
	cerr<<"Warning in line number: "<<lineno<<": "<<s<<endl;
}

bool operator == (const type& t1, const type& t2){
	if(t1.sizes!=t2.sizes) return false;
	if(t1.base.type!=t2.base.type) return false;
	if(t1.base.pointers!=t2.base.pointers) return false;
	return true;
}

void binaryTypeCheck(exp_astnode *e1, exp_astnode *e2){
	type t1 = e1->expType;
	type t2 = e2->expType;
		
	string s1 = t1.base.type;
	string s2 = t2.base.type;
	if(isBasic(t1) && isBasic(t2)){
		if(s1 == "string" && s2 != "string" || s2 == "string" && s1 != "string")
			showError("Incompatible types", -1);
		if(s1[0]=='s' || s2[0]=='s'){
			showError("Cannot operate on struct types");
		}
		if(s1 == "float" && s2 == "int"){
			e2->expType.base.type = "float";
			e2->typeCasted = true;
		}
		if(s1 == "int" && s2 == "float"){
			e1->expType.base.type = "float";
			e1->typeCasted = true;
		}
		return;
	}

	if(t1.sizes.size() == 0 && t2.sizes.size() == 0 && t1.base.pointers == 1 && t2.base.pointers == 1){
		if(t1.base.type == "void" || t2.base.type == "void")
			return;
	}

	// array type check
	if(t1.base.pointers ==  t2.base.pointers && t1.sizes.size() == t2.sizes.size()){
		if(t1.base.type != t2.base.type)
			showError("Incompatible types");
		for(int i=1;i<t1.sizes.size();++i){
			if(t1.sizes[i] != t2.sizes[i]){
				showError("Incompatible types!");
			}
		}
		return;
	}
	
	if(!(t1.sizes.size() == 0 && t1.base.pointers == 1+t2.base.pointers && t2.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}

	if(!(t2.sizes.size() == 0 && t2.base.pointers == 1+t1.base.pointers && t1.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}
}

void unaryTypeCheck(type t1, exp_astnode* e){
	type t2 = e->expType;
	// cerr<<t1.base.type<<" "<<e->expType.base.type<<endl;
	if(isBasic(t1) && isBasic(t2)){
		if(t1.base.type == "string" && t2.base.type != "string" ||
			t2.base.type == "string" && t1.base.type != "string"){
			showError("Incompatible types!", -1);
		}
		if(t2==t1) return;
		if(t1.base.type[0]=='s' || t2.base.type[0]=='s')
			showError("Incompatible types!");
		e->expType = t1;
		e->typeCasted=true;
		
		return;
	}

	if(t1.sizes.size() == 0 && t2.sizes.size() == 0 && t1.base.pointers == 1 && t2.base.pointers == 1){
		if(t1.base.type == "void" || t2.base.type == "void")
			return;
	}

	// if(t2.base.type == "void" && t1.base.type != "void")
		// showError("Can't cast void to non-void type");

	// array type check
	if(t1.base.pointers ==  t2.base.pointers && t1.sizes.size() == t2.sizes.size()){
		if(t1.base.type != t2.base.type)
			showError("Incompatible types");
		for(int i=1;i<t1.sizes.size();++i){
			if(t1.sizes[i] != t2.sizes[i]){
				showError("Incompatible types!");
			}
		}
		return;
	}
	
	if(!(t1.sizes.size() == 0 && t1.base.pointers == 1+t2.base.pointers && t2.sizes.size() == 1) || t1.base.type != t2.base.type){
		showError("Incompatible array types!");
		return;
	}

	//if(e->expType.base.type=="void") showError("Incompatible type!");
}

void stmt_astnode::print(int l){
	std::cout<<"This should never be called; stmt_astnode"<<std::endl;
}

void stmt_astnode::gencode(int accessType){
	cout<<"This should never be called; gencode stmt_astnode"<<endl;
	;
}

void exp_astnode::print(int l){
	std::cout<<"This should never be called; exp_astnode"<<std::endl;
}

void exp_astnode::gencode(int accessType){
	std::cout<<"This should never be called; gencode exp_astnode"<<std::endl;
}

void ref_astnode::print(int l){
	std::cout<<"This should never be called; ref_astnode"<<std::endl;
}

void ref_astnode::gencode(int accessType){
	std::cout<<"This should never be called; gencode ref_astnode"<<std::endl;
}

empty_astnode::empty_astnode(){

}

void empty_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Empty)";
}

void empty_astnode::gencode(int accessType){
	
}

seq_astnode::seq_astnode(std::vector<stmt_astnode*> n){
    nodes = n;
}

void seq_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Block [";
	for(unsigned int i = 0; i<nodes.size(); i++)
		nodes[i]->print(0);
	std::cout<<"])\n";
}

void seq_astnode::gencode(int accessType){
	for(unsigned int i=0; i<nodes.size(); i++){
		int defaultOffset = tempOffsets;
		nodes[i]->gencode(0);
		tempOffsets=defaultOffset;
	}
}

assign_stmt_astnode::assign_stmt_astnode(exp_astnode* n2){
    r = n2;
}

void assign_stmt_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	r->print(0);
}

void assign_stmt_astnode::gencode(int accessType){
	r->gencode(0);
}

assign_exp_astnode::assign_exp_astnode(exp_astnode* n1, exp_astnode* n2){
    l = n1;
    r = n2;
}

void assign_exp_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Ass ";
	this->l->print(0);
	std::cout<<" ";
	if(r->typeCasted) cout<<"(to_"+r->expType.base.type<<" ";
	r->print(0);
	if(r->typeCasted) cout<<") ";
	
	std::cout<<")\n";
}

void assign_exp_astnode::gencode(int accessType){
	// TODO: assigning for structs and floats

	l->gencode(2);
	r->gencode(1);
	cout<<"# assignment"<<endl;
	cout<<"lw $t0, "<<r->tempOffset<<"($sp)"<<endl;
	cout<<"lw $t1, "<<l->tempOffset<<"($sp)"<<endl;
	cout<<"sw $t0, 0($t1)"<<endl;
}

return_astnode::return_astnode(exp_astnode* n){
    node = n;
}

void return_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Return ";
	if(node->typeCasted) cout<<"(to_"+node->expType.base.type<<" ";
	node->print(0);
	if(node->typeCasted) cout<<") ";
	std::cout<<") ";

}

void return_astnode::gencode(int accessType){
	node->gencode(1);
	// TODO: struct copying
	// TODO: typecasting
	int rlocation = 8 + gst.getTotalArgsSize("function "+curFuncName);
	cout<<"# copying to RV"<<endl;
	cout<<"lw $t0, "<<node->tempOffset<<"($sp)"<<endl;
	cout<<"sw $t0, "<<rlocation<<"($sp)"<<endl;
	cout<<"add $v0, $t0, $0"<<endl;
	cout<<"# returning"<<endl;
	cout<<"lw $ra, 4($sp)"<<endl;
	cout<<"lw $sp, 0($sp)"<<endl;
	cout<<"jr $ra"<<endl;

}

if_astnode::if_astnode(exp_astnode* n1, stmt_astnode** n2){
    node = n1;
    nodes[0] = n2[0];
    nodes[1] = n2[1];
}

void if_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(If ";
	node->print(0);
	std::cout<<" \n";
	nodes[0]->print(l+4);
	std::cout<<" \n";
	nodes[1]->print(l+4);
	std::cout<<") \n";
}

void if_astnode::gencode(int accessType){
	// TODO: everything
}

while_astnode::while_astnode(exp_astnode* n1, stmt_astnode* n2){
    node = n1;
    node2 = n2;
}

void while_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(While ";
	node->print(0);
	std::cout<<" ";
	node2->print(0);
	std::cout<<") ";
}

void while_astnode::gencode(int accessType){
	// TODO: everything
}

for_astnode::for_astnode(exp_astnode** n1, stmt_astnode* n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	nodes[2]=n1[2];
	node=n2;
}

void for_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(For\n";
	for(int i=0; i<3; i++){
		nodes[i]->print(l + 4);
		std::cout<<" \n";
	}
	node->print(l+4);
	std::cout<<")\n";
}

void for_astnode::gencode(int accessType){
	// TODO: everything
}

op_astnode2::op_astnode2(exp_astnode** n1, std::string n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	op=n2;
}

void op_astnode2::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	bool toCast = true;
	if(op=="OR" || op=="AND")
		toCast=false;
	std::cout<<"("<<op;
	if(nodes[0]->expType.base.type == "int" && toCast)
		std::cout<<"-INT ";
	if(nodes[0]->expType.base.type == "float" && toCast)
		std::cout<<"-FLOAT ";
	
	if(nodes[0]->typeCasted && toCast)
		cout<<"(to_" + nodes[0]->expType.base.type;
	nodes[0]->print(0);
	if(nodes[0]->typeCasted && toCast)
		cout<<") ";
	
	if(nodes[1]->typeCasted && toCast)
		cout<<"(to_" + nodes[1]->expType.base.type;
	nodes[1]->print(0);
	if(nodes[1]->typeCasted && toCast)
		cout<<") ";
	std::cout<<") ";
}

void op_astnode2::gencode(int accessType){
	// TODO: type casting, boolean!

	nodes[0]->gencode(1);
	nodes[1]->gencode(1);
	cout<<"# Load values onto registers"<<endl;
	cout<<"lw $t0, "<<nodes[0]->tempOffset<<"($sp)"<<endl;
	cout<<"lw $t1, "<<nodes[1]->tempOffset<<"($sp)"<<endl;
	
	cout<<"# generate op code"<<endl;
	if(op == "PLUS")
		cout<<"add $t0, $t0, $t1"<<endl;
	else if(op == "MINUS")
		cout<<"sub $t0, $t0, $t1"<<endl;
	else if(op == "MULT"){
		cout<<"mul $t0, $t0, $t1"<<endl;
	}
	else if(op == "DIV"){
		cout<<"div $t0, $t0, $t1"<<endl;
	}
	tempOffsets -= 4;
	tempOffset = tempOffsets;
	cout<<"# store the value back into memory"<<endl;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;

}

op_astnode1::op_astnode1(exp_astnode* n1, std::string n2){
	node=n1;
	op=n2;
}

void op_astnode1::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"("<<op<<" ";
	node->print(0);
	std::cout<<") ";
}

void op_astnode1::gencode(int accessType){
	// TODO: everything
}

funcall_astnode::funcall_astnode(std::string n1, std::vector<exp_astnode*> n2){
	funcName=n1;
	nodes=n2;
}

void funcall_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( "<<funcName<<" (";
	for(int i=0;i<nodes.size();++i){
		if(nodes[i]->typeCasted) cout<<"(to_"<<nodes[i]->expType.base.type;
		nodes[i]->print(0);	
		if(nodes[i]->typeCasted) cout<<") ";
	}
	std::cout<<") ) ";
}

void funcall_astnode::gencode(int accessType){
	// TODO: everything
}

floatconst_astnode::floatconst_astnode(float n){
	val=n;
}

void floatconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(FloatConst "<<val<<") ";
}

void floatconst_astnode::gencode(int accessType){
	// TODO: everything
}

intconst_astnode::intconst_astnode(int n){
	val=n;
}

void intconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(IntConst "<<val<<") ";
}

void intconst_astnode::gencode(int accessType){
	cout<<"# loading intconst"<<endl;
	cout<<"addi $t0, $0, "<<val<<endl;
	tempOffsets-=4;
	tempOffset = tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

stringconst_astnode::stringconst_astnode(std::string n){
	val=n;
}

void stringconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(StringConst "<<val<<") ";
}

void stringconst_astnode::gencode(int accessType){
	// TODO: everything
}

identifier_astnode::identifier_astnode(std::string n){
	name=n;
}

void identifier_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Id \""<<name<<"\") ";
}

void identifier_astnode::gencode(int accessType){
	localSymbolTable lst = gst.symboltables["function "+curFuncName];
	int variableOffset = lst.symbols[name].v.offset;
	if(accessType==0){
		cerr<<"Should never happen"<<endl;
	}
	cout<<"addi $t0, $sp, "<<variableOffset<<endl;
	if(accessType==1) cout<<"lw $t0, 0($t0)"<<endl;
	tempOffsets-=4;
	tempOffset=tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;		
}

arrayref_astnode::arrayref_astnode(exp_astnode* b, exp_astnode* o){
	base = b;
	offset = o;
	this->lvalue = true;
}

void arrayref_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( arrayRef";
	base->print(0);
	std::cout<<" [";
	offset->print(0);
	std::cout<<"] ";
	std::cout<<") ";
}

void arrayref_astnode::gencode(int accessType){
	if(accessType==0) cerr<<"Should never happen"<<endl;
	base->gencode(2);
	offset->gencode(1);
	int t=4;
	type tempType = base->expType;
	if(tempType.sizes.size()!=0){
		tempType.sizes.erase(tempType.sizes.begin());
		t = getSize(variable(tempType, "", 0, 0));
	}
	cout<<"lw $t0, "<<offset->tempOffset<<"($sp)"<<endl;
	cout<<"muli $t0, $t0, "<<t<<endl;
	cout<<"lw $t1, "<<base->tempOffset<<"($sp)"<<endl;
	cout<<"sub $t0, $t1, $t0"<<endl;
	if(accessType==1) cout<<"lw $t0, 0($t0)"<<endl;
	tempOffsets -= 4;
	tempOffset=tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

pointer_astnode::pointer_astnode(ref_astnode* n){
	node=n;
}

void pointer_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Pointer ";
	node->print(0);
	std::cout<<") ";
}

void pointer_astnode::gencode(int accessType){
	int t = node->tempOffset;
	cout<<"lw $t0, "<<t<<"($sp)"<<endl;
	tempOffsets-=4;
	tempOffset=tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

deref_astnode::deref_astnode(ref_astnode* n){
	node=n;
}

void deref_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(DEREF ";
	node->print(0);
	std::cout<<") ";
}

void deref_astnode::gencode(int accessType){

}

member_astnode::member_astnode(exp_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
	this->lvalue = true;
}

void member_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(DOT ";
	node->print(0);
	std::cout<<" ";
	id->print(0);
	std::cout<<") ";
}

void member_astnode::gencode(int accessType){
	node->gencode(2);
	int offset = node->tempOffset;
	localSymbolTable lst = gst.symboltables[node->expType.base.type];
	int varOffset = lst.symbols[id->name].v.offset;
	cout<<"sw $t0, "<<node->tempOffset<<"($sp)"<<endl;
	cout<<"addi $t0, $t0, "<<varOffset<<endl;
	if(accessType==1) cout<<"lw $t0, 0($t0)"<<endl;
	tempOffsets-=4;
	tempOffset=tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

arrow_astnode::arrow_astnode(exp_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
	this->lvalue = true;
}

void arrow_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Arrow ";
	node->print(0);
	std::cout<<" ";
	id->print(0);
	std::cout<<") ";
}

void arrow_astnode::gencode(int accessType){
	node->gencode(1);
	int offset = node->tempOffset;
	localSymbolTable lst = gst.symboltables[node->expType.base.type];
	int varOffset = lst.symbols[id->name].v.offset;
	cout<<"sw $t0, "<<node->tempOffset<<"($sp)"<<endl;
	cout<<"addi $t0, $t0, "<<varOffset<<endl;
	if(accessType==1) cout<<"lw $t0, 0($t0)"<<endl;
	tempOffsets-=4;
	tempOffset=tempOffsets;
	cout<<"sw $t0, "<<tempOffset<<"($sp)"<<endl;
}

#define ASTCPP
#endif