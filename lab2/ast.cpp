#include "ast.h"

#ifndef ASTCPP

void stmt_astnode::print(){
	std::cout<<"This should never be called; stmt_astnode"<<std::endl;
}

void exp_astnode::print(){
	std::cout<<"This should never be called; exp_astnode"<<std::endl;
}

void ref_astnode::print(){
	std::cout<<"This should never be called; ref_astnode"<<std::endl;
}

empty_astnode::empty_astnode(){

}

void empty_astnode::print(){
	std::cout<<"(Empty)";
}

seq_astnode::seq_astnode(std::vector<stmt_astnode*> n){
    nodes = n;     
}

void seq_astnode::print(){
	std::cout<<"(Block [";
	for(unsigned int i = 0; i<nodes.size(); i++)
		nodes[i]->print();
	std::cout<<"] ) ";
}

ass_astnode::ass_astnode(exp_astnode* n1, exp_astnode* n2){
    l = n1;
    r = n2;
}

void ass_astnode::print(){
	std::cout<<"(Ass ";
	l->print();
	std::cout<<" ";
	r->print();
	std::cout<<") ";
}

return_astnode::return_astnode(exp_astnode* n){
    node = n;
}

void return_astnode::print(){
	std::cout<<"(Return ";
	node->print();
	std::cout<<") ";
}

if_astnode::if_astnode(exp_astnode* n1, stmt_astnode** n2){
    node = n1;
    nodes[0] = n2[0];
    nodes[1] = n2[1];
}

void if_astnode::print(){
	std::cout<<"(If ";
	node->print();
	std::cout<<" ";
	nodes[0]->print();
	std::cout<<" ";
	nodes[1]->print();
	std::cout<<" ) ";
}

while_astnode::while_astnode(exp_astnode* n1, stmt_astnode* n2){
    node = n1;
    node2 = n2;
}

void while_astnode::print(){
	std::cout<<"(While ";
	node->print();
	std::cout<<" ";
	node2->print();
	std::cout<<" ) ";
}

for_astnode::for_astnode(exp_astnode** n1, stmt_astnode* n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	nodes[2]=n1[2];
	node=n2;
}

void for_astnode::print(){
	std::cout<<"(For ";
	for(int i=0; i<3; i++){
		nodes[i]->print();
		std::cout<<" ";
	}
	node->print();
	std::cout<<" ) ";
}

op_astnode2::op_astnode2(exp_astnode** n1, std::string n2){
	nodes[0]=n1[0];
	nodes[1]=n1[1];
	op=n2;
}

void op_astnode2::print(){
	std::cout<<"("<<op<<" ";
	nodes[0]->print();
	nodes[1]->print();
	std::cout<<" ) ";
}

op_astnode1::op_astnode1(exp_astnode* n1, std::string n2){
	node=n1;
	op=n2;
}

void op_astnode1::print(){
	std::cout<<"("<<op<<" ";
	node->print();
	std::cout<<" ) ";
}

funcall_astnode::funcall_astnode(std::string n1, std::vector<exp_astnode*> n2){
	funcName=n1;
	nodes=n2;
}

void funcall_astnode::print(){
	std::cout<<"( "<<funcName<<" ";
	for(int i=0;i<nodes.size();++i){
		nodes[i]->print();	
	}
	std::cout<<" ) ";
}

floatconst_astnode::floatconst_astnode(float n){
	val=n;
}

void floatconst_astnode::print(){
	std::cout<<"(FloatConst "<<val<<" ) ";
}

intconst_astnode::intconst_astnode(int n){
	val=n;
}

void intconst_astnode::print(){
	std::cout<<"(IntConst "<<val<<" ) ";
}

stringconst_astnode::stringconst_astnode(std::string n){
	val=n;
}

void stringconst_astnode::print(){
	std::cout<<"(StringConst "<<val<<" ) ";
}

refast_astnode::refast_astnode(ref_astnode* n){
	ref=n;
}

void refast_astnode::print(){
	std::cout<<"(RefAst ";
	ref->print();
	std::cout<<" ) ";
}

identifier_astnode::identifier_astnode(std::string n){
	name=n;
}

void identifier_astnode::print(){
	std::cout<<" \""<<name<<"\" ";
}

arrayref_astnode::arrayref_astnode(identifier_astnode* n1, std::vector<exp_astnode*> n2){
	id=n1;
	nodes=n2;
}

void arrayref_astnode::print(){
	std::cout<<"( ";
	id->print();
	std::cout<<" ";
	for(unsigned int i=0; i<nodes.size(); i++){
		nodes[i]->print();
		std::cout<<" ";
	}
	std::cout<<" ) ";
}

pointer_astnode::pointer_astnode(ref_astnode* n){
	node=n;
}

void pointer_astnode::print(){
	std::cout<<"(Pointer ";
	node->print();
	std::cout<<" ) ";
}

deref_astnode::deref_astnode(ref_astnode* n){
	node=n;
}

void deref_astnode::print(){
	std::cout<<"(DEREF ";
	node->print();
	std::cout<<" ) ";
}

dotref_astnode::dotref_astnode(ref_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
}

void dotref_astnode::print(){
	std::cout<<"(DOT ";
	node->print();
	std::cout<<" ) ";
}

ptrop_astnode::ptrop_astnode(ref_astnode* n, identifier_astnode* i){
	node=n;
	id=i;
}

void ptrop_astnode::print(){
	std::cout<<"(-> ";
	node->print();
	std::cout<<" ) ";
}



#define ASTCPP
#endif