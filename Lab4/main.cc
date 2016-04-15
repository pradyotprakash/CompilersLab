#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "symbol_table.cpp"

extern globalSymbolTable gst;

using namespace std;


int main (int argc, char** arg)
{
  Parser parser;
  parser.parse();
  cout<<"--------------------"<<endl;
  gst.print();
}


