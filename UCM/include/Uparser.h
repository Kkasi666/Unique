// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning tokens to AST.

#ifndef UNIQUE_UCM_PARSER_H_
#define UNIQUE_UCM_PARSER_H_

#include "ASTNode.h"

/*
negative -> SUB NUM
factor -> PTHL expr PTHR | NUM | WORDidn | negative
term -> factor ((ADD|SUB) factor)*
expr -> term ((MUL|DIV) term)*
assign -> WORDidn ASS expr
print -> KEYWORDprint PTHL STR PTHR
statExpr -> (assign | print)*
*/

namespace compiler {

class Parser {
private:
	usint pos;
	StatExprNode *stat;
	enum state {
		ENDING = -1,
		RUNNING
	} parser_state;
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
	Terminal_Pointer getPos();
	Terminal_Pointer number();
	Terminal_Pointer identifier();
	Terminal_Pointer termOp();
	Terminal_Pointer exprOp();

	NegativeNode *negative();
	FactorNode *factor();
	TermNode *term();
	ExprNode *expr();
	AssignNode *assign();
	StatExprNode *statExpr();
public:
	Parser();
	~Parser();
	int parsing();
	void showAST();
	StatExprNode *getAST() const;
};

} // namespace compiler

#endif // UNIQUE_UCM_PARSER_H_