#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// Node creating functions //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


NodeProgram create_ast_node_program(NodeVarDeclList var_decl_list, NodeFuncDeclList func_decl_list, NodeStmtBlock main_stmt_block) {
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
  return node;
}

NodeVarDeclList create_ast_node_var_decl_list(NodeVarDecl var_decl, NodeVarDeclList tail) {
  NodeVarDeclList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_decl = var_decl;
  node->tail = tail;
  return node;
}

NodeVarDecl create_ast_node_var_decl(NodeVarIdList var_id_list, NodeTypeSpecifier type_specifier) {
  NodeVarDecl node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id_list = var_id_list;
  node->type_specifier = type_specifier;
  return node;
}

NodeVarIdList create_ast_node_var_id_list(char *var_id, NodeVarIdList tail) {
  NodeVarIdList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->var_id = var_id;
  node->tail = tail;
  return node;
}

NodeTypeSpecifier create_ast_node_primitive_type_specifier(DataType data_type) {
  NodeTypeSpecifier node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_primitive;
  node->primitive_type = data_type;
  return node;
}

NodeTypeSpecifier create_ast_node_array_type_specifier(DataType data_type, int size) {
  NodeTypeSpecifier node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_array;
  node->array_type.data_type = data_type;
  node->array_type.size = size;
  return node;
}

NodeFuncDeclList create_ast_node_func_decl_list(NodeFuncDecl func_decl, NodeFuncDeclList tail) {
  NodeFuncDeclList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_decl = func_decl;
  node->tail = tail;
  return node;
}

NodeFuncDecl create_ast_node_func_decl(NodeFuncHeader func_header, NodeStmtBlock func_stmt_block) {
  NodeFuncDecl node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_header = func_header;
  node->func_stmt_block = func_stmt_block;
  return node;
}

NodeFuncHeader create_ast_node_func_header(char *func_identifier, NodeFuncParamList func_param_list, NodeTypeSpecifier func_return_type) {
  NodeFuncHeader node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_identifier = func_identifier;
  node->func_param_list = func_param_list;
  node->func_return_type = func_return_type;
  return node;
}

NodeFuncParamList create_ast_node_func_param_list(NodeFuncParam param, NodeFuncParamList tail) {
  NodeFuncParamList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->param = param;
  node->tail = tail;
  return node;
}

NodeFuncParam create_ast_node_func_param(NodeVarIdList param_id_list, NodeTypeSpecifier param_type) {
  NodeFuncParam node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->param_id_list = param_id_list;
  node->param_type = param_type;
  return node;
}

NodeStmtBlock create_ast_node_stmt_block(NodeVarDeclList block_var_decl_list, NodeStmtList stmt_list) {
  NodeStmtBlock node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->block_var_decl_list = block_var_decl_list;
  node->stmt_list = stmt_list;
  return node;
}

NodeStmtList create_ast_node_stmt_list(NodeStmt stmt, NodeStmtList tail) {
  NodeStmtList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->stmt = stmt;
  node->tail = tail;
  return node;
}

NodeStmt create_ast_node_attribution_stmt(NodeVarAccess var_access, NodeExpression right) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_attribution_stmt;
  node->attribution_stmt.var_access = var_access;
  node->attribution_stmt.right = right;
  return node;
}

NodeStmt create_ast_node_func_call_stmt(NodeFuncCall call) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_func_call_stmt;
  node->func_call_stmt.call = call;
  return node;
}

NodeStmt create_ast_node_ifx_stmt(NodeExpression cond, NodeStmt body) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_comparison_ifx_stmt;
  node->comparison_ifx_stmt.cond = cond;
  node->comparison_ifx_stmt.body = body;
  return node;
}

NodeStmt create_ast_node_ifelse_stmt(NodeExpression cond, NodeStmt if_body, NodeStmt else_body) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_comparison_ifelse_stmt;
  node->comparison_ifelse_stmt.cond = cond;
  node->comparison_ifelse_stmt.if_body = if_body;
  node->comparison_ifelse_stmt.else_body = else_body;
  return node;
}

NodeStmt create_ast_node_iteration_stmt(NodeExpression cond, NodeStmt body) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_iteration_stmt;
  node->iteration_stmt.cond = cond;
  node->iteration_stmt.body = body;
  return node;
}

NodeStmt create_ast_node_return_stmt(NodeExpression expr) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_ret_stmt;
  node->return_expr = expr;
  return node;
}

