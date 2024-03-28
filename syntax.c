#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// Node creating functions //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


NodeProgram create_program(NodeVarDeclList var_decl_list, NodeFuncDeclList func_decl_list, NodeStmtBlock main_stmt_block, int lineno) {
  if (main_stmt_block == NULL) {
    fprintf(stderr, "Error: no main statement block found\n");
    exit(EXIT_FAILURE);
  }
  NodeProgram node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_decl_list = var_decl_list;
  node->func_decl_list = func_decl_list;
  node->main_stmt_block = main_stmt_block;
  node->lineno = lineno;
  return node;
}

NodeVarDeclList create_var_decl_list(NodeVarDecl var_decl, NodeVarDeclList tail, int lineno) {
  NodeVarDeclList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_decl = var_decl;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeVarDecl create_var_decl(NodeVarIdList var_id_list, NodeType type_specifier, int lineno) {
  NodeVarDecl node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id_list = var_id_list;
  node->type_specifier = type_specifier;
  node->lineno = lineno;
  return node;
}

NodeVarIdList create_var_id_list(NodeVarId var_id, NodeVarIdList tail, int lineno) {
  NodeVarIdList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id = var_id;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeVarId create_var_id(char *var_id, int lineno) {
  NodeVarId node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id = var_id;
  node->lineno = lineno;
  return node;
}

NodeVar create_var(NodeVarId var_id, NodeType var_type, NodeLiteral value, int lineno) {
  NodeVar node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id = var_id;
  node->var_type = var_type;
  node->var_value = value;
  node->lineno = lineno;
  return node;
}

NodeType create_primitive_type_specifier(DataType data_type, int lineno) {
  NodeType node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_primitive;
  node->primitive_type = data_type;
  node->lineno = lineno;
  return node;
}

NodeType create_array_type_specifier(DataType data_type, int size, int lineno) {
  NodeType node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_array;
  node->array_type.data_type = data_type;
  node->array_type.size = size;
  node->lineno = lineno;
  return node;
}

NodeFuncDeclList create_func_decl_list(NodeFuncDecl func_decl, NodeFuncDeclList tail, int lineno) {
  NodeFuncDeclList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_decl = func_decl;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeFuncDecl create_func_decl(NodeFuncHeader func_header, NodeStmtBlock func_stmt_block, int lineno) {
  NodeFuncDecl node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_header = func_header;
  node->func_stmt_block = func_stmt_block;
  node->lineno = lineno;
  return node;
}

NodeFuncHeader create_func_header(char *func_identifier, NodeFuncParamList func_param_list, NodeType func_return_type, int lineno) {
  NodeFuncHeader node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_identifier = func_identifier;
  node->func_param_list = func_param_list;
  node->func_return_type = func_return_type;
  node->lineno = lineno;
  return node;
}

NodeFuncParamList create_func_param_list(NodeFuncParam param, NodeFuncParamList tail, int lineno) {
  NodeFuncParamList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->param = param;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeFuncParam create_func_param(NodeVarIdList param_id_list, NodeType param_type, int lineno) {
  NodeFuncParam node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->param_id_list = param_id_list;
  node->param_type = param_type;
  node->lineno = lineno;
  return node;
}

NodeStmtBlock create_stmt_block(NodeVarDeclList block_var_decl_list, NodeStmtList stmt_list, int lineno) {
  NodeStmtBlock node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->block_var_decl_list = block_var_decl_list;
  node->stmt_list = stmt_list;
  node->lineno = lineno;
  return node;
}

NodeStmtList create_stmt_list(NodeStmt stmt, NodeStmtList tail, int lineno) {
  NodeStmtList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->stmt = stmt;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeStmt create_attribution_stmt(NodeVarAccess var_access, NodeExpression right, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_attribution_stmt;
  node->attribution_stmt.var_access = var_access;
  node->attribution_stmt.right = right;
  node->lineno = lineno;
  return node;
}

NodeStmt create_func_call_stmt(NodeFuncCall call, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_func_call_stmt;
  node->func_call_stmt.call = call;
  node->lineno = lineno;
  return node;
}

NodeStmt create_ifx_stmt(NodeExpression cond, NodeStmt body, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_comparison_ifx_stmt;
  node->comparison_ifx_stmt.cond = cond;
  node->comparison_ifx_stmt.body = body;
  node->lineno = lineno;
  return node;
}

NodeStmt create_ifelse_stmt(NodeExpression cond, NodeStmt if_body, NodeStmt else_body, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_comparison_ifelse_stmt;
  node->comparison_ifelse_stmt.cond = cond;
  node->comparison_ifelse_stmt.if_body = if_body;
  node->comparison_ifelse_stmt.else_body = else_body;
  node->lineno = lineno;
  return node;
}

NodeStmt create_iteration_stmt(NodeExpression cond, NodeStmt body, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_iteration_stmt;
  node->iteration_stmt.cond = cond;
  node->iteration_stmt.body = body;
  node->lineno = lineno;
  return node;
}

NodeStmt create_return_stmt(NodeExpression expr, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_ret_stmt;
  node->return_expr = expr;
  node->lineno = lineno;
  return node;
}

NodeStmt create_block_stmt(NodeStmtBlock block, int lineno) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_block_stmt;
  node->block = block;
  node->lineno = lineno;
  return node;
}

NodeVarAccess create_simple_var_access(char *var_id, int lineno) {
  NodeVarAccess node = malloc(sizeof(*node));

  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_simple_var_access;
  node->var_id = var_id;
  node->lineno = lineno;
  return node;
}

NodeVarAccess create_array_access(char *arr_id, NodeExpression idx, int lineno) {
  NodeVarAccess node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_array_access;
  node->array_access.arr_id = arr_id;
  node->array_access.idx = idx;
  node->lineno = lineno;
  return node;
}

NodeFuncCall create_func_call(char *func_id, NodeArgList arg_list, int lineno) {
  NodeFuncCall node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_id = func_id;
  node->arg_list = arg_list;
  node->lineno = lineno;
  return node;
}

NodeArgList create_arg_list(NodeExpression arg, NodeArgList tail, int lineno) {
  NodeArgList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->arg = arg;
  node->tail = tail;
  node->lineno = lineno;
  return node;
}

NodeExpression create_simple_expr_expression(NodeSimpleExpression simple_expr, int lineno) {
  NodeExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_simple_expr;
  node->simple_expr = simple_expr;
  node->lineno = lineno;
  return node;
}

NodeExpression create_relational_expr_expression(NodeSimpleExpression left, RelationalOperator op, NodeSimpleExpression right, int lineno) {
  NodeExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_relational_expr;
  node->relational_expr.left = left;
  node->relational_expr.op = op;
  node->relational_expr.right = right;
  node->lineno = lineno;
  return node;
}

NodeSimpleExpression create_term_simple_expr(NodeTerm term, int lineno) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_term_simple_expr;
  node->term = term;
  node->lineno = lineno;
  return node;
}

NodeSimpleExpression create_sign_simple_expr(SignOperator op, NodeTerm term, int lineno) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_sign_simple_expr;
  node->sign_simple_expr.op = op;
  node->sign_simple_expr.term = term;
  node->lineno = lineno;
  return node;
}

NodeSimpleExpression create_additive_simple_expr(NodeSimpleExpression left, AdditiveOperator op, NodeTerm right, int lineno) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_additive_simple_expr;
  node->additive_expr.left = left;
  node->additive_expr.op = op;
  node->additive_expr.right = right;
  node->lineno = lineno;
  return node;
}

NodeTerm create_factor_term(NodeFactor factor, int lineno) {
  NodeTerm node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_factor_term;
  node->factor = factor;
  node->lineno = lineno;
  return node;
}

NodeTerm create_multiplicative_term(NodeTerm left, MultiplicativeOperator op, NodeFactor right, int lineno) {
  NodeTerm node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_multiplicative_expr_term;
  node->multiplicative_expr.left = left;
  node->multiplicative_expr.op = op;
  node->multiplicative_expr.right = right;
  node->lineno = lineno;
  return node;
}

NodeFactor create_var_access_factor(NodeVarAccess var_access, int lineno) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_var_access;
  node->var_access = var_access;
  node->lineno = lineno;
  return node;
}

