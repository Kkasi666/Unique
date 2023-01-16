// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is defined all kind of AST nodes.

#include "ASTNode.h"

namespace compiler {

/* class NegativeNode */

NegativeNode::NegativeNode()
	: number(nullptr) {
}

NegativeNode::~NegativeNode() {
	if(number) delete number;
}

void NegativeNode::setNumber(Terminal *num) {
	this->number = num;
}

Terminal *NegativeNode::getNumber() const {
	return this->number;
}

void NegativeNode::show() {
	if(this->number) {
		printf("{ \"Negative\": { \"number\": ");
		number->show();
		printf(" } }");
	}
}

/* class FactorNode */

FactorNode::FactorNode()
	: operand(nullptr),expr(nullptr),negt(nullptr) {
}

FactorNode::~FactorNode() {
	if(operand) delete operand;
	if(expr) delete expr;
	if(negt) delete negt;
}

bool FactorNode::exprValid() {
	return expr;
}
bool FactorNode::negtValid() {
	return negt;
}

void FactorNode::setOperand(Terminal *ope) {
	this->operand=ope;
}

void FactorNode::setExprFactor(ExprNode *fac) {
	this->expr=fac;
}

void FactorNode::setNegtFactor(NegativeNode *fac) {
	this->negt=fac;
}

Terminal *FactorNode::getOperand() const {
	return this->operand;
}

ExprNode *FactorNode::getExprFactor() const {
	return this->expr;
}
NegativeNode *FactorNode::getNegtFactor() const {
	return this->negt;
}

void FactorNode::show() {
	if(operand) {
		printf("{ \"Factor\": { \"operand\": ");
		operand->show(); // token
		printf(" } }");
	} else {
		printf("{ \"Factor\": { ");
		if(expr) {
			expr->show();
		}else if(negt) {
			negt->show();
		}
		printf(" } }");
	}
}

/* class TermNode */

TermNode::TermNode() {}

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

bool TermNode::factorEmpty() {
	return factors.empty();
}

bool TermNode::operatorEmpty() {
	return operators.empty();
}

usint TermNode::getFactorSize() const {
	return factors.size();
}

bool TermNode::onlyFactor() {
	return factors.size()==1;
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

FactorNode *TermNode::getFactor(usint index) const {
	return factors.at(index);
}

Terminal *TermNode::getOperator(usint index) const{
	return operators.at(index);
}

void TermNode::show() {
	if(factors.empty()){ return; }
	printf("{ \"Term\": { \"factors\": [ ");
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
	printf(" } }");
}

/* class ExprNode */

ExprNode::ExprNode() {}

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

bool ExprNode::factorEmpty() {
	return factors.empty();
}

bool ExprNode::operatorEmpty() {
	return operators.empty();
}

usint ExprNode::getFactorSize() const {
	return factors.size();
}

bool ExprNode::onlyFactor() {
	return factors.size()==1;
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

TermNode *ExprNode::getFactor(usint index) const {
	return factors.at(index);
}

Terminal *ExprNode::getOperator(usint index) const{
	return operators.at(index);
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

/* class AssignNode */

AssignNode::AssignNode()
	: factor(nullptr) {
}

AssignNode::~AssignNode() {}

void AssignNode::setIdentifier(Terminal *idn) {
	this->identifier=idn;
}

void AssignNode::setFactor(ExprNode *exprN) {
	this->factor=exprN;
}

Terminal *AssignNode::getIdentifier() const {
	return this->identifier;
}

ExprNode *AssignNode::getFactor() const {
	return this->factor;
}

void AssignNode::show() {
	if(identifier) {
		printf("{ \"Assign\": { \"identifier\": ");
		identifier->show();
		printf(", ");
		factor->show();
		printf(" } }");
	}
}

/* class StatExprNode */

StatExprNode::StatExprNode() {}

StatExprNode::~StatExprNode() {
	if(!factors.empty()) {
		for(int i=0; i<factors.size(); i++) {
			delete factors.at(i);
		}
	}
}

usint StatExprNode::getFactorSize() const {
	return factors.size();
}

void StatExprNode::addFactor(AssignNode *fac) {
	factors.push_back(fac);
}

AssignNode *StatExprNode::getFactor(usint index) const {
	if(!factors.empty()) {
		return factors.at(index);
	} else {
		return 0x0;
	}
	
}

void StatExprNode::show() {
	if(!factors.empty()) {
		printf("{ \"StatExpr\": { \"factors\": [ ");
		for(int i=0; i<factors.size(); i++) {
			if(factors.at(i)!=0x0) {
				factors.at(i)->show();
				printf(", ");
			}
		}
		printf("\b\b  \b\b ] } }\n");
	}
}

} // namespace compiler