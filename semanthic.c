#include <stdio.h>
#include <stdlib.h>
#include "syntax.h"
#include "table.h"
#include "semanthic.h"

extern FILE *semout;

NodeType TypeInt;
NodeType TypeFloat;
NodeType TypeChar;
NodeType TypeString;
NodeType TypeBool;

Scope current_scope;

static void semant_error(char *msg, int lineno);
static int type_diff(NodeType t1, NodeType t2);
static int numeric(NodeType type);
static int type_equals(NodeType t1, NodeType t2);
static NodeType type_var(char *var_id);
static NodeType type_func(char *func_id);
static NodeType type_lit(NodeLiteral lit);
static NodeType type_expr(NodeExpression expr);
static NodeType type_simple_expr(NodeSimpleExpression expr);
static NodeType type_term(NodeTerm term);
static NodeType type_factor(NodeFactor factor);

void check_prog(NodeProgram prog) {
  fprintf(semout, "void check_prog(NodeProgram prog) {\n");
  TypeInt = create_primitive_type_specifier(type_int, 0);
  TypeFloat = create_primitive_type_specifier(type_float, 0);
  TypeChar = create_primitive_type_specifier(type_char, 0);
  TypeString = create_primitive_type_specifier(type_string, 0);
  TypeBool = create_primitive_type_specifier(type_bool, 0);

  current_scope = create_scope(NULL, global);
  check_var_decl_list(prog->var_decl_list);
  check_func_decl_list(prog->func_decl_list);
  check_stmt_block(prog->main_stmt_block);
  destroy_scope(&current_scope);

  fprintf(semout, "prog ok\n");
}

void check_var_decl_list(NodeVarDeclList var_decl_list) {
  fprintf(semout, "void check_var_decl_list(NodeVarDeclList var_decl_list) {\n");
  while (var_decl_list != NULL) {
    check_var_decl(var_decl_list->var_decl);
    var_decl_list = var_decl_list->tail;
  }
  fprintf(semout, "var_decl_list ok\n");
}

void check_func_decl_list(NodeFuncDeclList func_decl_list) {
  fprintf(semout, "void check_func_decl_list(NodeFuncDeclList func_decl_list) {\n");
  while (func_decl_list != NULL) {
    fprintf(semout, "Checking next func\n");
    check_func_decl(func_decl_list->func_decl);
    func_decl_list = func_decl_list->tail;
  }
  fprintf(semout, "func_decl_list ok\n");
}

void check_func_decl(NodeFuncDecl func_decl) {
  fprintf(semout, "void check_func_decl(NodeFuncDecl func_decl) {\n");
  char *key = func_decl->func_header->func_identifier;

  NodeFuncDecl decl = (NodeFuncDecl) lookup(current_scope, key);
  if (decl != NULL) {
    semant_error("Function redeclaration", decl->lineno);
  }

  insert(current_scope, key, func_decl);

  current_scope = create_scope(current_scope, function);
  fprintf(semout, "created function scope with parent %d\n", current_scope->parent->kind);

  NodeFuncParamList curr = func_decl->func_header->func_param_list;
  while (curr != NULL) {
    check_func_param(func_decl->func_header->func_param_list->param);
    curr = curr->tail;
  }

  check_var_decl_list(func_decl->func_stmt_block->block_var_decl_list);
  check_stmt_list(func_decl->func_stmt_block->stmt_list);

  NodeType ret_type = func_decl->func_header->func_return_type;

  for (NodeStmtList stmt = func_decl->func_stmt_block->stmt_list;
       stmt != NULL; stmt = stmt->tail) {
    if (stmt->stmt->kind == kind_ret_stmt) {
      if (ret_type == NULL)
        semant_error("Return statement on void type function", stmt->lineno);
      else if (type_diff(type_expr(stmt->stmt->return_expr),ret_type))
        semant_error("Return statement of wrong type", stmt->lineno);
    }
  }

  Scope parent_scope = current_scope->parent;
  destroy_scope(&current_scope);
  current_scope = parent_scope;
  fprintf(semout, "destroyed function scope");
  fprintf(semout, "func_decl ok\n");
}

void check_func_param(NodeFuncParam func_param) {
  fprintf(semout, "void check_func_param(NodeFuncParam func_param) {\n");
  NodeVarIdList curr = func_param->param_id_list;
  do {
    check_var(curr->var_id, func_param->param_type);
    curr = curr->tail;
  } while (curr != NULL);
  fprintf(semout, "func_param ok\n");
}

