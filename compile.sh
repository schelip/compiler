yacc -d syntax.y
lex lexical.l
gcc lex.yy.c y.tab.c -o compiler
./compiler