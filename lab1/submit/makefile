all: clean lex.cc parse.cc main.cc Scanner.h Scannerbase.h Scanner.ih Parser.h Parserbase.h Parser.ih
	g++   --std=c++0x lex.cc parse.cc main.cc -o parser;
	echo "digraph G {ordering=out;\n\n""`./parser < test-cc`""}" > graph.dot
	dot -Tpdf graph.dot -o graph.pdf

lex.cc: lex.l Scanner.ih 
	flexc++ lex.l;
	sed -i '/int lex()/r enums' Scanner.h 
	sed -i '/include/a #include "Parserbase.h"' Scanner.ih; 

parse.cc: parse.y Parser.ih Parser.h Parserbase.h
	# bisonc++  parse.y; 
	bisonc++ --construction -V parse.y; 
#	sed -i '/ifndef/a #include "tree_util.hh"' Parserbase.h;
#	sed -i '/ifndef/a #include "tree.hh"' Parserbase.h;
#	./sedscript
     

Parser.ih: parse.y
	if [ ! -e Parser.ih ]; then \
		bisonc++ --construction -V parse.y && sed -i '/#include/a int nodeCount = 0;' Parser.ih; \
	fi
Parser.h: parse.y
Parserbase.h: parse.y
Scanner.ih: lex.l
Scanner.h: lex.l
Scannerbase.h: lex.l

clean:
	rm -f Parserbase.h Parser.h Parser.ih parse.cc junk Scanner* lex.cc parser parse.y.output graph.dot graph.pdf
