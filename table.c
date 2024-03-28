#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "syntax.h"

FILE *semout;

static unsigned int hash(char *s0)
{
  unsigned int h = 0;
  char *s;
  for (s = s0; *s; s++)
    h = h * 65599 + *s;
  return h;
}

Bucket create_bucket(char *key, void *binding, Bucket next) {
  Bucket bucket = malloc(sizeof *bucket);
  if (bucket == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  bucket->key = key;
  bucket->binding = binding;
  bucket->next = next;
  return bucket;
}

SymbolTable create_table() {
  int size = sizeof(Bucket) * SIZE;
  SymbolTable table = malloc(size);
  memset(table, 0, size);
  return table;
}

void destroy_table(SymbolTable table) {
  free(table);
}

void insert(Scope scope, char *key, void *binding) {
  SymbolTable table = scope->table;
  int index = hash(key) % SIZE;
  table[index] = create_bucket(key, binding, table[index]);
  fprintf(semout, "inserted %s key at index %d\n", key, index);
  print_full_table(scope);
}

void *lookup(Scope scope, char *key) {
  SymbolTable table = scope->table;
  int index = hash(key) % SIZE;
  fprintf(semout, "looking up key %s with index %d at scope of kind %d\n", key, index, scope->kind);
  print_full_table(scope);
  Bucket bucket;
  for (bucket = table[index]; bucket; bucket = bucket->next) {
    if (strcmp(bucket->key, key) == 0) {
      fprintf(semout, "found bucket with key %s\n", key);
      return bucket->binding;
    }
  }
  return NULL;
}

void *full_lookup(Scope scope, char *key) {
  while (NULL != scope) {
    void *result = (void *)lookup(scope, key);
    if (result != NULL) {
      return result;
    }
    scope = scope->parent;
  }
  fprintf(semout, "did not find key %s at any scope\n", key);
  return NULL;
}

void pop(SymbolTable table, char *key) {
  int index = hash(key) % SIZE;
  table[index] = table[index]->next;
}

Scope create_scope(Scope parent, ScopeKind kind) {
  Scope scope = malloc(sizeof(*scope));
  scope->kind = kind;
  scope->table = create_table();
  scope->parent = parent;
  return scope;
}

void destroy_scope(Scope *scope) {
  free(*scope);
  scope = NULL;
}

void print_full_table(Scope scope) {
  SymbolTable table = scope->table;
  switch (scope->kind)
  {
  case global: fprintf(semout, "\nGlobal scope\n"); break;
  case function: fprintf(semout, "\nFunction scope\n"); break;
  case block: fprintf(semout, "\nBlock scope\n"); break;
  default: break;
  }
  fprintf(semout, "|-------------------------------\n");
  for (int i = 0; i < SIZE; i++)
  {
    Bucket bucket = table[i];
    if (bucket != NULL) {
      fprintf(semout, "[%d]: ", i);
      for (; bucket != NULL; bucket = bucket->next) {
        fprintf(semout, "%s ->", bucket->key);
      }
      fprintf(semout, " -/\n");
    }
  }
  fprintf(semout, "|-------------------------------\n");

  if (scope->parent != NULL)
    print_full_table(scope->parent);
  else
    fprintf(semout, "\n");
}
