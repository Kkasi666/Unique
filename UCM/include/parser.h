// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning tokens to AST.

#ifndef UNIQUE_UCM_PARSER_H_
#define UNIQUE_UCM_PARSER_H_

#include "ASTNode.h"

/*
negative -> SUB NUM
factor -> PTHL expr PTHR | NUM | IDN | negative
term -> factor ((ADD|SUB) factor)*
expr -> term ((MUL|DIV) term)*
assign -> IDN ASS expr
statExpr -> assign+
*/

namespace compiler {

class Parser {
private:
	TokenList *tkl;
	usint pos;
	StatExprNode *stat;
protected:
	void throwSyntaxWrong(std::string exceptedStr);

	bool isNumTerminal();
	bool isIdnTerminal();
	bool isTermOp();
	bool isExprOp();
	bool isLeftPth();
	bool isRightPth();
	bool isAssignment();

	bool isNegativeStart();
	bool isFactorStart();
	bool isTermStart();
	bool isExprStart();
	bool isAssignStart();
	bool isStatStart();

	void next();
	Terminal *number();
	Terminal *identifier();
	Terminal *termOp();
	Terminal *exprOp();

	NegativeNode *negative();
	FactorNode *factor();
	TermNode *term();
	ExprNode *expr();
	AssignNode *assign();
	StatExprNode *statExpr();
public:
	Parser();
	~Parser();
	void setTokenList(TokenList *tkl);
	int parsing();
	void showAST();
	StatExprNode *getAST() const;
};

} // namespace compiler

#endif // UNIQUE_UCM_PARSER_H_