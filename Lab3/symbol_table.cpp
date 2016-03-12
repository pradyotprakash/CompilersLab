#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

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
	 	cout<<"Type: "<<type<<" pointers: "<<pointers<<" ";
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
		cout<<"Base: ";base.print();cout<<" Arrays: ";
		for(auto i: sizes) cout<<i<<" ";
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
		cout<<vname<<" ";vtype.print();cout<<" offset: "<<offset<<" size: "<<size<<" ";
	}
};

class globalSymbolTableRow{
public:
	bool isFunction;
	variable v;
	std::vector<variable> args;

	void print(){
		cout<<isFunction<<" ";v.print();
		for(auto v:args) v.print();
	}

};


class localSymbolTableRow{
public:
	variable v;
	void print(){
		v.print();
	}
};

class localSymbolTable{
public:
	map<std::string, localSymbolTableRow> symbols;

	void print(){
		for(auto v: symbols){
			v.second.print();
		}
	}
};

class globalSymbolTable{
public:
	map<std::string, globalSymbolTableRow> symbols;
	map<std::string, localSymbolTable> symboltables; // should be used for structs and function bodies
	void print(){
		cout<<"Global symbol table:"<<endl;
		for(auto s: symbols){
			s.second.print();
			cout<<endl;
		}
		cout<<"Second level symbol tables:"<<endl;
		for(auto s:symboltables){
			cout<<s.first<<" symbol table now"<<endl;
			s.second.print();
			cout<<endl;
		}
	}
};





#endif


