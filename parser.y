%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "ast.h"

  int yylex(void);
  void yyerror(const char *);
  int yydebug = 1;

  extern FILE *yyin, *yyout;
  extern int yylineno, yy_flex_debug;
  extern char *yytext;
  extern int yywrap();

  extern FILE *astout;
  NodeProgram program_node;
%}

%union {
  int i_value;
  float f_value;
  char c_value;
  char *s_value;
  int b_value;
  DataType enum_data_type;
  SignOperator enum_sign_operator;
  RelationalOperator enum_relational_operator;
  AdditiveOperator enum_additive_operator;
  MultiplicativeOperator enum_multiplicative_operator;
  NodeProgram node_program;
  NodeVarDeclList node_var_decl_list;
  NodeVarDecl node_var_decl;
  NodeVarIdList node_var_id_list;
  NodeTypeSpecifier node_type_specifier;
  NodeFuncDeclList node_func_decl_list;
  NodeFuncDecl node_func_decl;
  NodeFuncHeader node_func_header;
  NodeFuncParamList node_func_param_list;
  NodeFuncParam node_func_param;
  NodeStmtBlock node_stmt_block;
  NodeStmtList node_stmt_list;
  NodeStmt node_stmt;
  NodeVarAccess node_var_access;
  NodeFuncCall node_func_call;
  NodeArgList node_arg_list;
  NodeExpression node_expression;
  NodeSimpleExpression node_simple_expression;
  NodeTerm node_term;
  NodeFactor node_factor;
  NodeLiteral node_literal;
}

%token <i_value> LITERAL_INT
%token <f_value> LITERAL_FLOAT
%token <c_value> LITERAL_CHAR
%token <s_value> LITERAL_STRING
%token <b_value> LITERAL_BOOL
%token  '=' '+' '-' '*' '/' '%' UPLUS UMINUS '<' '>' EQ NE GE LE NOT AND OR /* operators */
%token VAR ARRAY OF FUNCTION RETURN /* keywords */
%token INT FLOAT CHAR STRING BOOL /* types */
%token IF WHILE /* control structures */
%nonassoc IFX
%nonassoc ELSE
%token <s_value> ID

%start program

%type <node_program> program
%type <node_var_decl_list> variable_declaration_list
%type <node_var_decl> variable_declaration
%type <s_value> variable_identifier
%type <node_var_id_list> variable_identifier_list
%type <node_type_specifier> type_specifier
%type <node_type_specifier> primitive_type_specifier
%type <node_type_specifier> array_type_specifier
%type <enum_data_type> data_type
%type <node_func_decl_list> function_declaration_list
%type <node_func_decl> function_declaration
%type <node_func_header> function_header
%type <s_value> function_identifier
%type <node_func_param_list> function_parameters
%type <node_func_param_list> parameter_list
%type <node_func_param> parameter
%type <node_stmt_block> statement_block
%type <node_stmt_list> statement_list
%type <node_stmt> statement
%type <node_stmt> attribution_statement
%type <node_stmt> function_call_statement
%type <node_stmt> comparison_structure
%type <node_stmt> ifx_statement
%type <node_stmt> ifelse_statement
%type <node_stmt> iteration_structure
%type <node_stmt> return_statement
%type <node_var_access> variable_access
%type <node_var_access> simple_variable_access
%type <node_var_access> array_access
%type <node_func_call> function_call
%type <node_arg_list> argument_list
%type <node_expression> expression
%type <node_simple_expression> simple_expression
%type <node_term> term
%type <node_factor> factor
%type <enum_sign_operator> sign
%type <enum_relational_operator> relational_operator
%type <enum_additive_operator> additive_operator
%type <enum_multiplicative_operator> multiplicative_operator
%type <node_literal> literal

%%

program : variable_declaration_list function_declaration_list statement_block
        {
          $$ = create_ast_node_program($1, $2, $3);
          program_node = $$;
        } ;

variable_declaration_list : /* epsilon  */ { $$ = NULL; }
                          | variable_declaration variable_declaration_list { $$ = create_ast_node_var_decl_list($1, $2); }
                          ;
                    
variable_declaration : VAR variable_identifier_list ':' type_specifier ';' { $$ = create_ast_node_var_decl($2, $4); } ;

variable_identifier_list : variable_identifier { $$ = create_ast_node_var_id_list($1, NULL); }
                         | variable_identifier ',' variable_identifier_list { $$ = create_ast_node_var_id_list($1, $3); }
                         ;

variable_identifier : ID ;

type_specifier : primitive_type_specifier
               | array_type_specifier
               ;

primitive_type_specifier : data_type { $$ = create_ast_node_primitive_type_specifier($1); } ;
                        
array_type_specifier : ARRAY '[' LITERAL_INT ']' OF data_type { $$ = create_ast_node_array_type_specifier($6, $3); } ;

data_type : INT { $$ = type_int; }
          | FLOAT { $$ = type_float; }
          | CHAR  { $$ = type_char; }
          | STRING { $$ = type_string; }
          | BOOL { $$ = type_bool; }
          ;

function_declaration_list : /* epsilon */ { $$ = NULL; }
                          | function_declaration function_declaration_list { $$ = create_ast_node_func_decl_list($1, $2); }
                          ;

function_declaration : function_header statement_block { $$ = create_ast_node_func_decl($1, $2); } ;

