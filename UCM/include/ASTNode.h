// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is defined ast node.

#ifndef UNIQUE_UCM_ASTNODE_H_
#define UNIQUE_UCM_ASTNODE_H_

#include <vector>
#include "def.h"
#include "lexer.h"

typedef Token Terminal;
class ExprNode;

// factor -> PTHL expr PTHR | NUM | IDN (NUM + IDN = operand)
class FactorNode {
private:
	Terminal *operand;
	ExprNode *factor;
public:
	FactorNode();
	~FactorNode();
	void setOperand(Terminal *ope);
	void setFactor(ExprNode *fac);
	Terminal *getOperand() const;
	ExprNode *getFactor() const;
	void show();
};

// term -> factor ((ADD|SUB) factor)*
class TermNode {
private:
	std::vector<FactorNode*> factors;
	std::vector<Terminal*> operators;
public:
	TermNode();
	~TermNode();
	bool factorEmpty();
	bool operatorEmpty();
	usint getFactorSize() const;
	bool onlyFactor();
	void addFactor(FactorNode *factorN);
	void addOperator(Terminal *ter);
	FactorNode *getFactor(usint index) const;
	Terminal *getOperator(usint index) const;
	void show();
};

// expr -> term ((MUL|DIV) term)*
class ExprNode {
private:
	std::vector<TermNode*> factors;
	std::vector<Terminal*> operators;
public:
	ExprNode();
	~ExprNode();
	bool factorEmpty();
	bool operatorEmpty();
	usint getFactorSize() const;
	bool onlyFactor();
	void addFactor(TermNode *termN);
	void addOperator(Terminal *ter);
	TermNode *getFactor(usint index) const;
	Terminal *getOperator(usint index) const;
	void show();
};

// assign -> IDN ASS expr
class AssignNode {
private:
	Terminal *identifier;
	ExprNode *factor;
public:
	AssignNode();
	~AssignNode();
	void setIdentifier(Terminal *idn);
	void setFactor(ExprNode *exprN);
	Terminal *getIdentifier() const;
	ExprNode *getFactor() const;
	void show();
};

// statExpr -> assign+
class StatExprNode {
private:
	std::vector<AssignNode*> factors;
public:
	StatExprNode();
	~StatExprNode();
	usint getFactorSize() const;
	void addFactor(AssignNode *fac);
	AssignNode *getFactor(usint index) const;
	void show();
};

#endif // UNIQUE_UCM_ASTNODE_H_