// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is defined all kind of AST nodes.

#ifndef UNIQUE_UCM_ASTNODE_H_
#define UNIQUE_UCM_ASTNODE_H_

#include <vector>
#include "def.h"
#include "lexer.h"

namespace compiler {

typedef usint Terminal_Pointer; // just using a token's position instead of the token to save the space.
class ExprNode;

// negative -> SUB NUM
class NegativeNode {
private:
	// Terminal *negSymbol; // It is useless.
	Terminal_Pointer number;
public:
	NegativeNode();
	~NegativeNode();
	void setNumber(Terminal_Pointer num);
	Terminal_Pointer getNumber() const;
	void show();
};


// factor -> PTHL expr PTHR | NUM | IDN | negative
// "operand" include "NUM" and "IDN".
class FactorNode {
private:
	Terminal_Pointer operand;
	ExprNode *expr;
	NegativeNode *negt;
public:
	FactorNode();
	~FactorNode();
	bool exprValid();
	bool negtValid();
	void setOperand(Terminal_Pointer ope);
	void setExprFactor(ExprNode *fac);
	void setNegtFactor(NegativeNode *fac);
	Terminal_Pointer getOperand() const;
	ExprNode *getExprFactor() const;
	NegativeNode *getNegtFactor() const;
	void show();
};

// term -> factor ((ADD|SUB) factor)*
class TermNode {
private:
	std::vector<FactorNode*> factors;
	std::vector<Terminal_Pointer> operators;
public:
	TermNode();
	~TermNode();
	bool factorEmpty();
	bool operatorEmpty();
	usint getFactorSize() const;
	bool onlyFactor();
	void addFactor(FactorNode *factorN);
	void addOperator(Terminal_Pointer ter);
	FactorNode *getFactor(usint index) const;
	Terminal_Pointer getOperator(usint index) const;
	void show();
};

// expr -> term ((MUL|DIV) term)*
class ExprNode {
private:
	std::vector<TermNode*> factors;
	std::vector<Terminal_Pointer> operators;
public:
	ExprNode();
	~ExprNode();
	bool factorEmpty();
	bool operatorEmpty();
	usint getFactorSize() const;
	bool onlyFactor();
	void addFactor(TermNode *termN);
	void addOperator(Terminal_Pointer ter);
	TermNode *getFactor(usint index) const;
	Terminal_Pointer getOperator(usint index) const;
	void show();
};

// assign -> IDN ASS expr
class AssignNode {
private:
	Terminal_Pointer identifier;
	ExprNode *factor;
public:
	AssignNode();
	~AssignNode();
	void setIdentifier(Terminal_Pointer idn);
	void setFactor(ExprNode *exprN);
	Terminal_Pointer getIdentifier() const;
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

} // namespace compiler

#endif // UNIQUE_UCM_ASTNODE_H_