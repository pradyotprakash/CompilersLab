#include "ast.h"

#ifndef ASTCPP

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

assign_astnode::assign_astnode(ref_astnode* n1, exp_astnode* n2){
    l = n1;
    r = n2;
}

void assign_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"(Ass ";
	this->l->print(0);
	std::cout<<" ";
	r->print(0);
	std::cout<<")\n";
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

arrayref_astnode::arrayref_astnode(ref_astnode* b, exp_astnode* o){
	base = b;
	offset = o;
}

void arrayref_astnode::print(int l){
	for(int i=0;i<l;++i)
		cout<<' ';
	std::cout<<"( ";
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

member_astnode::member_astnode(ref_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
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

arrow_astnode::arrow_astnode(ref_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
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