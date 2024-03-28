#ifndef SYNTAX_H
#define SYNTAX_H

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
typedef struct nodeVarId *NodeVarId;
typedef struct nodeVar *NodeVar;
typedef struct nodeType *NodeType;
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
  int lineno;
};

struct nodeVarDeclList
{
  NodeVarDecl var_decl;
  NodeVarDeclList tail;
  int lineno;
};

struct nodeVarDecl
{
  NodeVarIdList var_id_list;
  NodeType type_specifier;
  int lineno;
};

struct nodeVarIdList
{
  NodeVarId var_id;
  NodeVarIdList tail;
  int lineno;
};

struct nodeVarId
{
  char *var_id;
  int lineno;
};

struct nodeVar
{
  NodeVarId var_id;
  NodeType var_type;
  NodeLiteral var_value;
  int lineno;
};

struct nodeType
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
  int lineno;
};

struct nodeFuncDeclList
{
  NodeFuncDecl func_decl;
  NodeFuncDeclList tail;
  int lineno;
};

struct nodeFuncDecl
{
  NodeFuncHeader func_header;
  NodeStmtBlock func_stmt_block;
  int lineno;
};

struct nodeFuncHeader
{
  char *func_identifier;
  NodeFuncParamList func_param_list;
  NodeType func_return_type;
  int lineno;
};

struct nodeFuncParamList
{
  NodeFuncParam param;
  NodeFuncParamList tail;
  int lineno;
};

struct nodeFuncParam
{
  NodeVarIdList param_id_list;
  NodeType param_type;
  int lineno;
};

struct nodeStmtBlock
{
  NodeVarDeclList block_var_decl_list;
  NodeStmtList stmt_list;
  int lineno;
};

struct nodeStmtList
{
  NodeStmt stmt;
  NodeStmtList tail;
  int lineno;
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
  int lineno;
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
  int lineno;
};

struct nodeFuncCall
{
  char *func_id;
  NodeArgList arg_list;
  int lineno;
};

struct nodeArgList
{
  NodeExpression arg;
  NodeArgList tail;
  int lineno;
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
  int lineno;
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
  int lineno;
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
  int lineno;
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
  int lineno;
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
  int lineno;
};


NodeProgram create_program(NodeVarDeclList var_decl_list, NodeFuncDeclList func_decl_list, NodeStmtBlock main_stmt_block, int lineno);
NodeVarDeclList create_var_decl_list(NodeVarDecl var_decl, NodeVarDeclList tail, int lineno);
NodeVarDecl create_var_decl(NodeVarIdList var_id_list, NodeType type_specifier, int lineno);
NodeVarIdList create_var_id_list(NodeVarId var_id, NodeVarIdList tail, int lineno);
NodeVarId create_var_id(char *var_id, int lineno);
NodeVar create_var(NodeVarId var_id, NodeType var_type, NodeLiteral value, int lineno);
NodeType create_primitive_type_specifier(DataType data_type, int lineno);
NodeType create_array_type_specifier(DataType data_type, int size, int lineno);
NodeFuncDeclList create_func_decl_list(NodeFuncDecl func_decl, NodeFuncDeclList tail, int lineno);
NodeFuncDecl create_func_decl(NodeFuncHeader func_header, NodeStmtBlock func_stmt_block, int lineno);
NodeFuncHeader create_func_header(char *func_identifier, NodeFuncParamList func_param_list, NodeType func_return_type, int lineno);
NodeFuncParamList create_func_param_list(NodeFuncParam param, NodeFuncParamList tail, int lineno);
NodeFuncParam create_func_param(NodeVarIdList param_id_list, NodeType param_type, int lineno);
NodeStmtBlock create_stmt_block(NodeVarDeclList block_var_decl_list, NodeStmtList stmt_list, int lineno);
NodeStmtList create_stmt_list(NodeStmt stmt, NodeStmtList tail, int lineno);
NodeStmt create_attribution_stmt(NodeVarAccess var_access, NodeExpression right, int lineno);
NodeStmt create_func_call_stmt(NodeFuncCall call, int lineno);
NodeStmt create_ifx_stmt(NodeExpression cond, NodeStmt body, int lineno);
NodeStmt create_ifelse_stmt(NodeExpression cond, NodeStmt if_body, NodeStmt else_body, int lineno);
NodeStmt create_iteration_stmt(NodeExpression cond, NodeStmt body, int lineno);
NodeStmt create_return_stmt(NodeExpression expr, int lineno);
NodeStmt create_block_stmt(NodeStmtBlock block, int lineno);
NodeVarAccess create_simple_var_access(char *var_id, int lineno);
NodeVarAccess create_array_access(char *arr_id, NodeExpression idx, int lineno);
NodeFuncCall create_func_call(char *func_id, NodeArgList arg_list, int lineno);
NodeArgList create_arg_list(NodeExpression arg, NodeArgList tail, int lineno);
NodeExpression create_simple_expr_expression(NodeSimpleExpression simple_expr, int lineno);
NodeExpression create_relational_expr_expression(NodeSimpleExpression left, RelationalOperator op, NodeSimpleExpression right, int lineno);
NodeSimpleExpression create_term_simple_expr(NodeTerm term, int lineno);
NodeSimpleExpression create_sign_simple_expr(SignOperator op, NodeTerm right, int lineno);
NodeSimpleExpression create_additive_simple_expr(NodeSimpleExpression left, AdditiveOperator op, NodeTerm right, int lineno);
NodeTerm create_factor_term(NodeFactor factor, int lineno);
NodeTerm create_multiplicative_term(NodeTerm left, MultiplicativeOperator op, NodeFactor right, int lineno);
NodeFactor create_var_access_factor(NodeVarAccess var_access, int lineno);
NodeFactor create_func_call_factor(NodeFuncCall func_call, int lineno);
NodeFactor create_parenthesized_expr_factor(NodeExpression expression, int lineno);
NodeFactor create_literal_factor(NodeLiteral literal, int lineno);
NodeFactor create_not_factor(NodeFactor not_factor, int lineno);
NodeLiteral create_int_literal(int value, int lineno);
NodeLiteral create_float_literal(float value, int lineno);
NodeLiteral create_char_literal(char value, int lineno);
NodeLiteral create_string_literal(char *value, int lineno);
NodeLiteral create_bool_literal(int value, int lineno);


