bison -d --verbose parser.y
lex -l lexer.l
gcc -Wall -g main.c lex.yy.c parser.tab.c syntax.c table.c semanthic.c -o compiler
./compiler < test.src