NodeFactor create_func_call_factor(NodeFuncCall func_call, int lineno) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_func_call;
  node->func_call = func_call;
  node->lineno = lineno;
  return node;
}

NodeFactor create_parenthesized_expr_factor(NodeExpression expression, int lineno) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_parenthesized_expr;
  node->expression = expression;
  node->lineno = lineno;
  return node;
}

NodeFactor create_literal_factor(NodeLiteral literal, int lineno) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_literal;
  node->literal = literal;
  node->lineno = lineno;
  return node;
}

NodeFactor create_not_factor(NodeFactor not_factor, int lineno) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_not_factor;
  node->not_factor = not_factor;
  node->lineno = lineno;
  return node;
}

NodeLiteral create_int_literal(int value, int lineno) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_integer;
  node->i_value = value;
  node->lineno = lineno;
  return node;
}

NodeLiteral create_float_literal(float value, int lineno) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_float;
  node->f_value = value;
  node->lineno = lineno;
  return node;
}

NodeLiteral create_char_literal(char value, int lineno) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_char;
  node->c_value = value;
  node->lineno = lineno;
  return node;
}

NodeLiteral create_string_literal(char *value, int lineno) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_string;
  node->s_value = strdup(value);
  if (node->s_value == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->lineno = lineno;
  return node;
}

