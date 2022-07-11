#ifndef SGLR_SCM_PARSER_H_
#define SGLR_SCM_PARSER_H_

#include "share.h"
#include "ASTNode.h"

/*
G(S):
1. factor -> PTHL expr PTHR | NUM
2. term -> factor ((ADD|SUB) factor)*
3. expr -> term ((MUL|DIV) term)*
4. statExpr -> expr
*/

class Parser {
private:
	TokenList *tkl;
	usint pos;
	StatExprNode *stat;
protected:
	bool isNumTerminal();
	bool isTermOp();
	bool isExprOp();
	bool isLeftPth();
	bool isRightPth();

	bool isFactorStart();
	bool isTermStart();
	bool isExprStart();
	bool isStatStart();

	void next();
	Terminal *number();
	Terminal *termOp();
	Terminal *exprOp();
	FactorNode *factor(); // factor -> PTHL expr PTHR | NUM
	TermNode *term(); // term -> factor ((ADD|SUB) factor)*
	ExprNode *expr(); // expr -> term ((MUL|DIV) term)*
	StatExprNode *statExpr(); // statExpr -> expr
public:
	Parser();
	~Parser();
	void setTokenList(TokenList *tkl);
	int parsing();
	void showAST();
	int getResult();
};

#endif // SGLR_SCM_PARSER_H_