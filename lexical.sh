lex lexical.l
gcc lex.yy.c -o lexical
./lexical test.src