NodeLiteral create_bool_literal(int value, int lineno) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_boolean;
  node->b_value = value;
  node->lineno = lineno;
  return node;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Node Printing Procedures /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

FILE *astout;

void print_indent(int level) {
  for (int i = 0; i < level; i++)
    fprintf(astout, "|  ");
  fprintf(astout, "+-");
}

void print_int(int value, int level) {
  print_indent(level);
  fprintf(astout, " %d\n", value);
}

void print_float(float value, int level) {
  print_indent(level);
  fprintf(astout, " %f\n", value);
}

void print_char(char value, int level) {
  print_indent(level);
  fprintf(astout, " %c\n", value);
}

void print_string(char *value, int level) {
  print_indent(level);
  fprintf(astout, "%s\n", value);
}

void print_bool(int value, int level) {
  print_indent(level);
  if (value)
    fprintf(astout, " true\n");
  else
    fprintf(astout, " false\n");
}

void print_data_type(DataType data_type, int level) {
  print_indent(level);
  switch (data_type) {
    case type_int:
      fprintf(astout, "type_int\n");
      break;
    case type_float:
      fprintf(astout, "type_float\n");
      break;
    case type_char:
      fprintf(astout, "type_char\n");
      break;
    case type_string:
      fprintf(astout, "type_string\n");
      break;
    case type_bool:
      fprintf(astout, "type_bool\n");
      break;
    default:
      fprintf(astout, "unknown_data_type\n");
      break;
  }
}

void print_sign_op(SignOperator op, int level) {
  print_indent(level);
  switch (op) {
    case op_uplus:
      fprintf(astout, "op_uplus\n");
      break;
    case op_uminus:
      fprintf(astout, "op_uminus\n");
      break;
    default:
      fprintf(astout, "unknown_sign_op\n");
      break;
  }
}

void print_relation_op(RelationalOperator op, int level) {
  print_indent(level);
  switch (op) {
    case op_eq:
      fprintf(astout, "op_eq\n");
      break;
    case op_ne:
      fprintf(astout, "op_ne\n");
      break;
    case op_gt:
      fprintf(astout, "op_gt\n");
      break;
    case op_ge:
      fprintf(astout, "op_ge\n");
      break;
    case op_lt:
      fprintf(astout, "op_lt\n");
      break;
    case op_le:
      fprintf(astout, "op_le\n");
      break;
    default:
      fprintf(astout, "unknown_relation_op\n");
      break;
  }
}

void print_additive_op(AdditiveOperator op, int level) {
  print_indent(level);
  switch (op) {
    case op_plus:
      fprintf(astout, "op_plus\n");
      break;
    case op_minus:
      fprintf(astout, "op_minus\n");
      break;
    case op_or:
      fprintf(astout, "op_or\n");
      break;
    default:
      fprintf(astout, "unknown_additive_op\n");
      break;
  }
}

