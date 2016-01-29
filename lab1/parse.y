%scanner Scanner.h
%scanner-token-function d_scanner.lex()

%token VOID INT FLOAT RETURN LE_OP GE_OP EQ_OP NE_OP OR_OP AND_OP INC_OP IF ELSE WHILE FOR INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL IDENTIFIER



%%

translation_unit:  
    function_definition { $$ = ++nodeCount;
            	    std::cout<<$$<<"[label=\"translation_unit\"]"<<std::endl;
            	    std::cout<<$$<<" -> "<<$1<<std::endl;
            }
  | translation_unit function_definition { $$ = ++nodeCount;
            	    std::cout<<$$<<"[label=\"translation_unit\"]"<<std::endl;
            	    std::cout<<$$<<" -> "<<$1<<std::endl;
        	    std::cout<<$$<<" -> "<<$2<<std::endl;
            }
  ;

function_definition:  
          type_specifier fun_declarator compound_statement 
          { $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"function_definition\"]"<<std::endl;
            	    std::cout<<$$<<" -> "<<$1<<std::endl;
        	    std::cout<<$$<<" -> "<<$2<<std::endl;
        	    std::cout<<$$<<" -> "<<$3<<std::endl;
            }
; 

type_specifier: 
            VOID  { 
            	    std::cout<<nodeCount+2<<"[label=\"type_specifier\"]"<<std::endl;
            	    std::cout<<nodeCount+1<<"[label=\"VOID\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

            }
        | INT   { 
                  std::cout<<nodeCount+2<<"[label=\"type_specifier\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"INT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;
            }
  | FLOAT { 
                  std::cout<<nodeCount+2<<"[label=\"type_specifier\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"FLOAT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;
            }
 ;       

fun_declarator: 
          IDENTIFIER '(' parameter_list ')'  
          	{   
            	    std::cout<<nodeCount+4<<"[label=\"fun_declarator\"]"<<std::endl;
                  std::cout<<nodeCount+3<<"[label=\"IDENTIFIER\"]"<<std::endl;
            	    std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
            	    std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
            	    std::cout<<nodeCount+4<<" -> "<<nodeCount+3<<std::endl;
            	    std::cout<<nodeCount+4<<" -> "<<nodeCount+2<<std::endl;
            	    std::cout<<nodeCount+4<<" -> "<<$3<<std::endl;
            	    std::cout<<nodeCount+4<<" -> "<<nodeCount+1<<std::endl;
            	    nodeCount += 4;
                  $$ = nodeCount;
            }
        | IDENTIFIER '(' ')' {
            	    std::cout<<nodeCount+4<<"[label=\"fun_declarator\"]"<<std::endl;
                  std::cout<<nodeCount+3<<"[label=\"IDENTIFIER\"]"<<std::endl;
                  std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+3<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+2<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 4;
                  $$ = nodeCount;
            }
  ;

parameter_list: 
    parameter_declaration 
            { $$ = ++nodeCount;
            	    std::cout<<$$<<"[label=\"parameter_list\"]"<<std::endl;
            	    std::cout<<$$<<" -> "<<$1<<std::endl;
            }
    
  | parameter_list ',' parameter_declaration 
      	{ 
            	    std::cout<<nodeCount+2<<"[label=\"parameter_list\"]"<<std::endl;
		    std::cout<<nodeCount+1<<"[label=\",\"]"<<std::endl;
		    std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
		    std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
		    std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;		   		    
		    nodeCount += 2;
                  $$ = nodeCount;
            }
  ;

parameter_declaration: 
          type_specifier declarator 
          {
          	$$ = ++nodeCount;
	             std::cout<<$$<<"[label=\"parameter_declaration\"]"<<std::endl;
                std::cout<<$$<<" -> "<<$1<<std::endl;
                std::cout<<$$<<" -> "<<$2<<std::endl;
          }
   ;     

