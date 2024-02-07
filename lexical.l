%option noyywrap

%{
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

   FILE *fout;
%}

/* util regular expressions */
letter      [a-zA-Z]
digit       [0-9]
alphanum    {letter}|{digit}
allchars    [ -~]
escapechars \\[bfnrtv]

/* constants */
const_int      {digit}+
const_float    {digit}*\.{digit}+
const_char     \'({allchars}|{escapechars})\'
const_string   \"({allchars}|{escapechars})*\"

/* operations */
op_sum         \+
op_sub         -
op_mul         \*
op_div         \/
op_mod         %
op_att         =
op_equ         ==
op_neq         !=
op_les         <
op_leq         <=
op_gre         >
op_geq         >=

/* keywords */
kw_var         var
kw_if          if
kw_else        else
kw_while       while
kw_return      return
kw_function    function
kw_int         int
kw_float       float
kw_char        char
kw_string      string

/* delimiters */
d_oppar        \(
d_clpar        \)
d_opsqbr       \[
d_clsqbr       \]
d_opbrack      \{
d_clbrack      \}
d_comma        ,
d_colon        :
d_semicolon    ;
d_ws           [ \n\t\r]+

/* identifier */
id             ({letter}|_)({alphanum}|_)*

/* comment */
comm           \/\/(.)+

%%

{const_int}       {fprintf(fout, "const_int ");}
{const_float}     {fprintf(fout, "const_float ");}
{const_char}      {fprintf(fout, "const_char ");}
{const_string}    {fprintf(fout, "const_string ");}
{op_sum}          {fprintf(fout, "op_sum ");}
{op_sub}          {fprintf(fout, "op_sub ");}
{op_mul}          {fprintf(fout, "op_mul ");}
{op_div}          {fprintf(fout, "op_div ");}
{op_mod}          {fprintf(fout, "op_mod ");}
{op_att}          {fprintf(fout, "op_att ");}
{op_equ}          {fprintf(fout, "op_equ ");}
{op_neq}          {fprintf(fout, "op_neq ");}
{op_les}          {fprintf(fout, "op_les ");}
{op_leq}          {fprintf(fout, "op_leq ");}
{op_gre}          {fprintf(fout, "op_gre ");}
{op_geq}          {fprintf(fout, "op_geq ");}
{kw_var}          {fprintf(fout, "kw_var ");}
{kw_if}           {fprintf(fout, "kw_if ");}
{kw_else}         {fprintf(fout, "kw_else ");}
{kw_while}        {fprintf(fout, "kw_while ");}
{kw_return}       {fprintf(fout, "kw_return ");}
{kw_function}     {fprintf(fout, "kw_function ");}
{kw_int}          {fprintf(fout, "kw_int ");}
{kw_float}        {fprintf(fout, "kw_float ");}
{kw_char}         {fprintf(fout, "kw_char ");}
{kw_string}       {fprintf(fout, "kw_string ");}
{d_oppar}         {fprintf(fout, "d_oppar ");}
{d_clpar}         {fprintf(fout, "d_clpar ");}
{d_opsqbr}        {fprintf(fout, "d_opsqbr ");}
{d_clsqbr}        {fprintf(fout, "d_clsqbr ");}
{d_opbrack}       {fprintf(fout, "d_opbrack ");}
{d_clbrack}       {fprintf(fout, "d_clbrack ");}
{d_comma}         {fprintf(fout, "d_comma ");}
{d_colon}         {fprintf(fout, "d_colon ");}
{d_semicolon}     {fprintf(fout, "d_semicolon ");}
{d_ws}            {fprintf(fout, "%s", yytext);}
{id}              {fprintf(fout, "id ");}
{comm}            {fprintf(fout, "comm ");}

%%

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		FILE *fin = fopen(argv[1], "r");
		if (fin)
			yyin = fin;

      char sOutFileName[100];
      strcat(sOutFileName, argv[1]);
      strcat(sOutFileName, ".out");
      fout = fopen(sOutFileName, "w");
		if (!fout)
			return EXIT_FAILURE;
	}
	yylex();
	return EXIT_SUCCESS;
}