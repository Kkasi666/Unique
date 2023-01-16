// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This can turn AST into byteCode.

#ifndef UNIQUE_UCM_CONSTRUCTER_
#define UNIQUE_UCM_CONSTRUCTER_

#include <string>
#include <vector>
#include <map>
#include "ASTNode.h"
#include "byteCode.h"

namespace compiler {

class Constructer {
private:
	StatExprNode *stat;
	std::map<std::string,usint> variableTable;
	usint idCur;
	std::vector<byte> byteCode;
protected:
	void makeByteCode(opCode op, int operand);
	void visitTermOp(Terminal *terl);
	void visitExprOp(Terminal *terl);
	void visitNegativeNode(NegativeNode *negt);
	void visitFactorNode(FactorNode *fac);
	void visitTermNode(TermNode *ter);
	void visitExprNode(ExprNode *expr);
	void visitAssignNode(AssignNode *ass);
	void visitStatExprNode(StatExprNode *stat);
public:
	Constructer();
	Constructer(StatExprNode *stat);
	~Constructer();
	void constructing();
	std::vector<byte> getCode() const;
	void showByteCode();
};

} // namespace compiler

#endif // UNIQUE_UCM_CONSTRUCTER_