NodeStmt create_ast_node_block_stmt(NodeStmtBlock block) {
  NodeStmt node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_block_stmt;
  node->block = block;
  return node;
}

NodeVarAccess create_ast_node_simple_var_access(char *var_id) {
  NodeVarAccess node = malloc(sizeof(*node));

  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_simple_var_access;
  node->var_id = var_id;
}

NodeVarAccess create_ast_node_array_access(char *arr_id, NodeExpression idx) {
  NodeVarAccess node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_array_access;
  node->array_access.arr_id = arr_id;
  node->array_access.idx = idx;
}

NodeFuncCall create_ast_node_func_call(char *func_id, NodeArgList arg_list) {
  NodeFuncCall node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->func_id = func_id;
  node->arg_list = arg_list;
  return node;
}

NodeArgList create_ast_node_arg_list(NodeExpression arg, NodeArgList tail) {
  NodeArgList node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->arg = arg;
  node->tail = tail;
  return node;
}

NodeExpression create_ast_node_simple_expr_expression(NodeSimpleExpression simple_expr) {
  NodeExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_simple_expr;
  node->simple_expr = simple_expr;
  return node;
}

NodeExpression create_ast_node_relational_expr_expression(NodeSimpleExpression left, RelationalOperator op, NodeSimpleExpression right) {
  NodeExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_relational_expr;
  node->relational_expr.left = left;
  node->relational_expr.op = op;
  node->relational_expr.right = right;
  return node;
}

NodeSimpleExpression create_ast_node_term_simple_expr(NodeTerm term) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_term_simple_expr;
  node->term = term;
  return node;
}

NodeSimpleExpression create_ast_node_sign_simple_expr(SignOperator op, NodeTerm term) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_sign_simple_expr;
  node->sign_simple_expr.op = op;
  node->sign_simple_expr.term = term;
  return node;
}

NodeSimpleExpression create_ast_node_additive_simple_expr(NodeSimpleExpression left, AdditiveOperator op, NodeTerm right) {
  NodeSimpleExpression node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_additive_simple_expr;
  node->additive_expr.left = left;
  node->additive_expr.op = op;
  node->additive_expr.right = right;
  return node;
}

NodeTerm create_ast_node_factor_term(NodeFactor factor) {
  NodeTerm node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_factor_term;
  node->factor = factor;
  return node;
}

NodeTerm create_ast_node_multiplicative_term(NodeTerm left, MultiplicativeOperator op, NodeFactor right) {
  NodeTerm node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_multiplicative_expr_term;
  node->multiplicative_expr.left = left;
  node->multiplicative_expr.op = op;
  node->multiplicative_expr.right = right;
  return node;
}

NodeFactor create_ast_node_var_access_factor(NodeVarAccess var_access) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_var_access;
  node->var_access = var_access;
  return node;
}

NodeFactor create_ast_node_func_call_factor(NodeFuncCall func_call) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_func_call;
  node->func_call = func_call;
  return node;
}

NodeFactor create_ast_node_parenthesized_expr_factor(NodeExpression expression) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_parenthesized_expr;
  node->expression = expression;
  return node;
}

NodeFactor create_ast_node_literal_factor(NodeLiteral literal) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_literal;
  node->literal = literal;
  return node;
}

NodeFactor create_ast_node_not_factor(NodeFactor not_factor) {
  NodeFactor node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_not_factor;
  node->not_factor = not_factor;
  return node;
}

NodeLiteral create_ast_node_int_literal(int value) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_integer;
  node->i_value = value;
  return node;
}

NodeLiteral create_ast_node_float_literal(float value) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_float;
  node->f_value = value;
  return node;
}

NodeLiteral create_ast_node_char_literal(char value) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_char;
  node->c_value = value;
  return node;
}

NodeLiteral create_ast_node_string_literal(char *value) {
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
  return node;
}