void print_multiplicative_op(MultiplicativeOperator op, int level) {
  print_indent(level);
  switch (op) {
    case op_mul:
      fprintf(astout, "op_mul\n");
      break;
    case op_div:
      fprintf(astout, "op_div\n");
      break;
    case op_mod:
      fprintf(astout, "op_mod\n");
      break;
    case op_and:
      fprintf(astout, "op_and\n");
      break;
    default:
      fprintf(astout, "unknown_multiplicative_op\n");
      break;
  }
}

void print_program(NodeProgram node, int level) {
  print_indent(level);
  fprintf(astout, "program\n");
  print_var_decl_list(node->var_decl_list, level + 1);
  print_func_decl_list(node->func_decl_list, level + 1);
  print_stmt_block(node->main_stmt_block, level + 1);
}

void print_var_decl_list(NodeVarDeclList node, int level) {
  if (node == NULL) {
    return;
  }
  print_var_decl(node->var_decl, level);
  if (node->tail != NULL)
    print_var_decl_list(node->tail, level);
}

void print_var_decl(NodeVarDecl node, int level) {
  print_indent(level);
  fprintf(astout, "var_decl\n");
  print_var_id_list(node->var_id_list, level + 1);
  print_type_specifier(node->type_specifier, level + 1);
}

void print_var_id_list(NodeVarIdList node, int level) {
  if (node == NULL) {
    return;
  }
  print_var(node->var_id, level);
  if (node->tail != NULL)
    print_var_id_list(node->tail, level);
}

void print_var(NodeVarId node, int level) {
  if (node == NULL) {
    return;
  }
  print_indent(level);
  fprintf(astout, "id: %s\n", node->var_id);
}

void print_type_specifier(NodeType node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_primitive:
      fprintf(astout, "primitive_type_specifier\n");
      print_primitive_type_specifier(node, level + 1);
      break;
    case kind_array:
      fprintf(astout, "array_type_specifier\n");
      print_array_type_specifier(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_type_specifier\n");
      break;
  }
}

void print_primitive_type_specifier(NodeType node, int level) {
  print_data_type(node->primitive_type, level);
}

void print_array_type_specifier(NodeType node, int level) {
  print_data_type(node->array_type.data_type, level);
  print_int(node->array_type.size, level);
}

void print_func_decl_list(NodeFuncDeclList node, int level) {
  if (node == NULL) {
    return;
  }
  print_func_decl(node->func_decl, level);
  if (node->tail != NULL)
    print_func_decl_list(node->tail, level);
}

void print_func_decl(NodeFuncDecl node, int level) {
  print_indent(level);
  fprintf(astout, "func_decl\n");
  print_func_header(node->func_header, level + 1);
  print_stmt_block(node->func_stmt_block, level + 1);
}

void print_func_header(NodeFuncHeader node, int level) {
  print_indent(level);
  fprintf(astout, "func_header\n");
  print_indent(level + 1);
  fprintf(astout, "id: %s\n", node->func_identifier);
  print_func_param_list(node->func_param_list, level + 1);
  if (node->func_return_type != NULL)
    print_type_specifier(node->func_return_type, level + 1);
}

void print_func_param_list(NodeFuncParamList node, int level) {
  if (node == NULL) {
    return;
  }
  print_func_param(node->param, level);
  if (node->tail != NULL)
    print_func_param_list(node->tail, level);
}

void print_func_param(NodeFuncParam node, int level) {
  print_indent(level);
  fprintf(astout, "func_param\n");
  print_var_id_list(node->param_id_list, level + 1);
  print_type_specifier(node->param_type, level + 1);
}

void print_stmt_block(NodeStmtBlock node, int level) {
  print_indent(level);
  fprintf(astout, "stmt_block\n");
  print_var_decl_list(node->block_var_decl_list, level + 1);
  print_stmt_list(node->stmt_list, level + 1);
}

