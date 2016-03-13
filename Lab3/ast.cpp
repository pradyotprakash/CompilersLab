#include "ast.h"
#ifndef ASTCPP



globalSymbolTable gst;
string curFuncName;
localSymbolTable curLocal;

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

void binaryTypeCheck(exp_astnode *e1, exp_astnode *e2){
	type t1 = e1->expType;
	type t2 = e2->expType;

	string s1 = t1.base.type;
	string s2 = t2.base.type;

	if(isBasic(t1) && isBasic(t2)){
		
		if(s1 == "string" && s2 != "string" ||
			s2 == "string" && s1 != "string")
			cerr<<"Incompatible types\n";
		else if(s1 == "float" && s2 == "int"){
			e2->expType.base.type = "float";
			e2->typeCasted = true;
		}
		else if(s1 == "int" && s2 == "float"){
			e1->expType.base.type = "float";
			e1->typeCasted = true;
		}
		return;
	}

	else{
		// if((t1.base.type=="void" || s1 == s2) && 
		// 	t1.base.pointers==1+ && t1.sizes.size()==0
		// 	t2.base.pointers==1 && t2.base.type!="void" && ){
		// 		e2->typeCasted=true;
		// 		e2->expType=e1->expType;
		// 	}
		// }
		// int x = t1.base.pointers + t1.sizes.size();
		// int y = t2.base.pointers + t2.sizes.size();
		// if((s1 == "void" || s1 == s2) &&  x == y && )
	}

}


void unaryTypeCheck(type t1, exp_astnode* e){
	type t2 = e->expType;

	if(isBasic(t1) && isBasic(t2)){
		if(t1.base.type == "string" && t2.base.type != "string" ||
			t2.base.type == "string" && t1.base.type != "string"){
			cerr<<"Return type mismatch\n";
		}
		else{
			e->expType = t1;	
		}
		return;
	}
}

void stmt_astnode::print(int l){
	std::cout<<"This should never be called; stmt_astnode"<<std::endl;
}

void exp_astnode::print(int l){
	std::cout<<"This should never be called; exp_astnode"<<std::endl;
}

void ref_astnode::print(int l){
	std::cout<<"This should never be called; ref_astnode"<<std::endl;
}

empty_astnode::empty_astnode(){

}

void empty_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Empty)";
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

// assign_astnode::assign_astnode(ref_astnode* n1, exp_astnode* n2){
//     l = n1;
//     r = n2;
// }

// void assign_astnode::print(int l){
// 	for(int i=0;i<l;++i)
// 		cout<<' ';
// 	std::cout<<"(Ass ";
// 	this->l->print(0);
// 	std::cout<<" ";
// 	r->print(0);
// 	std::cout<<")\n";
// }

assign_stmt_astnode::assign_stmt_astnode(exp_astnode* n2){
    // l = n1;
    r = n2;
}

void assign_stmt_astnode::print(int l){
	// for(int i=0;i<l;++i)
	// 	cout<<' ';
	// std::cout<<"(Ass ";
	// this->l->print(0);
	// std::cout<<" ";
	// r->print(0);
	// std::cout<<")\n";
}

assign_exp_astnode::assign_exp_astnode(exp_astnode* n1, exp_astnode* n2){
    l = n1;
    r = n2;
}

void assign_exp_astnode::print(int l){
	// for(int i=0;i<l;++i)
	// 	cout<<' ';
	// std::cout<<"(Ass ";
	// this->l->print(0);
	// std::cout<<" ";
	// r->print(0);
	// std::cout<<")\n";
}

return_astnode::return_astnode(exp_astnode* n){
    node = n;
}

void return_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Return ";
	node->print(0);
	std::cout<<") ";
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

op_astnode2::op_astnode2(exp_astnode** n1, std::string n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	op=n2;
}

void op_astnode2::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"("<<op<<" ";
	nodes[0]->print(0);
	nodes[1]->print(0);
	std::cout<<") ";
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

funcall_astnode::funcall_astnode(std::string n1, std::vector<exp_astnode*> n2){
	funcName=n1;
	nodes=n2;
}

void funcall_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( "<<funcName<<" ";
	for(int i=0;i<nodes.size();++i){
		nodes[i]->print(0);	
	}
	std::cout<<") ";
}

floatconst_astnode::floatconst_astnode(float n){
	val=n;
}

void floatconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(FloatConst "<<val<<") ";
}

intconst_astnode::intconst_astnode(int n){
	val=n;
}

void intconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(IntConst "<<val<<") ";
}

stringconst_astnode::stringconst_astnode(std::string n){
	val=n;
}

void stringconst_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(StringConst "<<val<<") ";
}

refast_astnode::refast_astnode(ref_astnode* n){
	ref=n;
}

void refast_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(RefAst ";
	ref->print(0);
	std::cout<<") ";
}

identifier_astnode::identifier_astnode(std::string n){
	name=n;
}

void identifier_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Id \""<<name<<"\") ";
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

#define ASTCPP
#endif