void check_stmt_block(NodeStmtBlock stmt_block) {
  fprintf(semout, "void check_stmt_block(NodeStmtBlock stmt_block) {\n");
  current_scope = create_scope(current_scope, block);
  fprintf(semout, "created block scope with parent %d\n", current_scope->parent->kind);

  check_var_decl_list(stmt_block->block_var_decl_list);
  check_stmt_list(stmt_block->stmt_list);

  Scope parent_scope = current_scope->parent;
  destroy_scope(&current_scope);
  current_scope = parent_scope;
  fprintf(semout, "destroyed block scope");
  fprintf(semout, "stmt_block ok\n");
}

void check_var_decl(NodeVarDecl var_decl) {
  fprintf(semout, "void check_var_decl(NodeVarDecl var_decl) {\n");
  NodeVarIdList curr = var_decl->var_id_list;
  do {
    check_var(curr->var_id, var_decl->type_specifier);
    curr = curr->tail;
  } while (curr != NULL);
  fprintf(semout, "var_decl ok\n");
}

void check_var(NodeVarId var_id, NodeType type) {
  fprintf(semout, "void check_var(NodeVarId var_id, NodeType type) {\n");
  char *key = var_id->var_id;
  NodeVar decl = (NodeVar) lookup(current_scope, key);
  if (decl != NULL) {
    semant_error("Variable redeclaration", decl->lineno);
  }

  NodeVar var = create_var(var_id, type, NULL, var_id->lineno);
  insert(current_scope, key, var);
  fprintf(semout, "var ok\n");
}

void check_stmt_list(NodeStmtList stmt_list) {
  fprintf(semout, "void check_stmt_list(NodeStmtList stmt_list) {\n");
  NodeStmtList curr = stmt_list;
  do {
    check_stmt(curr->stmt);
    curr = curr->tail;
  } while (curr != NULL);
  fprintf(semout, "stmt_list ok\n");
}

void check_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_stmt(NodeStmt stmt) {\n");
  switch (stmt->kind)
  {
  case kind_attribution_stmt: check_atrribution_stmt(stmt); break;
  case kind_func_call_stmt: check_func_call(stmt->func_call_stmt.call); break;
  case kind_comparison_ifx_stmt: check_comparison_ifx_stmt(stmt); break;
  case kind_comparison_ifelse_stmt: check_comparison_ifelse_stmt(stmt); break;
  case kind_iteration_stmt: check_iteration_stmt(stmt); break;
  case kind_ret_stmt: check_ret_stmt(stmt); break;
  case kind_block_stmt: check_stmt_block(stmt->block); break;
  default: semant_error("Unexpected statement kind", stmt->lineno); break;
  }
  fprintf(semout, "stmt ok\n");
}

void check_atrribution_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_atrribution_stmt(NodeStmt stmt) {\n");
  check_var_access(stmt->attribution_stmt.var_access);
  check_expr(stmt->attribution_stmt.right);
  NodeType var_type = type_var(stmt->attribution_stmt.var_access->var_id);
  fprintf(semout, "var type: %d\n", var_type->array_type.data_type);
  NodeType expr_type = type_expr(stmt->attribution_stmt.right);
  fprintf(semout, "expr type: %d\n", expr_type->primitive_type);
  if (stmt->attribution_stmt.var_access->kind == kind_array_access) {
    if (var_type->array_type.data_type != expr_type->primitive_type)
      semant_error("Attribution of wrong type", stmt->lineno);
  }
  else if (type_diff(var_type, expr_type))
    semant_error("Attribution of wrong type", stmt->lineno);
  fprintf(semout, "attribution_stmt ok\n");
}

void check_func_call(NodeFuncCall func_call) {
  fprintf(semout, "void check_func_call(NodeFuncCall func_call) {\n");
  char *key = func_call->func_id;
  NodeFuncDecl func_decl = (NodeFuncDecl) full_lookup(current_scope, key);
  if (func_decl == NULL)
    semant_error("Function not declared", func_call->lineno);
  NodeArgList call_args = func_call->arg_list;
  NodeFuncParamList func_params = func_decl->func_header->func_param_list;
  NodeVarIdList param_id_list;
  if (func_params != NULL)
    param_id_list = func_params->param->param_id_list;
  while (call_args != NULL) {
    if (func_params == NULL)
      semant_error("Too many arguments passed on function call", func_call->lineno);
    check_expr(call_args->arg);
    if (type_diff(type_expr(call_args->arg), func_params->param->param_type))
      semant_error("Argument of wrong type passed on function call", func_call->lineno);
    call_args = call_args->tail;
    param_id_list = param_id_list->tail;
    if (param_id_list == NULL) {
      func_params = func_params->tail;
      if (func_params != NULL)
        param_id_list = func_params->param->param_id_list;
    }
  }
  if (func_params != NULL)
    semant_error("Too few arguments passed on function call", func_call->lineno);
  fprintf(semout, "func_call ok\n");
}