void print_stmt_list(NodeStmtList node, int level) {
  if (node == NULL) {
    return;
  }
  print_stmt(node->stmt, level);
  if (node->tail != NULL)
    print_stmt_list(node->tail, level);
}

void print_stmt(NodeStmt node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_attribution_stmt:
      fprintf(astout, "attribution_stmt\n");
      print_attribution_stmt(node, level + 1);
      break;
    case kind_func_call_stmt:
      fprintf(astout, "func_call_stmt\n");
      print_func_call_stmt(node, level + 1);
      break;
    case kind_comparison_ifx_stmt:
      fprintf(astout, "comparison_ifx_stmt\n");
      print_ifx_stmt(node, level + 1);
      break;
    case kind_comparison_ifelse_stmt:
      fprintf(astout, "comparison_ifelse_stmt\n");
      print_ifelse_stmt(node, level + 1);
      break;
    case kind_iteration_stmt:
      fprintf(astout, "iteration_stmt\n");
      print_iteration_stmt(node, level + 1);
      break;
    case kind_ret_stmt:
      fprintf(astout, "ret_stmt\n");
      print_return_stmt(node, level + 1);
      break;
    case kind_block_stmt:
      fprintf(astout, "block_stmt\n");
      print_block_stmt(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_stmt\n");
      break;
  }
}

void print_attribution_stmt(NodeStmt node, int level) {
  print_var_access(node->attribution_stmt.var_access, level);
  print_expression(node->attribution_stmt.right, level);
}

void print_func_call_stmt(NodeStmt node, int level) {
  print_func_call(node->func_call_stmt.call, level);
}

void print_ifx_stmt(NodeStmt node, int level) {
  print_expression(node->comparison_ifx_stmt.cond, level);
  print_stmt(node->comparison_ifx_stmt.body, level);
}

void print_ifelse_stmt(NodeStmt node, int level) {
  print_expression(node->comparison_ifelse_stmt.cond, level);
  print_stmt(node->comparison_ifelse_stmt.if_body, level);
  print_stmt(node->comparison_ifelse_stmt.else_body, level);
}

void print_iteration_stmt(NodeStmt node, int level) {
  print_expression(node->iteration_stmt.cond, level);
  print_stmt(node->iteration_stmt.body, level);
}

void print_return_stmt(NodeStmt node, int level) {
  print_expression(node->return_expr, level);
}

void print_block_stmt(NodeStmt node, int level) {
  print_stmt_block(node->block, level);
}

void print_var_access(NodeVarAccess node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_simple_var_access:
      fprintf(astout, "simple_var_access\n");
      print_simple_var_access(node, level + 1);
      break;
    case kind_array_access:
      fprintf(astout, "array_access\n");
      print_array_access(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_var_access\n");
      break;
  }
}

void print_simple_var_access(NodeVarAccess node, int level) {
  print_indent(level);
  fprintf(astout, "id: %s\n", node->var_id);
}

void print_array_access(NodeVarAccess node, int level) {
  print_expression(node->array_access.idx, level);
}

void print_func_call(NodeFuncCall node, int level) {
  print_indent(level);
  fprintf(astout, "func_call\n");
  print_indent(level + 1);
  fprintf(astout, "id: %s\n", node->func_id);
  print_arg_list(node->arg_list, level + 1);
}

void print_arg_list(NodeArgList node, int level) {
  if (node == NULL) {
    return;
  }
  print_expression(node->arg, level);
  if (node->tail != NULL)
    print_arg_list(node->tail, level);
}

void print_expression(NodeExpression node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_simple_expr:
      fprintf(astout, "simple_expr\n");
      print_simple_expr_expression(node, level + 1);
      break;
    case kind_relational_expr:
      fprintf(astout, "relational_expr\n");
      print_relational_expr_expression(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_expr\n");
      break;
  }
}

void print_simple_expr_expression(NodeExpression node, int level) {
  print_simple_expr(node->simple_expr, level);
}

void print_relational_expr_expression(NodeExpression node, int level) {
  print_simple_expr(node->relational_expr.left, level);
  print_relation_op(node->relational_expr.op, level);
  print_simple_expr(node->relational_expr.right, level);
}

