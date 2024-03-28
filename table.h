#ifndef SYMBOL_H
#define SYMBOL_H

#define SIZE 109

typedef struct bucket *Bucket;
typedef Bucket *SymbolTable;
typedef struct scope *Scope;

typedef enum
{
  global,
  function,
  block
} ScopeKind;

struct bucket
{
  char *key;
  void *binding;
  Bucket next;
};

struct scope {
  ScopeKind kind;
  SymbolTable table;
  Scope parent;
};

Bucket create_bucket(char *key, void *binding, Bucket next);
SymbolTable create_empty_table();
void destroy_table(SymbolTable table);
void insert(Scope scope, char *key, void *binding);
void *lookup(Scope scope, char *key);
void *full_lookup(Scope scope, char *key);
Scope create_scope(Scope parent, ScopeKind kind);
void destroy_scope(Scope *scope);
void print_full_table(Scope scope);

#endif /* SYMBOL_H */
