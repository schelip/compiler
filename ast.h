#ifndef AST_H
#define AST_H

typedef enum {
  type_int,
  type_float,
  type_char,
  type_string,
  type_bool  
} DataType;

typedef enum
{
  op_uplus,
  op_uminus
} SignOperator;

typedef enum
{
  op_eq,
  op_ne,
  op_gt,
  op_ge,
  op_lt,
  op_le
} RelationalOperator;

typedef enum
{
  op_plus,
  op_minus,
  op_or
} AdditiveOperator;

typedef enum
{
  op_mul,
  op_div,
  op_mod,
  op_and
} MultiplicativeOperator;


typedef struct nodeProgram *NodeProgram;
typedef struct nodeVarDeclList *NodeVarDeclList;
typedef struct nodeVarDecl *NodeVarDecl;
typedef struct nodeVarIdList *NodeVarIdList;
typedef struct nodeTypeSpecifier *NodeTypeSpecifier;
typedef struct nodeFuncDeclList *NodeFuncDeclList;
typedef struct nodeFuncDecl *NodeFuncDecl;
typedef struct nodeFuncHeader *NodeFuncHeader;
typedef struct nodeFuncParamList *NodeFuncParamList;
typedef struct nodeFuncParam *NodeFuncParam;
typedef struct nodeStmtBlock *NodeStmtBlock;
typedef struct nodeStmtList *NodeStmtList;
typedef struct nodeStmt *NodeStmt;
typedef struct nodeVarAccess *NodeVarAccess;
typedef struct nodeFuncCall *NodeFuncCall;
typedef struct nodeArgList *NodeArgList;
typedef struct nodeExpression *NodeExpression;
typedef struct nodeSimpleExpression *NodeSimpleExpression;
typedef struct nodeTerm *NodeTerm;
typedef struct nodeFactor *NodeFactor;
typedef struct nodeLiteral *NodeLiteral;


struct nodeProgram
{
  NodeVarDeclList var_decl_list;
  NodeFuncDeclList func_decl_list;
  NodeStmtBlock main_stmt_block;
};

struct nodeVarDeclList
{
  NodeVarDecl var_decl;
  NodeVarDeclList tail;
};

struct nodeVarDecl
{
  NodeVarIdList var_id_list;
  NodeTypeSpecifier type_specifier;
};

struct nodeVarIdList
{
  char *var_id;
  NodeVarIdList tail;
};

struct nodeTypeSpecifier
{
  enum
  {
    kind_primitive,
    kind_array
  } kind;
  union
  {
    DataType primitive_type;
    struct {
      DataType data_type;
      int size;
    } array_type;
  };
};

struct nodeFuncDeclList
{
  NodeFuncDecl func_decl;
  NodeFuncDeclList tail;
};

struct nodeFuncDecl
{
  NodeFuncHeader func_header;
  NodeStmtBlock func_stmt_block;
};

struct nodeFuncHeader
{
  char *func_identifier;
  NodeFuncParamList func_param_list;
  NodeTypeSpecifier func_return_type;
};

struct nodeFuncParamList
{
  NodeFuncParam param;
  NodeFuncParamList tail;
};

struct nodeFuncParam
{
  NodeVarIdList param_id_list;
  NodeTypeSpecifier param_type;
};

struct nodeStmtBlock
{
  NodeVarDeclList block_var_decl_list;
  NodeStmtList stmt_list;
};

struct nodeStmtList
{
  NodeStmt stmt;
  NodeStmtList tail;
};

struct nodeStmt
{
  enum
  {
    kind_attribution_stmt,
    kind_func_call_stmt,
    kind_comparison_ifx_stmt,
    kind_comparison_ifelse_stmt,
    kind_iteration_stmt,
    kind_ret_stmt,
    kind_block_stmt
  } kind;
  union
  {
    struct {
      NodeVarAccess var_access;
      NodeExpression right;
    } attribution_stmt;
    struct {
      NodeFuncCall call;
    } func_call_stmt;
    struct {
      NodeExpression cond;
      NodeStmt body;
    } comparison_ifx_stmt;
    struct {
      NodeExpression cond;
      NodeStmt if_body;
      NodeStmt else_body;
    } comparison_ifelse_stmt;
    struct {
      NodeExpression cond;
      NodeStmt body;
    } iteration_stmt;
    NodeExpression return_expr;
    NodeStmtBlock block;
  };
};

struct nodeVarAccess
{
  enum
  {
    kind_simple_var_access,
    kind_array_access
  } kind;
  union
  {
    char *var_id;
    struct {
      char *arr_id;
      NodeExpression idx;
    } array_access;
  };
};

struct nodeFuncCall
{
  char *func_id;
  NodeArgList arg_list;
};

struct nodeArgList
{
  NodeExpression arg;
  NodeArgList tail;
};

