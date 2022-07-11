#include <malloc.h>
#include "ASTNode.h"

/* class FactorNode */

FactorNode::FactorNode()
	: number(nullptr), factor(nullptr) {
}

FactorNode::~FactorNode() {
	if(number) delete number;
	if(factor) delete factor;
}

void FactorNode::setNumber(Terminal *num) {
	this->number=num;
}

void FactorNode::setFactor(ExprNode *fac) {
	this->factor=fac;
}

Terminal *FactorNode::getNumber() const {
	return this->number;
}

ExprNode *FactorNode::getFactor() const {
	return this->factor;
}

void FactorNode::show() {
	if(number) {
		printf("{ \"Factor\": { \"number\": "); // token
		number->show();
		printf(" } }");
	} else if(factor) {
		printf("{ \"Factor\": { ");
		factor->show();
		printf(" } }");
	}
}

int FactorNode::getResult() {
	if(number) {
		return number->toInt();
	} else if(factor) {
		return factor->getResult();
	} else {
		return 0;
	}
}

/* class TermNode */

TermNode::TermNode() {
}

TermNode::~TermNode() {
	if(!factors.empty()){
		for(int i=0; i<factors.size(); i++) {
			delete factors.at(i);
		}
	}
	if(!operators.empty()){
		for(int i=0; i<operators.size(); i++) {
			delete operators.at(i);
		}
	}
}

void TermNode::addFactor(FactorNode *factorN) {
	if(factorN) {
		this->factors.push_back(factorN);
	}
}

void TermNode::addOperator(Terminal *ter) {
	if(ter) {
		this->operators.push_back(ter);
	}
}

int TermNode::termOpMake(usint index, int a, int b) {
	switch (operators[index]->getType()) {
		case MUL: return a*b; break;
		case DIV: return a/b; break;
		default: return 0; break;
	}
}

void TermNode::show() {
	if(factors.empty()){ return; }
	printf("\"Term\": { \"factors\": [ ");
	for(int i=0;i<factors.size();i++) {
		factors.at(i)->show();
		printf(", ");
	}
	printf("\b\b  \b\b]");
	if(!operators.empty()) {
		printf(" , \"operators\": [ ");
		for(int i=0;i<operators.size();i++) {
			operators.at(i)->show();
			printf(", ");
		}
		printf("\b\b  \b\b]");
	}
	printf(" }");
}

int TermNode::getResult() {
	if(!factors.empty()) {
		if(factors.size()==1) {
			return factors[0]->getResult();
		} else if(!operators.empty()) {
			int a=factors[0]->getResult();
			int b=factors[1]->getResult();
			int res=termOpMake(0,a,b);
			for(int i=2;i<factors.size();i++) {
				a=factors[i]->getResult();
				res=termOpMake(i-1,res,a);
			}
			return res;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

/* class ExprNode */

ExprNode::ExprNode() {
}

ExprNode::~ExprNode() {
	if(!factors.empty()){
		for(int i=0; i<factors.size(); i++) {
			delete factors.at(i);
		}
	}
	if(!operators.empty()){
		for(int i=0; i<operators.size(); i++) {
			delete operators.at(i);
		}
	}
}

void ExprNode::addFactor(TermNode *termN) {
	if(termN) {
		this->factors.push_back(termN);
	}
}

void ExprNode::addOperator(Terminal *ter) {
	if(ter) {
		this->operators.push_back(ter);
	}
}

int ExprNode::exprOpMake(usint index, int a, int b) {
	switch (operators[index]->getType()) {
		case ADD: return a+b; break;
		case SUB: return a-b; break;
		default: return 0; break;
	}
}

void   ExprNode::show() {
	if(factors.empty()){ return; }
	printf("\"Expr\": { \"factors\": [ ");
	for(int i=0;i<factors.size();i++) {
		factors.at(i)->show();
		printf(", ");
	}
	printf("\b\b  \b\b] ");
	if(!operators.empty()) {
		printf(" , \"operators\": [ ");
		for(int i=0;i<operators.size();i++) {
			operators.at(i)->show();
			printf(", ");
		}
		printf("\b\b  \b\b] ");
	}
	printf(" }");
}

int ExprNode::getResult() {
	if(!factors.empty()) {
		if(factors.size()==1) {
			return factors[0]->getResult();
		} else if(!operators.empty()) {
			int a=factors[0]->getResult();
			int b=factors[1]->getResult();
			int res=exprOpMake(0,a,b);
			for(int i=2;i<factors.size();i++) {
				a=factors[i]->getResult();
				res=exprOpMake(i-1,res,a);
			}
			return res;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

/* class StatExprNode */

StatExprNode::StatExprNode()
	: factor(nullptr) {
}

StatExprNode::~StatExprNode() {
	if(factor) delete factor;
}

void StatExprNode::setFactor(ExprNode *fac) {
	if(fac) {
		this->factor=fac;
	}
}
ExprNode *StatExprNode::getFactor() const {
	return this->factor;
}

void StatExprNode::show() {
	if(factor) {
		printf("{ \"StatExpr\": { ");
		factor->show();
		printf(" } }\n");
	}
}

int StatExprNode::getResult() {
	if(factor) {
		return factor->getResult();
	} else {
		return 0;
	}
}