bison -d --verbose parser.y
flex lexer.l
gcc lex.yy.c parser.tab.c ast.c -o compiler
./compiler < test.src