struct nodeExpression
{
  enum
  {
    kind_simple_expr,
    kind_relational_expr
  } kind;
  union
  {
    NodeSimpleExpression simple_expr;
    struct {
      NodeSimpleExpression left;
      RelationalOperator op;
      NodeSimpleExpression right;
    } relational_expr;
  };
};

struct nodeSimpleExpression
{
  enum
  {
    kind_term_simple_expr,
    kind_sign_simple_expr,
    kind_additive_simple_expr
  } kind;
  union
  {
    NodeTerm term;
    struct {
      SignOperator op;
      NodeTerm term;
    } sign_simple_expr;
    struct {
      NodeSimpleExpression left;
      AdditiveOperator op;
      NodeTerm right;
    } additive_expr;
  };
};

struct nodeTerm
{
  enum
  {
    kind_factor_term,
    kind_multiplicative_expr_term
  } kind;
  union
  {
    NodeFactor factor;
    struct {
      NodeTerm left;
      MultiplicativeOperator op;
      NodeFactor right;
    } multiplicative_expr;
  };
};

struct nodeFactor
{
  enum
  {
    kind_var_access,
    kind_func_call,
    kind_parenthesized_expr,
    kind_literal,
    kind_not_factor
  } kind;
  union
  {
    NodeVarAccess var_access;
    NodeFuncCall func_call;
    NodeExpression expression;
    NodeLiteral literal;
    NodeFactor not_factor;
  };
};

struct nodeLiteral
{
  enum
  {
    kind_lit_integer,
    kind_lit_float,
    kind_lit_char,
    kind_lit_string,
    kind_lit_boolean
  } kind;
  union
  {
    int i_value;
    float f_value;
    char c_value;
    char *s_value;
    int b_value;
  };
};


NodeProgram create_ast_node_program(NodeVarDeclList var_decl_list, NodeFuncDeclList func_decl_list, NodeStmtBlock main_stmt_block);
NodeVarDeclList create_ast_node_var_decl_list(NodeVarDecl var_decl, NodeVarDeclList tail);
NodeVarDecl create_ast_node_var_decl(NodeVarIdList var_id_list, NodeTypeSpecifier type_specifier);
NodeVarIdList create_ast_node_var_id_list(char *var_id, NodeVarIdList tail);
NodeTypeSpecifier create_ast_node_primitive_type_specifier(DataType data_type);
NodeTypeSpecifier create_ast_node_array_type_specifier(DataType data_type, int size);
NodeFuncDeclList create_ast_node_func_decl_list(NodeFuncDecl func_decl, NodeFuncDeclList tail);
NodeFuncDecl create_ast_node_func_decl(NodeFuncHeader func_header, NodeStmtBlock func_stmt_block);
NodeFuncHeader create_ast_node_func_header(char *func_identifier, NodeFuncParamList func_param_list, NodeTypeSpecifier func_return_type);
NodeFuncParamList create_ast_node_func_param_list(NodeFuncParam param, NodeFuncParamList tail);
NodeFuncParam create_ast_node_func_param(NodeVarIdList param_id_list, NodeTypeSpecifier param_type);
NodeStmtBlock create_ast_node_stmt_block(NodeVarDeclList block_var_decl_list, NodeStmtList stmt_list);
NodeStmtList create_ast_node_stmt_list(NodeStmt stmt, NodeStmtList tail);
NodeStmt create_ast_node_attribution_stmt(NodeVarAccess var_access, NodeExpression right);
NodeStmt create_ast_node_func_call_stmt(NodeFuncCall call);
NodeStmt create_ast_node_ifx_stmt(NodeExpression cond, NodeStmt body);
NodeStmt create_ast_node_ifelse_stmt(NodeExpression cond, NodeStmt if_body, NodeStmt else_body);
NodeStmt create_ast_node_iteration_stmt(NodeExpression cond, NodeStmt body);
NodeStmt create_ast_node_return_stmt(NodeExpression expr);
NodeStmt create_ast_node_block_stmt(NodeStmtBlock block);
NodeVarAccess create_ast_node_simple_var_access(char *var_id);
NodeVarAccess create_ast_node_array_access(char *arr_id, NodeExpression idx);
NodeFuncCall create_ast_node_func_call(char *func_id, NodeArgList arg_list);
NodeArgList create_ast_node_arg_list(NodeExpression arg, NodeArgList tail);
NodeExpression create_ast_node_simple_expr_expression(NodeSimpleExpression simple_expr);
NodeExpression create_ast_node_relational_expr_expression(NodeSimpleExpression left, RelationalOperator op, NodeSimpleExpression right);
NodeSimpleExpression create_ast_node_term_simple_expr(NodeTerm term);
NodeSimpleExpression create_ast_node_sign_simple_expr(SignOperator op, NodeTerm right);
NodeSimpleExpression create_ast_node_additive_simple_expr(NodeSimpleExpression left, AdditiveOperator op, NodeTerm right);
NodeTerm create_ast_node_factor_term(NodeFactor factor);
NodeTerm create_ast_node_multiplicative_term(NodeTerm left, MultiplicativeOperator op, NodeFactor right);
NodeFactor create_ast_node_var_access_factor(NodeVarAccess var_access);
NodeFactor create_ast_node_func_call_factor(NodeFuncCall func_call);
NodeFactor create_ast_node_parenthesized_expr_factor(NodeExpression expression);
NodeFactor create_ast_node_literal_factor(NodeLiteral literal);
NodeFactor create_ast_node_not_factor(NodeFactor not_factor);
NodeLiteral create_ast_node_int_literal(int value);
NodeLiteral create_ast_node_float_literal(float value);
NodeLiteral create_ast_node_char_literal(char value);
NodeLiteral create_ast_node_string_literal(char *value);
NodeLiteral create_ast_node_bool_literal(int value);


