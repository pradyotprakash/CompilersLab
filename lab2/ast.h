#include <iostream>
#include <vector>
using namespace std;
#ifndef ASTH

class abstract_astnode{
public:
	virtual void print()=0;
};

class stmt_astnode: public abstract_astnode{
public:
	virtual void print();
};

class exp_astnode: public abstract_astnode{
public:
	virtual void print();
};

class ref_astnode: public abstract_astnode{
public:
	virtual void print();
};

class empty_astnode: public stmt_astnode{
public:
	empty_astnode();
	void print();
};

class seq_astnode: public stmt_astnode{
protected:
	std::vector<stmt_astnode*> nodes;
public:
	seq_astnode(std::vector<stmt_astnode*>);
	void print();
};

class ass_astnode: public stmt_astnode{
protected:
	exp_astnode* l;
	exp_astnode* r;
public:
	ass_astnode(exp_astnode*, exp_astnode*);
	void print();
};

class return_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
public:
	return_astnode(exp_astnode*);
	void print();
};

class if_astnode: public stmt_astnode{
protected:
	exp_astnode *node;
	stmt_astnode *nodes[2];
public:
	if_astnode(exp_astnode*, stmt_astnode**);
	void print();
};

class while_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
	stmt_astnode *node2;
public:
	while_astnode(exp_astnode*, stmt_astnode*);
	void print();
};

class for_astnode: public stmt_astnode{
protected:
	exp_astnode* nodes[3];
	stmt_astnode* node;
public:
	for_astnode(exp_astnode**, stmt_astnode*);
	void print();
};

class op_astnode2: public exp_astnode{
protected:	
	exp_astnode* nodes[2];
	std::string op;
public:
	op_astnode2(exp_astnode**, std::string);
	void print();
};

class op_astnode1: public exp_astnode{
protected:
	exp_astnode* node;
	std::string op;
public:
	op_astnode1(exp_astnode*, std::string);
	void print();
};

class funcall_astnode: public exp_astnode{
	std::string funcName;
	std::vector<exp_astnode*> nodes;
public:
	funcall_astnode(std::string, std::vector<exp_astnode*>);
	void print();
};

class floatconst_astnode: public exp_astnode{
protected:
	float val;
public:
	floatconst_astnode(float);
	void print();
};

class intconst_astnode: public exp_astnode{
protected:
	int val;
public:
	intconst_astnode(int);
	void print();
};

class stringconst_astnode: public exp_astnode{
protected:
	std::string val;
public:
	stringconst_astnode(std::string);
	void print();
};

class refast_astnode: public exp_astnode{
protected:
	ref_astnode* ref;
public:
	refast_astnode(ref_astnode*);
	void print();
};

class identifier_astnode: public ref_astnode{
protected:
	std::string name;
public:
	identifier_astnode(std::string);
	void print();
};

class arrayref_astnode: public ref_astnode{
protected:
	identifier_astnode* id;
	std::vector<exp_astnode*> nodes;
public:
	arrayref_astnode(identifier_astnode*, std::vector<exp_astnode*>);
	void print();
};

class pointer_astnode: public ref_astnode{
protected:
	ref_astnode* node;
public:
	pointer_astnode(ref_astnode*);
	void print();
};

class deref_astnode: public ref_astnode{
protected:
	ref_astnode* node;
public:
	deref_astnode(ref_astnode*);
	void print();
};

#define ASTH
#endif