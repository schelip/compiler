#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef enum
{
  d_void,
  d_int,
  d_float,
  d_char,
  d_string,
  d_bool,
} data_type;

extern const char *data_type_names[];

typedef enum
{
  s_literal,
  s_variable,
  s_function,
} symbol_type;

extern const char *symbol_type_names[];

typedef struct {
  char name[40];
  data_type d_type;
  symbol_type s_type;
  int lineno;
} symbol;

extern symbol *symbol_table[50];
extern symbol *next_symbol;

extern int symbol_count;

extern void allocate_symbol();
extern int search_symbol(char *name);
extern void add_symbol(symbol_type type);
extern void print_symbol_table();

#endif