#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <set>

using namespace std;


class baseType{
public:
	std::string type;
	int pointers;
	
	baseType(string type, int pointers){
		this->type = type;
		this->pointers = pointers;
	}

	baseType(){}

	void print(){
	 	cout<<type<<" ";
	 	for(int i=0; i<pointers; i++)
	 		cout<<"*";
	 	cout<<" ";
	}
};

class type{
public:
	baseType base;
	std::vector<int> sizes;

	type(baseType b, vector<int> s){
		base = b;
		sizes = s;
	}

	type(){}

	void print(){
		base.print();
		for(auto i: sizes) cout<<"["<<i<<"]";
		cout<<" ";
	}
};

class variable{
public:
	type vtype;
	string vname;
	int offset;
	int size;

	variable(type t, string s, int o, int si){
		vtype = t;
		vname = s;
		offset = o;
		size = si;
	}

	variable(){}
	void print(){
		cout<<"("<<vname<<") (";vtype.print();cout<<")";
		if(size>0){
			cout<<" offset: ("<<offset<<") size: ("<<size<<") ";
		}
	}
};

class globalSymbolTableRow{
public:
	bool isFunction;
	variable v;
	std::vector<variable> args;

	void print(){
		cout<<"Function ";
		v.print();
		for(auto v:args){
			cout<<" | ";
			v.print();
		}
	}

};


class localSymbolTableRow{
public:
	variable v;
	void print(){
		v.print();
		cout<<endl;
	}
};

class localSymbolTable{
public:
	map<std::string, localSymbolTableRow> symbols;
	void print(){

		map<int, localSymbolTableRow> temp;
		for(auto v:symbols){
			temp[v.second.v.offset]=v.second;
		}

		for(auto v: temp){
			v.second.print();
		}
	}

	int getTotalLocalSize(){
		int m = 0;
		for(auto lstr: symbols){
			if(lstr.second.v.offset < 0) m+=lstr.second.v.size;
		}
		return m;
	}

	int getTotalArgsSize(){
		int m = 0;
		for(auto lstr: symbols){
			if(lstr.second.v.offset >= 0) m+=lstr.second.v.size;
		}
		return m;
	}
};

class globalSymbolTable{
public:
	map<string, globalSymbolTableRow> symbols;
	set<string> structsDefined;
	map<std::string, localSymbolTable> symboltables; // should be used for structs and function bodies
	
	globalSymbolTable(){
		// globalSymbolTableRow printrow;

		// printrow.isFunction=true;
		// printrow.v=variable(type(baseType("void", 0), vector<int>(0)), "print", 0, 0);
		// printrow.args=vector<variable>(0);

		// symbols["print"]=printrow;

		globalSymbolTableRow printnrow;
		printnrow.isFunction=true;
		printnrow.v=variable(type(baseType("void", 0), vector<int>(0)), "printn", 0, 0);
		printnrow.args=vector<variable>(0);

		symbols["printn"]=printnrow;

		globalSymbolTableRow printfrow;

		printfrow.isFunction=true;
		printfrow.v=variable(type(baseType("void", 0), vector<int>(0)), "printf", 0, 0);
		printfrow.args=vector<variable>(0);

		symbols["printf"]=printfrow;

		// cout<<".data"<<endl;
		// cout<<"space: .asciiz \"\\n\""<<endl;
		// cout<<".text"<<endl;
		

	}

	void print(){

		cout<<"Global symbol table:"<<endl;
		cout<<"--------------------"<<endl;
		cout<<"Format: name returnType arguments"<<endl;
		for(auto s: symbols){
			s.second.print();
			cout<<endl;
		}
		for(auto s: structsDefined){
			cout<<s<<endl;
		}
		cout<<"\n\n\n";
		cout<<"Other symbol tables:"<<endl;
		cout<<"--------------------"<<endl;
		for(auto s:symboltables){
			cout<<s.first<<" symbol table:\n"<<endl;
			s.second.print();
			cout<<"\n\n\n";
		}
	}

	int getTotalLocalSize(string s){
		return symboltables[s].getTotalLocalSize();
	}

	int getTotalArgsSize(string s){
		return symboltables[s].getTotalArgsSize();
	}

	int getReturnTypeSize(string s){
		return -symbols[s].v.size;
	}
};



#endif