NodeLiteral create_ast_node_bool_literal(int value) {
  NodeLiteral node = malloc(sizeof(*node));
  if (node == NULL) {
    fprintf(stderr, "Error: out of memory\n");
    exit(EXIT_FAILURE);
  }
  node->kind = kind_lit_boolean;
  node->b_value = value;
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

void print_ast_node_program(NodeProgram node, int level) {
  print_indent(level);
  fprintf(astout, "program\n");
  print_ast_node_var_decl_list(node->var_decl_list, level + 1);
  print_ast_node_func_decl_list(node->func_decl_list, level + 1);
  print_ast_node_stmt_block(node->main_stmt_block, level + 1);
}

void print_ast_node_var_decl_list(NodeVarDeclList node, int level) {
  if (node == NULL) {
    return;
  }
  print_ast_node_var_decl(node->var_decl, level);
  if (node->tail != NULL)
    print_ast_node_var_decl_list(node->tail, level);
}

void print_ast_node_var_decl(NodeVarDecl node, int level) {
  print_indent(level);
  fprintf(astout, "var_decl\n");
  print_ast_node_var_id_list(node->var_id_list, level + 1);
  print_ast_node_type_specifier(node->type_specifier, level + 1);
}

void print_ast_node_var_id_list(NodeVarIdList node, int level) {
  if (node == NULL) {
    return;
  }
  print_indent(level);
  fprintf(astout, "id: %s\n", node->var_id);
  if (node->tail != NULL)
    print_ast_node_var_id_list(node->tail, level);
}

void print_ast_node_type_specifier(NodeTypeSpecifier node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_primitive:
      fprintf(astout, "primitive_type_specifier\n");
      print_ast_node_primitive_type_specifier(node, level + 1);
      break;
    case kind_array:
      fprintf(astout, "array_type_specifier\n");
      print_ast_node_array_type_specifier(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_type_specifier\n");
      break;
  }
}

void print_ast_node_primitive_type_specifier(NodeTypeSpecifier node, int level) {
  print_data_type(node->primitive_type, level);
}

void print_ast_node_array_type_specifier(NodeTypeSpecifier node, int level) {
  print_data_type(node->array_type.data_type, level);
  print_int(node->array_type.size, level);
}

void print_ast_node_func_decl_list(NodeFuncDeclList node, int level) {
  if (node == NULL) {
    return;
  }
  print_ast_node_func_decl(node->func_decl, level);
  if (node->tail != NULL)
    print_ast_node_func_decl_list(node->tail, level);
}

void print_ast_node_func_decl(NodeFuncDecl node, int level) {
  print_indent(level);
  fprintf(astout, "func_decl\n");
  print_ast_node_func_header(node->func_header, level + 1);
  print_ast_node_stmt_block(node->func_stmt_block, level + 1);
}

void print_ast_node_func_header(NodeFuncHeader node, int level) {
  print_indent(level);
  fprintf(astout, "func_header\n");
  print_indent(level + 1);
  fprintf(astout, "id: %s\n", node->func_identifier);
  print_ast_node_func_param_list(node->func_param_list, level + 1);
  print_ast_node_type_specifier(node->func_return_type, level + 1);
}

void print_ast_node_func_param_list(NodeFuncParamList node, int level) {
  if (node == NULL) {
    return;
  }
  print_ast_node_func_param(node->param, level);
  if (node->tail != NULL)
    print_ast_node_func_param_list(node->tail, level);
}

void print_ast_node_func_param(NodeFuncParam node, int level) {
  print_indent(level);
  fprintf(astout, "func_param\n");
  print_ast_node_var_id_list(node->param_id_list, level + 1);
  print_ast_node_type_specifier(node->param_type, level + 1);
}

void print_ast_node_stmt_block(NodeStmtBlock node, int level) {
  print_indent(level);
  fprintf(astout, "stmt_block\n");
  print_ast_node_var_decl_list(node->block_var_decl_list, level + 1);
  print_ast_node_stmt_list(node->stmt_list, level + 1);
}

void print_ast_node_stmt_list(NodeStmtList node, int level) {
  if (node == NULL) {
    return;
  }
  print_ast_node_stmt(node->stmt, level);
  if (node->tail != NULL)
    print_ast_node_stmt_list(node->tail, level);
}

void print_ast_node_stmt(NodeStmt node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_attribution_stmt:
      fprintf(astout, "attribution_stmt\n");
      print_ast_node_attribution_stmt(node, level + 1);
      break;
    case kind_func_call_stmt:
      fprintf(astout, "func_call_stmt\n");
      print_ast_node_func_call_stmt(node, level + 1);
      break;
    case kind_comparison_ifx_stmt:
      fprintf(astout, "comparison_ifx_stmt\n");
      print_ast_node_ifx_stmt(node, level + 1);
      break;
    case kind_comparison_ifelse_stmt:
      fprintf(astout, "comparison_ifelse_stmt\n");
      print_ast_node_ifelse_stmt(node, level + 1);
      break;
    case kind_iteration_stmt:
      fprintf(astout, "iteration_stmt\n");
      print_ast_node_iteration_stmt(node, level + 1);
      break;
    case kind_ret_stmt:
      fprintf(astout, "ret_stmt\n");
      print_ast_node_return_stmt(node, level + 1);
      break;
    case kind_block_stmt:
      fprintf(astout, "block_stmt\n");
      print_ast_node_block_stmt(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_stmt\n");
      break;
  }
}

void print_ast_node_attribution_stmt(NodeStmt node, int level) {
  print_ast_node_var_access(node->attribution_stmt.var_access, level);
  print_ast_node_expression(node->attribution_stmt.right, level);
}

void print_ast_node_func_call_stmt(NodeStmt node, int level) {
  print_ast_node_func_call(node->func_call_stmt.call, level);
}

void print_ast_node_ifx_stmt(NodeStmt node, int level) {
  print_ast_node_expression(node->comparison_ifx_stmt.cond, level);
  print_ast_node_stmt(node->comparison_ifx_stmt.body, level);
}

void print_ast_node_ifelse_stmt(NodeStmt node, int level) {
  print_ast_node_expression(node->comparison_ifelse_stmt.cond, level);
  print_ast_node_stmt(node->comparison_ifelse_stmt.if_body, level);
  print_ast_node_stmt(node->comparison_ifelse_stmt.else_body, level);
}

void print_ast_node_iteration_stmt(NodeStmt node, int level) {
  print_ast_node_expression(node->iteration_stmt.cond, level);
  print_ast_node_stmt(node->iteration_stmt.body, level);
}

void print_ast_node_return_stmt(NodeStmt node, int level) {
  print_ast_node_expression(node->return_expr, level);
}

void print_ast_node_block_stmt(NodeStmt node, int level) {
  print_ast_node_stmt_block(node->block, level);
}

void print_ast_node_var_access(NodeVarAccess node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_simple_var_access:
      fprintf(astout, "simple_var_access\n");
      print_ast_node_simple_var_access(node, level + 1);
      break;
    case kind_array_access:
      fprintf(astout, "array_access\n");
      print_ast_node_array_access(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_var_access\n");
      break;
  }
}

void print_ast_node_simple_var_access(NodeVarAccess node, int level) {
  print_indent(level);
  fprintf(astout, "id: %s\n", node->var_id);
}

void print_ast_node_array_access(NodeVarAccess node, int level) {
  print_ast_node_expression(node->array_access.idx, level);
}

void print_ast_node_func_call(NodeFuncCall node, int level) {
  print_indent(level);
  fprintf(astout, "func_call\n");
  print_indent(level + 1);
  fprintf(astout, "id: %s\n", node->func_id);
  print_ast_node_arg_list(node->arg_list, level + 1);
}

void print_ast_node_arg_list(NodeArgList node, int level) {
  if (node == NULL) {
    return;
  }
  print_ast_node_expression(node->arg, level);
  if (node->tail != NULL)
    print_ast_node_arg_list(node->tail, level);
}

void print_ast_node_expression(NodeExpression node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_simple_expr:
      fprintf(astout, "simple_expr\n");
      print_ast_node_simple_expr_expression(node, level + 1);
      break;
    case kind_relational_expr:
      fprintf(astout, "relational_expr\n");
      print_ast_node_relational_expr_expression(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_expr\n");
      break;
  }
}

void print_ast_node_simple_expr_expression(NodeExpression node, int level) {
  print_ast_node_simple_expr(node->simple_expr, level);
}

void print_ast_node_relational_expr_expression(NodeExpression node, int level) {
  print_ast_node_simple_expr(node->relational_expr.left, level);
  print_relation_op(node->relational_expr.op, level);
  print_ast_node_simple_expr(node->relational_expr.right, level);
}

void print_ast_node_simple_expr(NodeSimpleExpression node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_term_simple_expr:
      fprintf(astout, "term_simple_expr\n");
      print_ast_node_term_simple_expr(node, level + 1);
      break;
    case kind_sign_simple_expr:
      fprintf(astout, "sign_simple_expr\n");
      print_ast_node_sign_simple_expr(node, level + 1);
      break;
    case kind_additive_simple_expr:
      fprintf(astout, "additive_simple_expr\n");
      print_ast_node_additive_simple_expr(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_simple_expr\n");
      break;
  }
}

void print_ast_node_term_simple_expr(NodeSimpleExpression node, int level) {
  print_ast_node_term(node->term, level);
}

void print_ast_node_sign_simple_expr(NodeSimpleExpression node, int level) {
  print_sign_op(node->sign_simple_expr.op, level);
  print_ast_node_term(node->sign_simple_expr.term, level);
}

void print_ast_node_additive_simple_expr(NodeSimpleExpression node, int level) {
  print_ast_node_simple_expr(node->additive_expr.left, level);
  print_additive_op(node->additive_expr.op, level);
  print_ast_node_term(node->additive_expr.right, level);
}

void print_ast_node_term(NodeTerm node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_factor_term:
      fprintf(astout, "factor_term\n");
      print_ast_node_factor_term(node, level + 1);
      break;
    case kind_multiplicative_expr_term:
      fprintf(astout, "multiplicative_expr_term\n");
      print_ast_node_multiplicative_term(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_term\n");
      break;
  }
}

void print_ast_node_factor_term(NodeTerm node, int level) {
  print_ast_node_factor(node->factor, level);
}

void print_ast_node_multiplicative_term(NodeTerm node, int level) {
  print_ast_node_term(node->multiplicative_expr.left, level);
  print_multiplicative_op(node->multiplicative_expr.op, level);
  print_ast_node_factor(node->multiplicative_expr.right, level);
}

void print_ast_node_factor(NodeFactor node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_var_access:
      fprintf(astout, "var_access_factor\n");
      print_ast_node_var_access_factor(node, level + 1);
      break;
    case kind_func_call:
      fprintf(astout, "func_call_factor\n");
      print_ast_node_func_call_factor(node, level + 1);
      break;
    case kind_parenthesized_expr:
      fprintf(astout, "parenthesized_expr_factor\n");
      print_ast_node_parenthesized_expr_factor(node, level + 1);
      break;
    case kind_literal:
      fprintf(astout, "literal_factor\n");
      print_ast_node_literal_factor(node, level + 1);
      break;
    case kind_not_factor:
      fprintf(astout, "not_factor\n");
      print_ast_node_not_factor(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_factor\n");
      break;
  }
}

void print_ast_node_var_access_factor(NodeFactor node, int level) {
  print_ast_node_var_access(node->var_access, level);
}

void print_ast_node_func_call_factor(NodeFactor node, int level) {
  print_ast_node_func_call(node->func_call, level);
}

void print_ast_node_parenthesized_expr_factor(NodeFactor node, int level) {
  print_ast_node_expression(node->expression, level);
}

void print_ast_node_literal_factor(NodeFactor node, int level) {
  print_ast_node_literal(node->literal, level);
}

void print_ast_node_not_factor(NodeFactor node, int level) {
  print_ast_node_factor(node->not_factor, level);
}

void print_ast_node_literal(NodeLiteral node, int level) {
  print_indent(level);
  switch (node->kind) {
    case kind_lit_integer:
      fprintf(astout, "int_literal\n");
      print_ast_node_int_literal(node, level + 1);
      break;
    case kind_lit_float:
      fprintf(astout, "float_literal\n");
      print_ast_node_float_literal(node, level + 1);
      break;
    case kind_lit_char:
      fprintf(astout, "char_literal\n");
      print_ast_node_char_literal(node, level + 1);
      break;
    case kind_lit_string:
      fprintf(astout, "string_literal\n");
      print_ast_node_string_literal(node, level + 1);
      break;
    case kind_lit_boolean:
      fprintf(astout, "bool_literal\n");
      print_ast_node_bool_literal(node, level + 1);
      break;
    default:
      fprintf(astout, "unknown_literal\n");
      break;
  }
}

void print_ast_node_int_literal(NodeLiteral node, int level) {
  print_int(node->i_value, level);
}

void print_ast_node_float_literal(NodeLiteral node, int level) {
  print_float(node->f_value, level);
}

void print_ast_node_char_literal(NodeLiteral node, int level) {
  print_char(node->c_value, level);
}

void print_ast_node_string_literal(NodeLiteral node, int level) {
  print_string(node->s_value, level);
}

void print_ast_node_bool_literal(NodeLiteral node, int level) {
  print_bool(node->b_value, level);
}
