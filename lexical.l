%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "y.tab.h"
  void yyerror(char *);
  int yylineno;
%}

%option yylineno
%option nodefault

/* util regular expressions */
letter          [a-zA-Z]
digit           [0-9]
alphanum        {letter}|{digit}
allchars        [ -~]
escapechars     \\[bfnrtv]

/* constants */
const_int       {digit}+
const_float     {digit}*\.{digit}+
const_char      \'({allchars}|{escapechars})\'
const_string    \"({allchars}|{escapechars})*\"
const_bool      true|false

id              ({letter}|_)({alphanum}|_)*

comm            \/\*(.)+\*\/

symbols         [-+*/%=!<>\(\)\[\]\{\},:;]

%%

{const_int}     {
                  yylval = atoi(yytext);
                  fprintf(yyout, "CONST_INT");
                  return CONST_INT;
                }
{const_float}   {
                  yylval = atof(yytext);
                  fprintf(yyout, "CONST_FLOAT");
                  return CONST_FLOAT;
                }
{const_char}    {
                  fprintf(yyout, "CONST_INT");
                  return CONST_CHAR;
                }
{const_string}  {
                  fprintf(yyout, "CONST_STRING");
                  return CONST_STRING;
                }
{const_bool}    {
                  fprintf(yyout, "CONST_BOOL");
                  return CONST_BOOL;
                }
"!!"            {
                  fprintf(yyout, "AND");
                  return AND;
                }
"||"            {
                  fprintf(yyout, "OR");
                  return OR;
                }
"=="            {
                  fprintf(yyout, "EQ");
                  return EQ;
                }
"!="            {
                  fprintf(yyout, "NE");
                  return NE;
                }
"<="            {
                  fprintf(yyout, "LE");
                  return LE;
                }
">="            {
                  fprintf(yyout, "GE");
                  return GE;
                }
"var"           {
                  fprintf(yyout, "VAR");
                  return VAR;
                }
"if"            {
                  fprintf(yyout, "IF");
                  return IF;
                }
"else"          {
                  fprintf(yyout, "ELSE");
                  return ELSE;
                }
"while"         {
                  fprintf(yyout, "WHILE");
                  return WHILE;
                }
"return"        {
                  fprintf(yyout, "RETURN");
                  return RETURN;
                }
"function"      {
                  fprintf(yyout, "FUNCTION");
                  return FUNCTION;
                }
"int"           {
                  fprintf(yyout, "INT");
                  return INT;
                }
"float"         {
                  fprintf(yyout, "FLOAT");
                  return FLOAT;
                }
"char"          {
                  fprintf(yyout, "CHAR");
                  return CHAR;
                }
"string"        {
                  fprintf(yyout, "STRING");
                  return STRING;
                }
{id}            {
                  fprintf(yyout, "ID");
                  return ID;
                }
{comm}          {
                  fprintf(yyout, "comment");
                }
{symbols}       {
                  ECHO;
                  return *yytext;
                }
[\n|\r|\r\n]    {
                  ECHO;
                  yylineno++;
                }
[ \t]           {
                  ECHO;
                }
<<EOF>>         {
                  return END;
                  yyterminate();
                }
.               {
                  fprintf(yyout, "Error: unrecognized character at line %d", yylineno);
                }

%%

int yywrap()
{
  return 1;
}

/* int main(int argc, char* argv[]) {
  yyin=fopen("test.src","r");
  yyout=fopen("test.src.out", "w");
  yylex();
  return EXIT_SUCCESS;
} */