function_header : FUNCTION function_identifier function_parameters { $$ = create_ast_node_func_header($2, $3, NULL); }
                | FUNCTION function_identifier function_parameters ':' type_specifier { $$ = create_ast_node_func_header($2, $3, $5); }
                ;

function_identifier : ID ;

function_parameters : '(' ')' { $$ = NULL; }
                    | '(' parameter_list ')' { $$ = $2; } ;

parameter_list : parameter { $$ = create_ast_node_func_param_list($1, NULL); }
               | parameter ';' parameter_list { $$ = create_ast_node_func_param_list($1, $3); }
               ;

parameter : variable_identifier_list ':' type_specifier { $$ = create_ast_node_func_param($1, $3); } ;

statement_block : '{' variable_declaration_list statement_list '}' { $$ = create_ast_node_stmt_block($2, $3); } ;

statement_list : /* epsilon */ { $$ = NULL; }
               | statement statement_list { $$ = create_ast_node_stmt_list($1, $2); }
               ;

statement : attribution_statement
          | function_call_statement
          | comparison_structure
          | iteration_structure
          | return_statement
          | statement_block { $$ = create_ast_node_block_stmt($1); }
          ;

attribution_statement : variable_access '=' expression ';' { $$ = create_ast_node_attribution_stmt($1, $3); } ;

variable_access : simple_variable_access
                | array_access
                ;

simple_variable_access : ID { $$ = create_ast_node_simple_var_access($1); } ;

array_access : ID '[' expression ']' { $$ = create_ast_node_array_access($1, $3); } ;

function_call_statement : function_call ';' { $$ = create_ast_node_func_call_stmt($1); } ;

function_call : ID '(' ')' { $$ = create_ast_node_func_call($1, NULL); }
              | ID '(' argument_list ')' { $$ = create_ast_node_func_call($1, $3); };
              ;

argument_list : expression { $$ = create_ast_node_arg_list($1, NULL); }
              | expression ',' argument_list { $$ = create_ast_node_arg_list($1, $3); }
              ;

comparison_structure : ifx_statement
                     | ifelse_statement
                     ;

ifx_statement : IF '(' expression ')' statement %prec IFX { $$ = create_ast_node_ifx_stmt($3, $5); };

ifelse_statement : IF '(' expression ')' statement ELSE statement { $$ = create_ast_node_ifelse_stmt($3, $5, $7); } ;

iteration_structure : WHILE '(' expression ')' statement { $$ = create_ast_node_iteration_stmt($3, $5); } ;

return_statement : RETURN expression ';' { $$ = create_ast_node_return_stmt($2); } ;

expression : simple_expression { $$ = create_ast_node_simple_expr_expression($1); }
           | simple_expression relational_operator simple_expression { $$ = create_ast_node_relational_expr_expression($1, $2, $3); }
           ;

simple_expression : term { $$ = create_ast_node_term_simple_expr($1); }
                  | sign term { $$ = create_ast_node_sign_simple_expr($1, $2); }
                  | simple_expression additive_operator term { $$ = create_ast_node_additive_simple_expr($1, $2, $3); }
                  ;

term : factor { $$ = create_ast_node_factor_term($1); }
     | term multiplicative_operator factor { $$ = create_ast_node_multiplicative_term($1, $2, $3); }
     ;

factor : variable_access { $$ = create_ast_node_var_access_factor($1); }
       | function_call { $$ = create_ast_node_func_call_factor($1); }
       | '(' expression ')' { $$ = create_ast_node_parenthesized_expr_factor($2); }
       | literal { $$ = create_ast_node_literal_factor($1); }
       | NOT factor { $$ = create_ast_node_not_factor($2); }
       ;

sign : '+' %prec UPLUS { $$ = op_uplus; }
     | '-' %prec UMINUS { $$ = op_uminus; }
     ;

relational_operator : EQ { $$ = op_eq; }
                    | NE { $$ = op_ne; }
                    | '<' { $$ = op_gt; }
                    | GE { $$ = op_ge; }
                    | '>' { $$ = op_lt; }
                    | LE { $$ = op_le; }
                    ;

additive_operator : '+' { $$ = op_plus; }
                  | '-' { $$ = op_minus; }
                  | OR { $$ = op_or; }
                  ;

multiplicative_operator : '*' { $$ = op_mul; }
                        | '/' { $$ = op_div; }
                        | '%' { $$ = op_mod; }
                        | AND { $$ = op_and; }
                        ;

literal : LITERAL_INT { $$ = create_ast_node_int_literal($1); }
        | LITERAL_FLOAT { $$ = create_ast_node_float_literal($1); }
        | LITERAL_CHAR { $$ = create_ast_node_char_literal($1); }
        | LITERAL_STRING { $$ = create_ast_node_string_literal($1); }
        | LITERAL_BOOL { $$ = create_ast_node_bool_literal($1); }
        ;

%%

void yyerror(const char *s)
{
  fflush(stderr);
  fprintf(stderr, "Error:  %s at line %d\n", s, yylineno);
}

int main(int argc, char* argv[])
{
  yyout=fopen("test.src.out","w");
  astout=fopen("ast.out", "w");
  yyparse();
  fflush(yyout);
  print_ast_node_program(program_node, 0);
  return EXIT_SUCCESS;
}
