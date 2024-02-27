%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "symbol.h"

  int yylex(void);
  void yyerror(const char *);
  int yydebug = 1;

  extern FILE *yyin, *yyout;
  extern int yylineno, yy_flex_debug;
  extern char * yytext;
  extern int yywrap();

  void finalize();
%}

%union {
  int i_value;
  float f_value;
  char c_value;
  char s_value[1000];
  int b_value;
};  

%token <i_value> LITERAL_INT
%token <f_value> LITERAL_FLOAT
%token <c_value> LITERAL_CHAR
%token <s_value> LITERAL_STRING
%token <b_value> LITERAL_BOOL
%token '+' '-' '*' '/' '%' NOT AND OR
%token VAR ARRAY OF FUNCTION RETURN
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

program : variable_declaration_list function_declaration_list statement_block END { fprintf(yyout, " -> End\n"); finalize(); } ;

variable_declaration_list : /* epsilon  */
                          | variable_declaration_list variable_declaration
                          ;
                    
variable_declaration : VAR variable_identifier_list ':' type_specifier ';' { fprintf(yyout, " -> Variable declaration "); } ;

variable_identifier_list : variable_identifier
                         | variable_identifier_list ',' variable_identifier
                         ;

variable_identifier : ID { fprintf(yyout, " -> Variable "); add_symbol(s_variable); };

type_specifier : base_type_specifier
               | ARRAY '[' LITERAL_INT ']' OF base_type_specifier
               ;

base_type_specifier : INT { next_symbol ->d_type = d_int; }
                    | FLOAT { next_symbol ->d_type = d_float; }
                    | CHAR { next_symbol ->d_type = d_char; }
                    | STRING { next_symbol ->d_type = d_string; }
                    | BOOL { next_symbol ->d_type = d_bool; }
                    ;

function_declaration_list : /* epsilon */
                          | function_declaration_list function_declaration
                          ;

function_declaration : function_header { fprintf(yyout, " -> Function header "); } variable_declaration_list statement_block ;

function_header : FUNCTION function_name function_parameters
                | FUNCTION function_name function_parameters ':' type_specifier
                ;

function_name : ID { strcpy(next_symbol ->name, yytext); } ;

function_parameters : '(' ')'
                    | '(' parameter_list ')' ;

parameter_list : parameter
               | parameter_list ';' parameter
               ;

parameter : variable_identifier_list ':' type_specifier

statement_block : '{' statement_list '}' ;

statement_list : /* epsilon */
               | statement_list statement
               ;

statement : attribution_statement
          | function_call_statement
          | comparison_structure
          | iteration_structure
          | return_statement
          | statement_block
          ;

attribution_statement : ID '=' expression ';' { fprintf(yyout, " -> Attribution statement "); }

function_call : ID '(' ')'
              | ID '(' argument_list ')'
              ;

function_call_statement : function_call ';' { fprintf(yyout, " -> Function call statement "); }

argument_list : expression
              | argument_list ',' expression
              ;

comparison_structure : IF '(' expression ')' statement %prec IFX
                     | IF '(' expression ')' statement ELSE statement { fprintf(yyout, " -> If-else statement "); }
                     ;

iteration_structure : WHILE '(' expression ')' statement { fprintf(yyout, " -> While loop "); }

return_statement : RETURN expression ';' { fprintf(yyout, " -> Return statement "); }

expression : simple_expression
           | simple_expression relational_operator simple_expression
           ;

simple_expression : term
                  | sign term
                  | simple_expression additive_operator term
                  ;

term : factor
     | term multiplicative_operator factor
     ;

factor : ID
       | function_call
       | '(' expression ')'
       | literal { strcpy(next_symbol ->name, yytext); add_symbol(s_literal); }
       | NOT factor
       ;

sign : '+' | '-' %prec UMINUS ;

relational_operator : EQ | NE | '<' | GE | '>' | LE ;

additive_operator : '+' | '-' | OR ;

multiplicative_operator : '*' | '/' | '%' | AND ;

literal : LITERAL_INT
        | LITERAL_FLOAT
        | LITERAL_CHAR
        | LITERAL_STRING
        | LITERAL_BOOL
        ;

%%

void yyerror(const char *s)
{
  fprintf(stderr, "Error:  %s at line %d\n", s, yylineno);
}

void finalize()
{
  print_symbol_table();
  for (int i = 0; i < symbol_count; i++)
    free(symbol_table[i]);
  free(next_symbol);
  exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[])
{
  yyout=fopen("test.src.out","w");
  allocate_symbol();
  yyparse();
  return EXIT_SUCCESS;
}
