%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex(void);
  void yyerror(const char *);
  int yydebug=1;
  extern FILE* yyin;
  extern FILE* yyout;
  extern int yylineno;
  extern int yy_flex_debug; 
%}

%token CONST_INT CONST_FLOAT CONST_CHAR CONST_STRING CONST_BOOL
%token '+' '-' '*' '/' '%' NOT AND OR
%token VAR RETURN FUNCTION
%token INT FLOAT CHAR STRING BOOL
%token IF ELSE WHILE
%nonassoc IFX
%nonassoc ELSE
%token ID END

%left GE LE '<' '>'
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS
%nonassoc EQ NE
%nonassoc '='

%%

program : statement_list END {
                                fprintf(yyout, "-> End\n");
                                exit(1);
                             }
        ;

statement_list : statement 
               | statement_list statement  
               ;

statement_block : '{' statement_list '}'
                ;

statement : variable_declaration_statement 
          | function_declaration_statement 
          | attribution_statement
          | expression_statement 
          | condition_statement 
          | iteration_statement 
          | return_statement 
          | ';'
          ;

variable_declaration_statement : VAR ID ':' type_specifier ';' { fprintf(yyout, " -> Variable Declaration Statement"); }
                               | VAR ID ':' type_specifier '=' expression_statement { fprintf(yyout, " -> Variable Declaration Statement with Assignment"); }
                               ;

function_declaration : FUNCTION ID '(' parameter_list ')' { fprintf(yyout, " -> Function Declaration"); }
                     | FUNCTION ID '('')' { fprintf(yyout, " -> Function Declaration without parameters"); }
                     | FUNCTION ID '(' parameter_list ')' ':' type_specifier { fprintf(yyout, " -> Function Declaration with Return Type"); }
                     | FUNCTION ID '('')' ':' type_specifier { fprintf(yyout, " -> Function Declaration without Parameters with Return Type"); }
                     ;

function_declaration_statement : function_declaration statement_block
                               | function_declaration ';'
                               ;

parameter_list : parameter 
               | parameter_list ',' parameter
               ;

parameter : ID ':' type_specifier { fprintf(yyout, " -> Parameter"); }
          ;

attribution_statement : ID '=' expression_statement { fprintf(yyout, " -> Attribution Statement"); }
                      ;

expression_statement : expression ';'
                     ;

condition_statement : IF '(' expression ')' statement_block { fprintf(yyout, " -> If Statement"); } %prec IFX
                    | IF '(' expression ')' statement_block ELSE statement_block { fprintf(yyout, " -> If Else Statement"); }
                    ;

iteration_statement : WHILE '(' expression ')' statement_block { fprintf(yyout, " -> While Statement"); }
                    ;

return_statement : RETURN expression_statement { fprintf(yyout, " -> Return Statement"); }
                 ;

type_specifier : INT { fprintf(yyout, " -> Integer Type"); }
               | FLOAT { fprintf(yyout, " -> Float Type"); }
               | CHAR { fprintf(yyout, " -> Char Type"); }
               | STRING { fprintf(yyout, " -> String Type"); }
               | BOOL { fprintf(yyout, " -> Bool Type"); }
               ;

expression : term
           | expression term_operator term
           ;

term_operator : OR
              | '+' { fprintf(yyout, " -> Addition Operator"); }
              | '-' { fprintf(yyout, " -> Subtraction Operator"); }
              ;

term : factor
     | term factor_operator factor
     ;

factor_operator : AND
                | EQ
                | NE
                | '<'
                | LE
                | '>'
                | GE
                | '*'
                | '/'
                | '%'
                ;

factor : value
       | unary_operator value
       ;

unary_operator : '-' %prec UMINUS
               | NOT
               ;

value : '(' expression ')' { fprintf(yyout, " -> Expression in Parentheses"); }
      | const { fprintf(yyout, " -> Constant"); }
      | ID { fprintf(yyout, " -> Identifier"); }
      | function_call { fprintf(yyout, " -> Function Call"); }
      ;

const : CONST_INT
      | CONST_FLOAT
      | CONST_CHAR
      | CONST_STRING
      | CONST_BOOL
      ;

function_call : ID'('')' { fprintf(yyout, " -> Function Call without Arguments"); }
              | ID'(' argument_list ')' { fprintf(yyout, " -> Function Call with Arguments"); }
              ;

argument_list : expression { fprintf(yyout, " -> Argument"); }
              | argument_list ',' expression { fprintf(yyout, " -> Argument List"); }
              ;

%%

void yyerror(const char *s)
{
  fprintf(stderr, "Syntax error:  %s at line %d\n", s, yylineno);
}

int main(int argc, char* argv[])
{
  yyin=fopen("test.src","r");
  yyout=fopen("test.src.out","w");
  yyparse();
  fclose(yyin);
  return EXIT_SUCCESS;
}