void print_simple_expr(NodeSimpleExpression node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_term_simple_expr:
      fprintf(astout, "term_simple_expr\n");
      print_term_simple_expr(node, level + 1);
      break;
    case kind_sign_simple_expr:
      fprintf(astout, "sign_simple_expr\n");
      print_sign_simple_expr(node, level + 1);
      break;
    case kind_additive_simple_expr:
      fprintf(astout, "additive_simple_expr\n");
      print_additive_simple_expr(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_simple_expr\n");
      break;
  }
}

void print_term_simple_expr(NodeSimpleExpression node, int level) {
  print_term(node->term, level);
}

void print_sign_simple_expr(NodeSimpleExpression node, int level) {
  print_sign_op(node->sign_simple_expr.op, level);
  print_term(node->sign_simple_expr.term, level);
}

void print_additive_simple_expr(NodeSimpleExpression node, int level) {
  print_simple_expr(node->additive_expr.left, level);
  print_additive_op(node->additive_expr.op, level);
  print_term(node->additive_expr.right, level);
}

void print_term(NodeTerm node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_factor_term:
      fprintf(astout, "factor_term\n");
      print_factor_term(node, level + 1);
      break;
    case kind_multiplicative_expr_term:
      fprintf(astout, "multiplicative_expr_term\n");
      print_multiplicative_term(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_term\n");
      break;
  }
}

void print_factor_term(NodeTerm node, int level) {
  print_factor(node->factor, level);
}

void print_multiplicative_term(NodeTerm node, int level) {
  print_term(node->multiplicative_expr.left, level);
  print_multiplicative_op(node->multiplicative_expr.op, level);
  print_factor(node->multiplicative_expr.right, level);
}

void print_factor(NodeFactor node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_var_access:
      fprintf(astout, "var_access_factor\n");
      print_var_access_factor(node, level + 1);
      break;
    case kind_func_call:
      fprintf(astout, "func_call_factor\n");
      print_func_call_factor(node, level + 1);
      break;
    case kind_parenthesized_expr:
      fprintf(astout, "parenthesized_expr_factor\n");
      print_parenthesized_expr_factor(node, level + 1);
      break;
    case kind_literal:
      fprintf(astout, "literal_factor\n");
      print_literal_factor(node, level + 1);
      break;
    case kind_not_factor:
      fprintf(astout, "not_factor\n");
      print_not_factor(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_factor\n");
      break;
  }
}

void print_var_access_factor(NodeFactor node, int level) {
  print_var_access(node->var_access, level);
}

void print_func_call_factor(NodeFactor node, int level) {
  print_func_call(node->func_call, level);
}

void print_parenthesized_expr_factor(NodeFactor node, int level) {
  print_expression(node->expression, level);
}

void print_literal_factor(NodeFactor node, int level) {
  print_literal(node->literal, level);
}

void print_not_factor(NodeFactor node, int level) {
  print_factor(node->not_factor, level);
}

void print_literal(NodeLiteral node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_lit_integer:
      fprintf(astout, "int_literal\n");
      print_int_literal(node, level + 1);
      break;
    case kind_lit_float:
      fprintf(astout, "float_literal\n");
      print_float_literal(node, level + 1);
      break;
    case kind_lit_char:
      fprintf(astout, "char_literal\n");
      print_char_literal(node, level + 1);
      break;
    case kind_lit_string:
      fprintf(astout, "string_literal\n");
      print_string_literal(node, level + 1);
      break;
    case kind_lit_boolean:
      fprintf(astout, "bool_literal\n");
      print_bool_literal(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_literal\n");
      break;
  }
}

void print_int_literal(NodeLiteral node, int level) {
  print_int(node->i_value, level);
}

void print_float_literal(NodeLiteral node, int level) {
  print_float(node->f_value, level);
}

void print_char_literal(NodeLiteral node, int level) {
  print_char(node->c_value, level);
}

void print_string_literal(NodeLiteral node, int level) {
  print_string(node->s_value, level);
}

void print_bool_literal(NodeLiteral node, int level) {
  print_bool(node->b_value, level);
}
