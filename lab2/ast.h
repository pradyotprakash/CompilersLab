#include <iostream>
#include <vector>

class abstract_astnode{
public:
	virtual void print() = 0;
};

class stmt_astnode: public abstract_astnode{
public:
	void print();
};

class exp_astnode: public abstract_astnode{
public:
	void print();
};

class ref_astnode: public abstract_astnode{
public:
	void print();
};

class empty_astnode: public stmt_astnode{
public:
	void print();
};

class seq_astnode: public stmt_astnode{
public:
	std::vector<stmt_astnode*> nodes;
	void print();
};

class ass_astnode: public stmt_astnode{
public:
	exp_astnode* nodes[2];
	void print();
};

class return_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	void print();
};

class if_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	stmt_astnode *nodes[2];
	void print();
};

class while_astnode: public stmt_astnode{
public:
	exp_astnode *node;
	stmt_astnode *node2;
	void print();
};

class for_astnode: public stmt_astnode{
public:
	exp_astnode* nodes[3];
	stmt_astnode* node;
	void print();
};

class op_astnode2: public exp_astnode{
public:
	exp_astnode* nodes[2];
	std::string op;
	void print();
};

class op_astnode1: public exp_astnode{
public:
	exp_astnode* nodes;
	std::string op;
	void print();
};

class funcall_astnode: public exp_astnode{
public:
	std::string funcName;
	std::vector<exp_astnode*> nodes;
	void print();
};

class floatconst_astnode: public exp_astnode{
public:
	std::string val;
	void print();
};

class intconst_astnode: public exp_astnode{
public:
	std::string val;
	void print();
};

class stringconst_astnode: public exp_astnode{
public:
	std::string val;
	void print();
};

class refast_astnode: public exp_astnode{
public:
	ref_astnode* ref;
	void print();
};

class identifier_astnode: public ref_astnode{
public:
	std::string name;
	void print();
};

class arrayref_astnode: public ref_astnode{
public:
	identifier_astnode* id;
	std::vector<exp_astnode*> nodes;
	void print();
};

class pointer_astnode: public ref_astnode{
public:
	ref_astnode* node;
	void print();
};

class deref_astnode: public ref_astnode{
public:
	ref_astnode* node;
	void print();
};