void check_comparison_ifx_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_comparison_ifx_stmt(NodeStmt stmt) {\n");
  if (type_diff(type_expr(stmt->comparison_ifx_stmt.cond), TypeBool))
    semant_error("If condition must be an expression of boolean type", stmt->lineno);
  check_stmt(stmt->comparison_ifx_stmt.body);
  fprintf(semout, "comparison_ifx_stmt ok\n");
}

void check_comparison_ifelse_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_comparison_ifelse_stmt(NodeStmt stmt) {\n");
  if (type_diff(type_expr(stmt->comparison_ifelse_stmt.cond), TypeBool))
    semant_error("If condition must be an expression of boolean type", stmt->lineno);
  check_stmt(stmt->comparison_ifelse_stmt.if_body);
  check_stmt(stmt->comparison_ifelse_stmt.else_body);
  fprintf(semout, "comparison_ifelse_stmt ok\n");
}

void check_iteration_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_iteration_stmt(NodeStmt stmt) {\n");
  if (type_diff(type_expr(stmt->iteration_stmt.cond), TypeBool))
    semant_error("While condition must be an expression of boolean type", stmt->lineno);
  check_stmt(stmt->iteration_stmt.body);
  fprintf(semout, "iteration_stmt ok\n");
}

void check_ret_stmt(NodeStmt stmt) {
  fprintf(semout, "void check_ret_stmt(NodeStmt stmt) {\n");
  check_expr(stmt->return_expr);
  Scope scope = current_scope;
  while (scope->kind != global) {
    if (scope->kind == function)
      return;
    scope = scope->parent;
  }
  semant_error("Unexpected return outside of function definition", stmt->lineno);
  fprintf(semout, "ret_stmt ok\n");
}

void check_expr(NodeExpression expr) {
  fprintf(semout, "void check_expr(NodeExpression expr) {\n");
  if (expr->kind == kind_simple_expr)
    check_simple_expr(expr->simple_expr);
  else {
    NodeType lType = type_simple_expr(expr->relational_expr.left);
    NodeType rType = type_simple_expr(expr->relational_expr.right);
    if (!numeric(lType) && !numeric(rType)) {
      if (expr->relational_expr.op == op_eq && expr->relational_expr.op == op_ne) {
        if (type_diff(lType, rType)) {
          semant_error("Incompatible types being compared", expr->lineno);
        }
      } else {
        semant_error("Non-numeric types being compared", expr->lineno);
      }
    }
  }
  fprintf(semout, "expr ok\n");
}

void check_simple_expr(NodeSimpleExpression expr) {
  fprintf(semout, "void check_simple_expr(NodeSimpleExpression expr) {\n");
  if (expr->kind == kind_term_simple_expr)
    check_term(expr->term);
  else if (expr->kind == kind_sign_simple_expr) {
    NodeType type = type_term(expr->sign_simple_expr.term);
    if (!numeric(type))
      semant_error("Sign operator used on non-numeric type", expr->lineno);
  }
  else {
    NodeType lType = type_simple_expr(expr->additive_expr.left);
    NodeType rType = type_term(expr->additive_expr.right);
    if (expr->additive_expr.op == op_or && (type_diff(lType, TypeBool) || type_diff(rType, TypeBool)))
      semant_error("Boolean operator used on non-boolean type", expr->lineno);
    if (!numeric(lType) || !numeric(rType))
      semant_error("Arithmetic operator used on non-numeric type", expr->lineno);
  }
  fprintf(semout, "simple_expr ok\n");
}

void check_term(NodeTerm term) {
  fprintf(semout, "void check_term(NodeTerm term) {\n");
  if (term->kind == kind_factor_term)
    check_factor(term->factor);
  else {
    NodeType lType = type_term(term->multiplicative_expr.left);
    NodeType rType = type_factor(term->multiplicative_expr.right);
    if (term->multiplicative_expr.op == op_and && (type_diff(lType, TypeBool) || type_diff(rType, TypeBool)))
      semant_error("Boolean operator used on non-boolean type", term->lineno);
    if (!numeric(lType) || !numeric(rType))
      semant_error("Arithmetic operator used on non-numeric type", term->lineno);
  }
  fprintf(semout, "term ok\n");
}

void check_factor(NodeFactor factor) {
  fprintf(semout, "void check_factor(NodeFactor factor) {\n");
  switch (factor->kind)
  {
  case kind_var_access: check_var_access(factor->var_access); break;
  case kind_func_call: check_func_call(factor->func_call); break;
  case kind_parenthesized_expr: check_expr(factor->expression); break;
  case kind_literal: break;
  case kind_not_factor: check_not_factor(factor->not_factor); break;
  default: semant_error("Unexpected factor in expression", factor->lineno); break;
  }
  fprintf(semout, "factor ok\n");
}