void print_data_type(DataType data_type, int level);
void print_sign_op(SignOperator op, int level);
void print_relation_op(RelationalOperator op, int level);
void print_additive_op(AdditiveOperator op, int level);
void print_multiplicative_op(MultiplicativeOperator op, int level);
void print_ast_node_program(NodeProgram node, int level);
void print_ast_node_var_decl_list(NodeVarDeclList node, int level);
void print_ast_node_var_decl(NodeVarDecl node, int level);
void print_ast_node_var_id_list(NodeVarIdList node, int level);
void print_ast_node_type_specifier(NodeTypeSpecifier node, int level);
void print_ast_node_primitive_type_specifier(NodeTypeSpecifier node, int level);
void print_ast_node_array_type_specifier(NodeTypeSpecifier node, int level);
void print_ast_node_func_decl_list(NodeFuncDeclList node, int level);
void print_ast_node_func_decl(NodeFuncDecl node, int level);
void print_ast_node_func_header(NodeFuncHeader node, int level);
void print_ast_node_func_param_list(NodeFuncParamList node, int level);
void print_ast_node_func_param(NodeFuncParam node, int level);
void print_ast_node_stmt_block(NodeStmtBlock node, int level);
void print_ast_node_stmt_list(NodeStmtList node, int level);
void print_ast_node_stmt(NodeStmt node, int level);
void print_ast_node_attribution_stmt(NodeStmt node, int level);
void print_ast_node_func_call_stmt(NodeStmt node, int level);
void print_ast_node_ifx_stmt(NodeStmt node, int level);
void print_ast_node_ifelse_stmt(NodeStmt node, int level);
void print_ast_node_iteration_stmt(NodeStmt node, int level);
void print_ast_node_return_stmt(NodeStmt node, int level);
void print_ast_node_block_stmt(NodeStmt node, int level);
void print_ast_node_var_access(NodeVarAccess node, int level);
void print_ast_node_simple_var_access(NodeVarAccess node, int level);
void print_ast_node_array_access(NodeVarAccess node, int level);
void print_ast_node_func_call(NodeFuncCall node, int level);
void print_ast_node_arg_list(NodeArgList node, int level);
void print_ast_node_expression(NodeExpression node, int level);
void print_ast_node_simple_expr_expression(NodeExpression node, int level);
void print_ast_node_relational_expr_expression(NodeExpression node, int level);
void print_ast_node_simple_expr(NodeSimpleExpression node, int level);
void print_ast_node_term_simple_expr(NodeSimpleExpression node, int level);
void print_ast_node_sign_simple_expr(NodeSimpleExpression node, int level);
void print_ast_node_additive_simple_expr(NodeSimpleExpression node, int level);
void print_ast_node_term(NodeTerm node, int level);
void print_ast_node_factor_term(NodeTerm node, int level);
void print_ast_node_multiplicative_term(NodeTerm node, int level);
void print_ast_node_factor(NodeFactor node, int level);
void print_ast_node_var_access_factor(NodeFactor node, int level);
void print_ast_node_func_call_factor(NodeFactor node, int level);
void print_ast_node_parenthesized_expr_factor(NodeFactor node, int level);
void print_ast_node_literal_factor(NodeFactor node, int level);
void print_ast_node_not_factor(NodeFactor node, int level);
void print_ast_node_literal(NodeLiteral node, int level);
void print_ast_node_int_literal(NodeLiteral node, int level);
void print_ast_node_float_literal(NodeLiteral node, int level);
void print_ast_node_char_literal(NodeLiteral node, int level);
void print_ast_node_string_literal(NodeLiteral node, int level);
void print_ast_node_bool_literal(NodeLiteral node, int level);

#endif /* AST_H */
