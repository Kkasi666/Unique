// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This can make ast to byteCode.

#ifndef UNIQUE_UCM_BUILDER_
#define UNIQUE_UCM_BUILDER_

#include <string>
#include <vector>
#include <map>
#include "def.h"
#include "ASTNode.h"
#include "byteCode.h"

class Builder {
private:
	StatExprNode *stat;
	std::map<std::string,usint> variableTable;
	usint idCur;
	std::vector<byte> byteCode;
protected:
	void makeByteCode(opCode op, int operand);
	void visitTermOp(Terminal *terl);
	void visitExprOp(Terminal *terl);
	void visitFactorNode(FactorNode *fac);
	void visitTermNode(TermNode *ter);
	void visitExprNode(ExprNode *expr);
	void visitAssignNode(AssignNode *ass);
	void visitStatExprNode(StatExprNode *stat);
public:
	Builder();
	Builder(StatExprNode *stat);
	~Builder();
	void building();
	std::vector<byte> getCode() const;
	void showByteCode();
};

#endif // UNIQUE_UCM_BUILDER_