%{
    #include <stdio.h>
    int yydebug=1;
%}

%token const_int const_float const_char const_string const_bool
%token op_sum op_sub op_mul op_div op_mod /*op_att*/ op_not op_and op_or /*op_equ op_neq op_les op_leq op_gre op_geq*/
%token kw_var kw_if kw_else kw_while kw_return kw_function kw_int kw_float kw_char kw_string
%token id
%token newline

%nonassoc op_equ op_neq op_les op_leq op_gre op_geq
%nonassoc op_att

%%

program : statement_list newline {
                                    printf("\nComplete\n");
                                    exit(1);
                                 }
        ;

statement_list : statement 
               | statement statement_list 
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
          ;

variable_declaration_statement : kw_var id ':' type_specifier ';'
                     | kw_var id ':' type_specifier op_att expression_statement 
                     ;

function_declaration_statement : kw_function id '(' parameter_list ')' statement_block 
                     | kw_function id '(' parameter_list ')' ':' type_specifier statement_block 
                     ;

parameter_list : parameter 
               | parameter ',' parameter_list 
               ;

parameter : id ':' type_specifier
          ;

attribution_statement : id op_att expression_statement
                      ;

expression_statement : expression ';' 
                     ;

condition_statement : kw_if '(' expression ')' statement_block
                    | kw_if '(' expression ')' statement_block kw_else statement_block 
                    ;

iteration_statement : kw_while '(' expression ')' statement_block 
                    ;

return_statement : kw_return expression_statement
                 ;

type_specifier : kw_int 
               | kw_float 
               | kw_char 
               | kw_string 
               ;

expression : term
           | term term_operator expression
           ;

term_operator : op_or
              | op_sum
              | op_sub
              ;

term : factor
     | factor factor_operator term
     ;

factor_operator : op_and
                | op_equ
                | op_neq
                | op_les
                | op_leq
                | op_gre
                | op_geq
                | op_mul
                | op_div
                | op_mod
                ;

factor : value
       | unary_operator value
       ;

unary_operator : op_sub
               | op_not
               ;

value : '(' expression ')'
      | const
      | id
      | function_call
      ;

const : const_int
      | const_float
      | const_char
      | const_string
      | const_bool
      ;

/* expression : boolean_expression
           | arithmetic_expression 
           | id
           | function_call
           | const_char
           | const_string
           ;

boolean_expression : boolean_term
                   | boolean_term op_or boolean_expression
                   ;

boolean_term : boolean_factor
             | boolean_factor op_and boolean_term
             ;

boolean_factor : '(' boolean_expression ')'
               | op_not boolean_factor
               | arithmetic_expression relative_operator arithmetic_expression
               | id
               | function_call
               | const_bool
               ;

relative_operator : op_equ
                  | op_neq
                  | op_les
                  | op_leq
                  | op_gre
                  | op_geq
                  ;

arithmetic_expression : arithmetic_term
                      | arithmetic_term op_sum arithmetic_expression
                      | arithmetic_term op_sub arithmetic_expression
                      ;

arithmetic_term : arithmetic_factor
                | arithmetic_factor op_mul arithmetic_term
                | arithmetic_factor op_div arithmetic_term
                | arithmetic_factor op_mod arithmetic_term
                ;

arithmetic_factor : '(' arithmetic_expression ')'
                  | id
                  | function_call
                  | numeric_const
                  ;

numeric_const : const_int
              | const_float
              ; */

function_call : id'(' argument_list ')'
              ;

argument_list : expression
              | expression ',' argument_list
              ;

%%

void yyerror(char const *s)
{
    printf("yyerror  %s\n",s);
    return ;
}

int main()
{
  yyparse();
  return 1;
}
    