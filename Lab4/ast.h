#include <iostream>
#include <vector>
#include "symbol_table.cpp"
using namespace std;


#ifndef ASTH

class abstract_astnode{
public:
	virtual void print(int)=0;
	string code;
	int tempOffset;

	virtual std::string gencode() = 0;
	
};

class stmt_astnode: public abstract_astnode{
public:
	virtual void print(int);
	vector<variable> declarations=vector<variable>(0);
	virtual string gencode();
};

class exp_astnode: public abstract_astnode{
public:
	bool lvalue = false;
	bool canBeIndex = false;
	int expvalue=-1, offset = 0;
	bool typeCasted=false;
	bool isLocal=false, isAddress=false;
	virtual void print(int);
	virtual string gencode();
	int tempLocal;
	type expType;
};

class ref_astnode: public exp_astnode{
public:
	virtual void print(int);
	virtual string gencode();
};

class empty_astnode: public stmt_astnode{
public:
	empty_astnode();
	void print(int);
	string gencode();
};

class seq_astnode: public stmt_astnode{
protected:
	std::vector<stmt_astnode*> nodes;
public:
	seq_astnode(std::vector<stmt_astnode*>);
	void print(int);
	string gencode();
};

class assign_stmt_astnode: public stmt_astnode{
protected:
	exp_astnode* r;
public:
	assign_stmt_astnode(exp_astnode*);
	void print(int);
	string gencode();
};

class assign_exp_astnode: public exp_astnode{
protected:
	exp_astnode *l, *r;
public:
	assign_exp_astnode(exp_astnode*, exp_astnode*);
	void print(int);
	string gencode();
};

class return_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
public:
	return_astnode(exp_astnode*);
	void print(int);
	string gencode();
};

class if_astnode: public stmt_astnode{
protected:
	exp_astnode *node;
	stmt_astnode *nodes[2];
public:
	if_astnode(exp_astnode*, stmt_astnode**);
	void print(int);
	string gencode();
};

class while_astnode: public stmt_astnode{
protected:	
	exp_astnode *node;
	stmt_astnode *node2;
public:
	while_astnode(exp_astnode*, stmt_astnode*);
	void print(int);
	string gencode();
};

class for_astnode: public stmt_astnode{
protected:
	exp_astnode* nodes[3];
	stmt_astnode* node;
public:
	for_astnode(exp_astnode**, stmt_astnode*);
	void print(int);
	string gencode();
};

class op_astnode2: public exp_astnode{
protected:	
	exp_astnode* nodes[2];
	std::string op;
public:
	op_astnode2(exp_astnode**, std::string);
	void print(int);
	string gencode();
};

class op_astnode1: public exp_astnode{
protected:
	exp_astnode* node;
	std::string op;
public:
	op_astnode1(exp_astnode*, std::string);
	void print(int);
	string gencode();
};

class funcall_astnode: public exp_astnode{
	std::string funcName;
	std::vector<exp_astnode*> nodes;
public:
	funcall_astnode(std::string, std::vector<exp_astnode*>);
	void print(int);
	string gencode();
};

class floatconst_astnode: public exp_astnode{
protected:
	float val;
public:
	floatconst_astnode(float);
	void print(int);
	string gencode();
};

class intconst_astnode: public exp_astnode{
protected:
	int val;
public:
	intconst_astnode(int);
	void print(int);
	string gencode();
};

class stringconst_astnode: public exp_astnode{
protected:
	std::string val;
public:
	stringconst_astnode(std::string);
	void print(int);
	string gencode();
};

class refast_astnode: public exp_astnode{
protected:
	ref_astnode* ref;
public:
	refast_astnode(ref_astnode*);
	void print(int);
	string gencode();
};

class identifier_astnode: public exp_astnode{
protected:
	std::string name;
public:
	identifier_astnode(std::string);
	void print(int);
	string gencode();
};

class arrayref_astnode: public exp_astnode{
protected:
	exp_astnode* base;
	exp_astnode* offset;
public:
	arrayref_astnode(exp_astnode*, exp_astnode*);
	void print(int);
	string gencode();
};

class pointer_astnode: public exp_astnode{
protected:
	ref_astnode* node;
public:
	pointer_astnode(ref_astnode*);
	void print(int);
	string gencode();
};

class deref_astnode: public exp_astnode{
protected:
	ref_astnode* node;
public:
	deref_astnode(ref_astnode*);
	void print(int);
	string gencode();
};

class member_astnode: public exp_astnode{
protected:
	exp_astnode* node;
	identifier_astnode* id;
public:
	member_astnode(exp_astnode*, identifier_astnode*);
	void print(int);
	string gencode();
};

class arrow_astnode: public exp_astnode{
protected:
	exp_astnode* node;
	identifier_astnode* id;
public:
	arrow_astnode(exp_astnode*, identifier_astnode*);
	void print(int);
	string gencode();
};


#define ASTH
#endif