declarator: 
          IDENTIFIER {
          	
	        std::cout<<nodeCount+2<<"[label=\"declarator\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"IDENTIFIER\"]"<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 2;
                  $$ = nodeCount;
          }
  | declarator '[' constant_expression ']' 
  {
          std::cout<<nodeCount+3<<"[label=\"declarator\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"[\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"]\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$1<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$3<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 3;
                  $$ = nodeCount;
          }
    ;    


constant_expression: 
          INT_CONSTANT {
            std::cout<<nodeCount+2<<"[label=\"constant_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"INT_CONSTANT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;
          }
        | FLOAT_CONSTANT {
            std::cout<<nodeCount+2<<"[label=\"constant_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"FLOAT_CONSTANT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;
          }
      ;
compound_statement: 
          '{' '}' {
           std::cout<<nodeCount+3<<"[label=\"compound_statement\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"{\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"}\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 3;
                  $$ = nodeCount;
          }
  | '{' statement_list '}' 
  {
    std::cout<<nodeCount+3<<"[label=\"compound_statement\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"{\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"}\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 3;
                  $$ = nodeCount;
  }
        | '{' declaration_list statement_list '}' {
          std::cout<<nodeCount+3<<"[label=\"compound_statement\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"{\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"}\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$3<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 3;
                  $$ = nodeCount;
        }
  ;

statement_list: 
          statement {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"statement_list\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | statement_list statement  {

            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"statement_list\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;
            std::cout<<$$<<" -> "<<$2<<std::endl;
        }
   ;

statement: 
          '{' statement_list '}'  //a solution to the local decl problem
          {
            std::cout<<nodeCount+3<<"[label=\"statement\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"{\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"}\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;

          nodeCount += 3;
                  $$ = nodeCount;
          }
        | selection_statement   
        {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"statement\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | iteration_statement   
        {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"statement\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
  | assignment_statement  
        {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"statement\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | RETURN expression ';' 
        {

           std::cout<<nodeCount+3<<"[label=\"statement\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"RETURN\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\";\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 3;
                  $$ = nodeCount;
        }
    ;    

assignment_statement: 
          ';' 
          {
            
            std::cout<<nodeCount+2<<"[label=\"assignment_statement\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\";\"]"<<std::endl;
            
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
          }
  |  l_expression '=' expression ';' 
  { 
            std::cout<<nodeCount+3<<"[label=\"assignment_statement\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"=\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\";\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$1<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$3<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 3;
                  $$ = nodeCount;
  }
;

expression: 
          logical_and_expression {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | expression OR_OP logical_and_expression
        {
          std::cout<<nodeCount+2<<"[label=\"expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"OR_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            
            nodeCount += 2;
                  $$ = nodeCount;
        }
;

logical_and_expression: 
          equality_expression
          {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"logical_and_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | logical_and_expression AND_OP equality_expression 
        {
          std::cout<<nodeCount+2<<"[label=\"logical_and_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"AND_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
;

equality_expression: 
          relational_expression 
          {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"equality_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | equality_expression EQ_OP relational_expression   
        {
          std::cout<<nodeCount+2<<"[label=\"equality_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"EQ_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
  | equality_expression NE_OP relational_expression 
        {
            std::cout<<nodeCount+2<<"[label=\"equality_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"NE_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
;
relational_expression: 
          additive_expression   {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"relational_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
        | relational_expression '<' additive_expression {
          std::cout<<nodeCount+2<<"[label=\"relational_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"<\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
  | relational_expression '>' additive_expression {
          std::cout<<nodeCount+2<<"[label=\"relational_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\">\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
  | relational_expression LE_OP additive_expression {
          std::cout<<nodeCount+2<<"[label=\"relational_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"LE_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
        | relational_expression GE_OP additive_expression {
          std::cout<<nodeCount+2<<"[label=\"relational_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"GE_OP\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
; 

additive_expression: 
          multiplicative_expression   {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"additive_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
  | additive_expression '+' multiplicative_expression {
          std::cout<<nodeCount+2<<"[label=\"additive_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"+\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
  | additive_expression '-' multiplicative_expression {
          std::cout<<nodeCount+2<<"[label=\"additive_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"-\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
; 

multiplicative_expression: 
          unary_expression   {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"multiplicative_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;      
          }
  | multiplicative_expression '*' unary_expression {
          std::cout<<nodeCount+2<<"[label=\"multiplicative_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"*\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
  | multiplicative_expression '/' unary_expression {
          std::cout<<nodeCount+2<<"[label=\"multiplicative_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"/\"]"<<std::endl;
            std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;      
            std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;      
            nodeCount += 2;
                  $$ = nodeCount;
        }
;
unary_expression: 
          postfix_expression  {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"unary_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;
          }        
  | unary_operator postfix_expression   {
    $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"unary_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;
            std::cout<<$$<<" -> "<<$2<<std::endl;
  }
;
postfix_expression: 
          primary_expression {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"postfix_expression\"]"<<std::endl;
            std::cout<<$$<<" -> "<<$1<<std::endl;
          }
        | IDENTIFIER '(' ')' {
          std::cout<<nodeCount+4<<"[label=\"postfix_expression\"]"<<std::endl;
            std::cout<<nodeCount+3<<"[label=\"IDENTIFIER\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+3<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 4;
                  $$ = nodeCount;
        }
  | IDENTIFIER '(' expression_list ')' {
    std::cout<<nodeCount+4<<"[label=\"postfix_expression\"]"<<std::endl;
            std::cout<<nodeCount+3<<"[label=\"IDENTIFIER\"]"<<std::endl;
          std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+3<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<$3<<std::endl;
          std::cout<<nodeCount+4<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 4;
                  $$ = nodeCount;
  }
  | l_expression INC_OP {
    std::cout<<nodeCount+2<<"[label=\"postfix_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"INC_OP\"]"<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
          
          nodeCount += 2;
                  $$ = nodeCount;
  }
;
primary_expression: 
          l_expression {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"primary_expression\"]"<<std::endl;
          std::cout<<$$<<" -> "<<$1<<std::endl;
          }
        | l_expression '=' expression {
          std::cout<<nodeCount+2<<"[label=\"primary_expression\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"=\"]"<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
          std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;

          nodeCount += 2;
          $$ = nodeCount;
        }
  | INT_CONSTANT
  {
    std::cout<<nodeCount+2<<"[label=\"primary_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"INT_CONSTANT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

  }
  | FLOAT_CONSTANT {
    std::cout<<nodeCount+2<<"[label=\"primary_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"FLOAT_CONSTANT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

  }
        | STRING_LITERAL
        {
    std::cout<<nodeCount+2<<"[label=\"primary_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"STRING_CONSTANT\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

  }
  | '(' expression ')'  { 
            std::cout<<nodeCount+3<<"[label=\"primary_expression\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 3;
                  $$ = nodeCount;
  }
;
l_expression: 
          IDENTIFIER {
    std::cout<<nodeCount+2<<"[label=\"l_expression\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"IDENTIFIER\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

  }
        | l_expression '[' expression ']'   { 
            std::cout<<nodeCount+3<<"[label=\"l_expression\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"[\"]"<<std::endl;
          std::cout<<nodeCount+1<<"[label=\"]\"]"<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$1<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+2<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<$3<<std::endl;
          std::cout<<nodeCount+3<<" -> "<<nodeCount+1<<std::endl;
          nodeCount += 3;
                  $$ = nodeCount;
  }
;
expression_list: 
          expression {
            $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"expression_list\"]"<<std::endl;
          std::cout<<$$<<" -> "<<$1<<std::endl;
          }
        | expression_list ',' expression   {
    std::cout<<nodeCount+2<<"[label=\"expression_list\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\",\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

  }
;
unary_operator: 
          '-' { 
                  std::cout<<nodeCount+2<<"[label=\"unary_operator\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"-\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

            }
  | '!'   { 
                  std::cout<<nodeCount+2<<"[label=\"unary_operator\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\"!\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

            }
;
selection_statement: 
          IF '(' expression ')' statement ELSE statement {
            std::cout<<nodeCount+5<<"[label=\"selection_statement\"]"<<std::endl;
            std::cout<<nodeCount+4<<"[label=\"IF\"]"<<std::endl;
            std::cout<<nodeCount+3<<"[label=\"(\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\")\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\"ELSE\"]"<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<nodeCount+4<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<nodeCount+3<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<$3<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<nodeCount+2<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<$5<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<nodeCount+1<<std::endl;
                  std::cout<<nodeCount+5<<" -> "<<$7<<std::endl;
                  nodeCount += 5;
                  $$ = nodeCount;
          }
;
iteration_statement: 
          WHILE '(' expression ')' statement  {
            std::cout<<nodeCount+4<<"[label=\"iteration_statement\"]"<<std::endl;
            std::cout<<nodeCount+3<<"[label=\"WHILE\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\"(\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+3<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+2<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<$3<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<nodeCount+1<<std::endl;
                  std::cout<<nodeCount+4<<" -> "<<$5<<std::endl;
                  
                  nodeCount += 4;
                  $$ = nodeCount;
          }
        | FOR '(' expression ';' expression ';' expression ')' statement {
          
            std::cout<<nodeCount+6<<"[label=\"iteration_statement\"]"<<std::endl;
            std::cout<<nodeCount+5<<"[label=\"FOR\"]"<<std::endl;
            std::cout<<nodeCount+4<<"[label=\"(\"]"<<std::endl;
            std::cout<<nodeCount+3<<"[label=\";\"]"<<std::endl;
            std::cout<<nodeCount+2<<"[label=\";\"]"<<std::endl;
            std::cout<<nodeCount+1<<"[label=\")\"]"<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<nodeCount+5<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<nodeCount+4<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<$3<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<nodeCount+3<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<$5<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<nodeCount+2<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<$7<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<nodeCount+1<<std::endl;
                  std::cout<<nodeCount+6<<" -> "<<$9<<std::endl;
                  nodeCount += 6;
                  $$ = nodeCount;
          }
        
;
declaration_list: 
          declaration           { $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"declaration_list\"]"<<std::endl;
                  std::cout<<$$<<" -> "<<$1<<std::endl;
             }
        | declaration_list declaration { $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"declaration_list\"]"<<std::endl;
                  std::cout<<$$<<" -> "<<$1<<std::endl;
              std::cout<<$$<<" -> "<<$2<<std::endl;
             
            }
;
declaration: 
          type_specifier declarator_list';' { 
                  std::cout<<nodeCount+2<<"[label=\"declaration\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\";\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$2<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

            }
;
declarator_list: 
          declarator { $$ = ++nodeCount;
            std::cout<<$$<<"[label=\"declarator_list\"]"<<std::endl;
                  std::cout<<$$<<" -> "<<$1<<std::endl;
             }
  | declarator_list ',' declarator { 
                  std::cout<<nodeCount+2<<"[label=\"declarator_list\"]"<<std::endl;
                  std::cout<<nodeCount+1<<"[label=\",\"]"<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$1<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<nodeCount+1<<std::endl;
                  std::cout<<nodeCount+2<<" -> "<<$3<<std::endl;
                  nodeCount += 2;
                  $$ = nodeCount;

            }
;
