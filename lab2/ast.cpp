#include "ast.h"

void stmt_astnode::print(){

}

void exp_astnode::print(){

}

void ref_astnode::print(){

}

void empty_astnode::print(){
	std::cout<<"(Empty)";
}

void seq_astnode::print(){
	for(unsigned int i = 0; i<nodes.size(); i++)
		nodes[i]->print();
}

void ass_astnode::print(){
	std::cout<<"(Ass ";
	for(unsigned int i=0; i<2; i++){
		nodes[i]->print();
		if(i!=1) std::cout<<" ";
	}
	std::cout<<")";
}

void return_astnode::print(){
	std::cout<<"(Return ";
	node->print();
	std::cout<<")";
}

void if_astnode::print(){
	std::cout<<"(If ";
	node->print();
	std::cout<<" ";
	nodes[0]->print();
	std::cout<<" ";
	nodes[1]->print();
	std::cout<<" )";
}

void while_astnode::print(){
	std::cout<<"(While ";
	node->print();
	std::cout<<" ";
	node2->print();
	std::cout<<" )";
}

void for_astnode::print(){
	std::cout<<"(For ";
	for(int i=0; i<3; i++){
		nodes[i]->print();
		std::cout<<" ";
	}
	node->print();
	std::cout<<" )";
}

void op_astnode2::print(){
	std::cout<<"("<<op<<" ";
	nodes[0]->print();
	nodes[1]->print();
	std::cout<<" )";
}

void op_astnode1::print(){
	std::cout<<"("<<op<<" ";
	nodes->print();
	std::cout<<" )";
}

void funcall_astnode::print(){
	std::cout<<"( "<<funcName<<" ";
	for(int i=0;i<nodes.size();++i){
		nodes[i]->print();	
	}
	std::cout<<" )";
}

void floatconst_astnode::print(){
	std::cout<<"(FloatConst "<<val<<" )";
}

void intconst_astnode::print(){
	std::cout<<"(IntConst "<<val<<" )";
}

void stringconst_astnode::print(){
	std::cout<<"(StringConst "<<val<<" )";
}

void refast_astnode::print(){
	std::cout<<"(RefAst ";
	ref->print();
	std::cout<<" )";
}

void identifier_astnode::print(){
	std::cout<<"\""<<name<<"\"";
}

void arrayref_astnode::print(){
	std::cout<<"( ";
	id->print();
	std::cout<<" ";
	for(unsigned int i=0; i<nodes.size(); i++){
		nodes[i]->print();
		std::cout<<" ";
	}
	std::cout<<" )";
}

void pointer_astnode::print(){
	std::cout<<"(Pointer ";
	node->print();
	std::cout<<" )";
}

void deref_astnode::print(){
	std::cout<<"(Deref ";
	node->print();
	std::cout<<" )";
}