void check_var_access(NodeVarAccess var_access) {
  fprintf(semout, "void check_var_access(NodeVarAccess var_access) {\n");
  fprintf(semout, "current scope = %d\n", current_scope->kind);
  char *key;
  if (var_access->kind == kind_simple_var_access)
    key = var_access->var_id;
  else
    key = var_access->array_access.arr_id;
  NodeVar decl = (NodeVar) full_lookup(current_scope, key);
  if (decl == NULL)
    semant_error("Undeclared variable access", var_access->lineno);
  if (var_access->kind == kind_array_access) {
    check_expr(var_access->array_access.idx);
    if (type_diff(type_expr(var_access->array_access.idx), TypeInt))
      semant_error("Array index must be an integer", var_access->lineno);
  }
  fprintf(semout, "var_access ok\n");
  return;
}

void check_not_factor(NodeFactor factor) {
  fprintf(semout, "void check_not_factor(NodeFactor factor) {\n");
  if (!type_diff(type_factor(factor), TypeBool))
    semant_error("Boolean operator used on non-boolean factor", factor->lineno);
  fprintf(semout, "not_factor ok\n");
}

static void semant_error(char *msg, int lineno) {
  fprintf(stderr, "Semanthic Error: %s at line %d\n", msg, lineno);
  exit(EXIT_FAILURE);
}

static int type_diff(NodeType t1, NodeType t2) {
  if (t1->kind != t2->kind)
    return 1;
  if (t1->kind == kind_primitive)
    return t1->primitive_type != t2->primitive_type;
  else
    return t1->array_type.data_type != t2->array_type.data_type
      || t1->array_type.size != t2->array_type.size;
}

static int numeric(NodeType type) {
  return !type_diff(type, TypeInt) || !type_diff(type, TypeFloat);
}

static int type_equals(NodeType t1, NodeType t2) {
  return !type_diff(t1, t2);
}

static NodeType type_var(char *var_id) {
  NodeVar decl = (NodeVar)full_lookup(current_scope, var_id);
  if (decl != NULL) {
    return decl->var_type;
  }
  return NULL;
}

static NodeType type_func(char *func_id) {
  NodeFuncDecl decl = (NodeFuncDecl) full_lookup(current_scope, func_id);
  if (decl != NULL) {
    return decl->func_header->func_return_type;
  }
  return NULL;
}

static NodeType type_lit(NodeLiteral lit) {
  switch (lit->kind)
  {
  case kind_lit_integer: return TypeInt;
  case kind_lit_float: return TypeFloat;
  case kind_lit_char: return TypeChar;
  case kind_lit_string: return TypeString;
  case kind_lit_boolean: return TypeBool;
  default: semant_error("Unexpected literal type", lit->lineno);
  }
  return NULL;
}

static NodeType type_expr(NodeExpression expr) {
  if (expr->kind == kind_simple_expr)
    return type_simple_expr(expr->simple_expr);
  else
    return TypeBool;
}

static NodeType type_simple_expr(NodeSimpleExpression expr) {
  if (expr->kind == kind_term_simple_expr)
    return type_term(expr->term);
  else if (expr->kind == kind_sign_simple_expr)
    return type_term(expr->sign_simple_expr.term);
  else if (expr->additive_expr.op == op_or)
      return TypeBool;
  else if (type_equals(type_simple_expr(expr->additive_expr.left), TypeFloat)
    || type_equals(type_term(expr->additive_expr.right), TypeFloat))
      return TypeFloat;
  else
    return TypeInt;
}

static NodeType type_term(NodeTerm term) {
  if (term->kind == kind_factor_term)
    return type_factor(term->factor);
  else if (term->multiplicative_expr.op == op_and)
    return TypeBool;
  else if (type_equals(type_term(term->multiplicative_expr.left), TypeFloat)
    || type_equals(type_factor(term->multiplicative_expr.right), TypeFloat))
    return TypeFloat;
  else
    return TypeInt;
}

static NodeType type_factor(NodeFactor factor) {
  switch (factor->kind)
  {
  case kind_var_access: return type_var(factor->var_access->var_id); break;
  case kind_func_call: return type_func(factor->func_call->func_id); break;
  case kind_parenthesized_expr: return type_expr(factor->expression); break;
  case kind_literal: return type_lit(factor->literal);
  case kind_not_factor: return TypeBool;
  default: semant_error("Unexpected factor in expression", factor->lineno);
  }
  return NULL;
}
