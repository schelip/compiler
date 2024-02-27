#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

extern int yylineno;
extern FILE *yyout;
extern void yyerror(const char *);

symbol *symbol_table[50];
symbol *next_symbol;
int symbol_count = 0;

const char *data_type_names[] = {
    "void",
    "int",
    "float",
    "char",
    "string",
    "bool"};

const char *symbol_type_names[] = {
    "literal",
    "variable",
    "function"};

void allocate_symbol()
{
  if ((next_symbol = malloc(sizeof(symbol))) == 0)
    yyerror("Out of memory");
}

int search_symbol(char *name)
{
  int i;
  for (i = symbol_count - 1; i >= 0; --i)
    if (strcmp(symbol_table[i]->name, name)==0)
      return i;
  return -1;
}

void add_symbol(symbol_type type)
{
  if (search_symbol(next_symbol->name) != -1)
    return;

  next_symbol->s_type = type;
  next_symbol->lineno = yylineno;

  printf("\nAdding symbol:\n\tName: %s\n\tData Type: %s\n\tSymbol Type: %s\n\tLine: %d\n",
         next_symbol->name, data_type_names[next_symbol->d_type],
         symbol_type_names[next_symbol->s_type], next_symbol->lineno);

  symbol_table[symbol_count++] = next_symbol;

  allocate_symbol();
}

void print_symbol_table()
{
  if (!symbol_count)
    return;

  int i;
  symbol *s;

  fprintf(yyout, "\n%-40.40s | %-10.10s | %-10.10s | %-10.10s\n", "SYMBOL", "DATA_TYPE", "SYMBOL_TYPE", "LINENO");
  fprintf(yyout, "--------------------------------------------------------------------------------\n");

  for (i = 0; i < symbol_count; i++)
  {
    s = symbol_table[i];
    fprintf(yyout, "%-40.40s | %-10.10s | %-10.10s | %-d\n", s->name, data_type_names[s->d_type], symbol_type_names[s->s_type], s->lineno);
  }
}
