#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "symbol_table.cpp"
#include "ast.h"

extern globalSymbolTable gst;

using namespace std;


int main (int argc, char** arg)
{
  Parser parser;
  parser.parse();
  if(gst.symbols.find("main")==gst.symbols.end()){
  	showWarning("Main has not been defined", 0);
  }
  gst.print();
}


