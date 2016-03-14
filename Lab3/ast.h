#include <iostream>
#include <vector>
#include "symbol_table.cpp"
using namespace std;


#ifndef ASTH

class abstract_astnode{
public:
	virtual void print(int)=0;
	// virtual std::string generate_code(const symbolTable&) = 0;
	// virtual basic_types getType();
	// virtual bool checkTypeofAST();
	// protected:
	// virtual void setType(basic_types);
	// private:
	// typeExp astnode_type;
};

class stmt_astnode: public abstract_astnode{
public:
	virtual void print(int);
	vector<variable> declarations=vector<variable>(0);

};

class exp_astnode: public abstract_astnode{
public:
	bool lvalue = false;
	bool canBeIndex = false;
	int expvalue=-1;
	bool typeCasted=false;
	virtual void print(int);
	type expType;
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

// class assign_astnode: public stmt_astnode{
// protected:
// 	ref_astnode* l;
// 	exp_astnode* r;
// public:
// 	assign_astnode(ref_astnode*, exp_astnode*);
// 	void print(int);
// };

class assign_stmt_astnode: public stmt_astnode{
protected:
	exp_astnode* r;
public:
	assign_stmt_astnode(exp_astnode*);
	void print(int);
};

class assign_exp_astnode: public exp_astnode{
protected:
	exp_astnode *l, *r;
public:
	assign_exp_astnode(exp_astnode*, exp_astnode*);
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

class identifier_astnode: public exp_astnode{
protected:
	std::string name;
public:
	identifier_astnode(std::string);
	void print(int);
};

class arrayref_astnode: public exp_astnode{
protected:
	exp_astnode* base;
	exp_astnode* offset;
public:
	arrayref_astnode(exp_astnode*, exp_astnode*);
	void print(int);
};

class pointer_astnode: public exp_astnode{
protected:
	ref_astnode* node;
public:
	pointer_astnode(ref_astnode*);
	void print(int);
};

class deref_astnode: public exp_astnode{
protected:
	ref_astnode* node;
public:
	deref_astnode(ref_astnode*);
	void print(int);
};

class member_astnode: public exp_astnode{
protected:
	exp_astnode* node;
	identifier_astnode* id;
public:
	member_astnode(exp_astnode*, identifier_astnode*);
	void print(int);
};

class arrow_astnode: public exp_astnode{
protected:
	exp_astnode* node;
	identifier_astnode* id;
public:
	arrow_astnode(exp_astnode*, identifier_astnode*);
	void print(int);
};


#define ASTH
#endif