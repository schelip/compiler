yacc -d --verbose parser.y
lex lexer.l
gcc lex.yy.c y.tab.c symbol.c -o compiler
./compiler < test.src