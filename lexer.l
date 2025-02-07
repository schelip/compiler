%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "syntax.h"
  #include "parser.tab.h"
  void yyerror(char *);
  char *copytext(char *text);
%}

%option yylineno
%option nodefault

/* util regular expressions */
letter          [a-zA-Z]
digit           [0-9]
alphanum        {letter}|{digit}
allchars        [ -~]
escapechars     \\[bfnrtv]
linebreak       [\n|\r|\r\n]

/* literals */
literal_int       {digit}+
literal_float     {digit}*\.{digit}+
literal_char      \'({allchars}|{escapechars})\'
literal_str       \"({allchars}|{escapechars})*\"
literal_bool      true|false

id              ({letter}|_)({alphanum}|_)*

comm            \/\*([^*]|\*[^\/])*\*\/

symbols         [-+*/%=!<>\(\)\[\]\{\},:;]

%%

{literal_int}   {
                  fprintf(yyout, "LITERAL_INT");
                  yylval.i_value = atoi(yytext);
                  return LITERAL_INT;
                }
{literal_float} {
                  fprintf(yyout, "LITERAL_FLOAT");
                  yylval.f_value = atof(yytext);
                  return LITERAL_FLOAT;
                }
{literal_char}  {
                  fprintf(yyout, "LITERAL_CHAR");
                  yylval.c_value = yytext[1];
                  return LITERAL_CHAR;
                }
{literal_str}   {
                  fprintf(yyout, "LITERAL_STRING");
                  yylval.s_value = copytext(yytext);
                  return LITERAL_STRING;
                }
{literal_bool}  {
                  fprintf(yyout, "LITERAL_BOOL");
                  return LITERAL_BOOL;
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
"array"         {
                  fprintf(yyout, "ARRAY");
                  return ARRAY;
                }
"of"            {
                  fprintf(yyout, "OF");
                  return OF;
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
"bool"          {
                  fprintf(yyout, "BOOL");
                  return BOOL;
                }
{id}            {
                  fprintf(yyout, "ID");
                  yylval.s_value = copytext(yytext);
                  return ID;
                }
{comm}          ;
{symbols}       {
                  ECHO;
                  return *yytext;
                }
{linebreak}     {
                  ECHO;
                }
[ \t]           {
                  ECHO;
                }
.               {
                  fprintf(stderr, "Error: unexpected character \'%s\' at line %d\n", yytext, yylineno);
                  exit(EXIT_FAILURE);
                }

%%

int yywrap()
{
  return 1;
}

char *copytext(char *text) {
  size_t len = strlen(text);             
  char *val = malloc(sizeof(char *) * len + 1);
  val = strncpy(val, yytext, len);
  val[len] = '\0';
  return val;
}