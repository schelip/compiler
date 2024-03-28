#ifndef SEMANTHIC_H
#define SEMANTHIC_H

#include "table.h"
#include "syntax.h"

void check_prog(NodeProgram prog);
void check_var_decl_list(NodeVarDeclList var_decl_list);
void check_func_decl_list(NodeFuncDeclList func_decl_list);
void check_func_decl(NodeFuncDecl func_decl);
void check_func_param(NodeFuncParam func_param);
void check_stmt_block(NodeStmtBlock block);
void check_var_decl(NodeVarDecl var_decl);
void check_var(NodeVarId var_id, NodeType type);
void check_stmt_list(NodeStmtList stmt_list);
void check_stmt(NodeStmt stmt);
void check_atrribution_stmt(NodeStmt stmt);
void check_func_call(NodeFuncCall func_call);
void check_comparison_ifx_stmt(NodeStmt stmt);
void check_comparison_ifelse_stmt(NodeStmt stmt);
void check_iteration_stmt(NodeStmt stmt);
void check_ret_stmt(NodeStmt stmt);
void check_expr(NodeExpression expr);
void check_simple_expr(NodeSimpleExpression expr);
void check_term(NodeTerm term);
void check_factor(NodeFactor factor);
void check_var_access(NodeVarAccess var_access);
void check_not_factor(NodeFactor factor);

#endif /* SEMANTHIC_H */