void print_data_type(DataType data_type, int level);
void print_sign_op(SignOperator op, int level);
void print_relation_op(RelationalOperator op, int level);
void print_additive_op(AdditiveOperator op, int level);
void print_multiplicative_op(MultiplicativeOperator op, int level);
void print_program(NodeProgram node, int level);
void print_var_decl_list(NodeVarDeclList node, int level);
void print_var_decl(NodeVarDecl node, int level);
void print_var_id_list(NodeVarIdList node, int level);
void print_var(NodeVarId node, int level);
void print_type_specifier(NodeType node, int level);
void print_primitive_type_specifier(NodeType node, int level);
void print_array_type_specifier(NodeType node, int level);
void print_func_decl_list(NodeFuncDeclList node, int level);
void print_func_decl(NodeFuncDecl node, int level);
void print_func_header(NodeFuncHeader node, int level);
void print_func_param_list(NodeFuncParamList node, int level);
void print_func_param(NodeFuncParam node, int level);
void print_stmt_block(NodeStmtBlock node, int level);
void print_stmt_list(NodeStmtList node, int level);
void print_stmt(NodeStmt node, int level);
void print_attribution_stmt(NodeStmt node, int level);
void print_func_call_stmt(NodeStmt node, int level);
void print_ifx_stmt(NodeStmt node, int level);
void print_ifelse_stmt(NodeStmt node, int level);
void print_iteration_stmt(NodeStmt node, int level);
void print_return_stmt(NodeStmt node, int level);
void print_block_stmt(NodeStmt node, int level);
void print_var_access(NodeVarAccess node, int level);
void print_simple_var_access(NodeVarAccess node, int level);
void print_array_access(NodeVarAccess node, int level);
void print_func_call(NodeFuncCall node, int level);
void print_arg_list(NodeArgList node, int level);
void print_expression(NodeExpression node, int level);
void print_simple_expr_expression(NodeExpression node, int level);
void print_relational_expr_expression(NodeExpression node, int level);
void print_simple_expr(NodeSimpleExpression node, int level);
void print_term_simple_expr(NodeSimpleExpression node, int level);
void print_sign_simple_expr(NodeSimpleExpression node, int level);
void print_additive_simple_expr(NodeSimpleExpression node, int level);
void print_term(NodeTerm node, int level);
void print_factor_term(NodeTerm node, int level);
void print_multiplicative_term(NodeTerm node, int level);
void print_factor(NodeFactor node, int level);
void print_var_access_factor(NodeFactor node, int level);
void print_func_call_factor(NodeFactor node, int level);
void print_parenthesized_expr_factor(NodeFactor node, int level);
void print_literal_factor(NodeFactor node, int level);
void print_not_factor(NodeFactor node, int level);
void print_literal(NodeLiteral node, int level);
void print_int_literal(NodeLiteral node, int level);
void print_float_literal(NodeLiteral node, int level);
void print_char_literal(NodeLiteral node, int level);
void print_string_literal(NodeLiteral node, int level);
void print_bool_literal(NodeLiteral node, int level);

#endif /* SYNTAX_H */
