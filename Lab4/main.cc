#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "symbol_table.cpp"
#include "ast.h"
#include <map>
#include <string>
extern globalSymbolTable gst;
extern map<int, string> globalStrings;
extern vector<exp_astnode*> printargs;
using namespace std;


int main (int argc, char** arg)
{
	cout<<".text"<<endl;
	Parser parser;
	parser.parse();
	if(gst.symbols.find("main")==gst.symbols.end()){
		showWarning("Main has not been defined", 0);
	}
	cout<<".data"<<endl;
	for(auto v: globalStrings){
		cout<<"S_"<<v.first<<": .asciiz "<<v.second<<endl;
	}
	cout<<"newl: .asciiz \"\\n\""<<endl;
	cout<<"space: .asciiz \" \""<<endl;
	// gst.print();
}


