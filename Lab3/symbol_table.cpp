#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

struct baseType{
	std::string type;
	int pointers;
};

struct type{
	struct baseType base;
	std::vector<int> sizes;
};

class symbol_table_row{
public:
	struct type symbol_type;
	std::string symbol_name;
	int size;
	int offset;

	symbol_table_row(struct type symbol_type, std::string symbol_name, int size, int offset){
		this->symbol_type = symbol_type;
		this->symbol_name = symbol_name;
		this->size = size;
		this->offset = offset;
	}
};

class symbol_table{
public:
	std::map<std::string, symbol_table_row> rows;
	// std::map<std::string, symbol_table*> structTables;

	symbol_table(std::map<std::string, symbol_table_row> rows){//, std::map<std::string, symbol_table*> structTables){
		this->rows = rows;
		// this->structTables = structTables;
	}

	symbol_table(){}
};
#endif
