#include <stdio.h>
#include <stdlib.h>

#include "syntax.h"
#include "semanthic.h"
#include "parser.tab.h"

extern FILE *yyout, *astout, *semout;
extern NodeProgram program;

int main(int argc, char **argv) {
  yyout = fopen("lex.out","w");
  astout = fopen("ast.out", "w");
  semout = fopen("sem.out", "w");
  yyparse();
  fflush(yyout);
  print_program(program, 0);
  fflush(astout);
  check_prog(program);
  fflush(semout);
}
