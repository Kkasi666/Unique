#ifndef SGLR_SCM_ASTNODE_H_
#define SGLR_SCM_ASTNODE_H_

#include "lexer.h"
#include <vector>

typedef Token Terminal;
class ExprNode;

// factor -> PTHL expr PTHR | NUM
class FactorNode {
private:
	Terminal *number;
	ExprNode *factor;
public:
	FactorNode();
	~FactorNode();
	void setNumber(Terminal *num);
	void setFactor(ExprNode *fac);
	Terminal *getNumber() const;
	ExprNode *getFactor() const;
	void show();
	int getResult();
};

// term -> factor ((ADD|SUB) factor)*
class TermNode {
private:
	std::vector<FactorNode*> factors;
	std::vector<Terminal*> operators;
public:
	TermNode();
	~TermNode();
	void addFactor(FactorNode *factorN);
	void addOperator(Terminal *ter);
	int termOpMake(usint index, int a, int b);
	void show();
	int getResult();
};

// expr -> term ((MUL|DIV) term)*
class ExprNode {
private:
	std::vector<TermNode*> factors;
	std::vector<Terminal*> operators;
public:
	ExprNode();
	~ExprNode();
	void addFactor(TermNode *termN);
	void addOperator(Terminal *ter);
	int exprOpMake(usint index, int a, int b);
	void show();
	int getResult();
};

// statExpr -> expr
class StatExprNode {
private:
	ExprNode *factor;
public:
	StatExprNode();
	~StatExprNode();
	void setFactor(ExprNode *fac);
	ExprNode *getFactor() const;
	void show();
	int getResult();
};

#endif // SGLR_SCM_ASTNODE_H_