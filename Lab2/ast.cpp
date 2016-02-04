#include <iostream>
#include <vector>

class abstract_astnode{
public:
	virtual void print() = 0;
	/*
	virtual std::string generate_code(const symbolTable&) = 0;
	virtual basic_types getType() = 0;
	virtual bool checkTypeOfAST() = 0;

protected:
	virtual void setType(basic_types) = 0;

private:
	typeExp astnode_type;
	*/
};

class stmt_astnode: public abstract_astnode{
public:
	void print(){};
};

class exp_astnode: public abstract_astnode{
public:
	void print(){};
};

class ref_astnode: public abstract_astnode{
public:
	void print(){};
};

class empty_astnode: public stmt_astnode{
public:
	void print(){
		std::cout<<"(Empty)";
	}
};

class seq_astnode: public stmt_astnode{
public:
	std::vector<stmt_astnode*> nodes;
	void print(){
		for(unsigned int i = 0; i<nodes.size(); i++)
			nodes[i]->print();
	}
};

class ass_astnode: public stmt_astnode{
public:
	exp_astnode* nodes[2];
	void print(){
		std::cout<<"(Ass ";
		for(unsigned int i=0; i<2; i++){
			nodes[i]->print();
			if(i!=1) std::cout<<" ";
		}
		std::cout<<")";
	}
};

class return_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	void print(){
		std::cout<<"(Return ";
		node->print();
		std::cout<<")";
	}
};

class if_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	stmt_astnode *nodes[2];
	void print(){
		std::cout<<"(If ";
		node->print();
		std::cout<<" ";
		nodes[0]->print();
		std::cout<<" ";
		nodes[1]->print();
		std::cout<<" )";
	}
};

class while_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	stmt_astnode *node2;
	void print(){
		std::cout<<"(While ";
		node->print();
		std::cout<<" ";
		node2->print();
		std::cout<<" )";
	}
};

class for_astnode: public stmt_astnode{
public:
	exp_astnode* nodes[3];
	stmt_astnode* node;
	void print(){
		std::cout<<"(For ";
		for(int i=0; i<3; i++){
			nodes[i]->print();
			std::cout<<" ";
		}
		node->print();
		std::cout<<" )";
	}
};

class op_astnode2: public exp_astnode{
public:
	exp_astnode* nodes[2];
	std::string op;
	void print(){
		std::cout<<"("<<op<<" ";
		nodes[0]->print();
		nodes[1]->print();
		std::cout<<" )";
	}
};

class op_astnode1: public exp_astnode{
public:
	exp_astnode* nodes;
	std::string op;
	void print(){
		std::cout<<"("<<op<<" ";
		nodes->print();
		std::cout<<" )";
	}
};

class funcall_astnode: public exp_astnode{
public:
	std::string funcName;
	std::vector<exp_astnode*> nodes;
	void print(){
		std::cout<<"( "<<funcName<<" ";
		for(int i=0;i<nodes.size();++i){
			nodes[i]->print();	
		}
		std::cout<<" )";
	}
};

class floatconst_astnode: public exp_astnode{
public:
	std::string val;
	void print(){
		std::cout<<"(FloatConst "<<val<<" )";
	}
};

class intconst_astnode: public exp_astnode{
public:
	std::string val;
	void print(){
		std::cout<<"(IntConst "<<val<<" )";
	}
};

class stringconst_astnode: public exp_astnode{
public:
	std::string val;
	void print(){
		std::cout<<"(StringConst "<<val<<" )";
	}
};

class refast_astnode: public exp_astnode{
public:
	ref_astnode* ref;
	void print(){
		std::cout<<"(RefAst ";
		ref->print();
		std::cout<<" )";
	}
};

class identifier_astnode: public ref_astnode{
public:
	std::string name;
	void print(){
		std::cout<<"\""<<name<<"\"";
	}
};

class arrayref_astnode: public ref_astnode{
public:
	identifier_astnode* id;
	std::vector<exp_astnode*> nodes;
	void print(){
		std::cout<<"( ";
		id->print();
		std::cout<<" ";
		for(unsigned int i=0; i<nodes.size(); i++){
			nodes[i]->print();
			std::cout<<" ";
		}
		std::cout<<" )";
	}
};

class pointer_astnode: public ref_astnode{
public:
	ref_astnode* node;
	void print(){
		std::cout<<"(Pointer ";
		node->print();
		std::cout<<" )";
	}
};

class deref_astnode: public ref_astnode{
public:
	ref_astnode* node;
	void print(){
		std::cout<<"(Deref ";
		node->print();
		std::cout<<" )";
	}
};

