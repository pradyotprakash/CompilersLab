%%

"\n"			lineno++;
[ \t] 			// skip

void 			return Parser::VOID;	//
int				return Parser::INT;		//
float 			return Parser::FLOAT;	//

return			return Parser::RETURN;	//
"<="			return Parser::LE_OP;	// 
">="			return Parser::GE_OP;	//
"=="			return Parser::EQ_OP;	//
"!="			return Parser::NE_OP;	//
"||"			return Parser::OR_OP;
"&&"			return Parser::AND_OP;
"++"			return Parser::INC_OP;	//
if 				return Parser::IF;
else			return Parser::ELSE;
while			return Parser::WHILE;
for				return Parser::FOR;
struct 			return Parser::STRUCT;	//
"->"			return Parser::PTR_OP;	//

"//".*"\n"	    lineno++;

"/*"[^*]*(\*([^/*][^*]*)?)*"*/" // skip return Parser::COMMENT;

([0-9]+)|(0[bB][01]*)|(0[0-7]*)|(0[xX][0-9a-fA-F]*) {Parser::d_val__ = stoi(std::string(matched())); return Parser::INT_CONSTANT;}

([0-9]+\.([0-9]*([eE]([+\-]?)[0-9]+)?))|([0-9]*\.([0-9]+([eE]([+\-]?)[0-9]+)?)) {Parser::d_val__ = stof(std::string(matched())); return Parser::FLOAT_CONSTANT;}

\"[[:alpha:][:digit:]( )(\t)(\n)(\\)(\"):]*\" {Parser::d_val__ = std::string(matched()); return Parser::STRING_LITERAL;}

[[:alpha:]_][[:alpha:][:digit:]_]*	{Parser::d_val__ = std::string(matched()); return Parser::IDENTIFIER;}
.				{Parser::d_val__ = std::string(matched()); return matched()[0];}
