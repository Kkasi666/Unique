#include "builder.h"

Builder::Builder()
: stat(nullptr), idCur(0) {}

Builder::Builder(StatExprNode *stat)
	: stat(stat), idCur(0) {}

Builder::~Builder() {}

void Builder::makeByteCode(command com, int operand) {
	byteCode.push_back(com);
	byteCode.push_back(operand);
}

void Builder::visitTermOp(Terminal *terl) {
	switch (terl->getType()) {
		case T_MUL: makeByteCode(MUL, 0x0000); break;
		case T_DIV:  makeByteCode(DIV, 0x0000); break;
		default: makeByteCode(NOP,0x0000); break;
	}
}
void Builder::visitExprOp(Terminal *terl) {
	switch (terl->getType()) {
		case T_ADD: makeByteCode(ADD, 0x0000); break;
		case T_SUB:  makeByteCode(SUB, 0x0000); break;
		default: makeByteCode(NOP,0x0000); break;
	}
}

void Builder::visitFactorNode(FactorNode *fac) {
	if(fac->getOperand()) {
		if(fac->getOperand()->getType()==T_NUM) {
			int value = fac->getOperand()->getValue();
			makeByteCode(PUSH, value);
		} else if (fac->getOperand()->getType()==T_IDN) {
			usint vId = variableTable[fac->getOperand()->getData()];
			makeByteCode(LOAD, vId);
		}
		
	} else if(fac->getFactor()) {
		visitExprNode(fac->getFactor());
	} else {
		return; // error
	}
}
void Builder::visitTermNode(TermNode *ter) {
		if(!ter->factorEmpty()) {
		if(ter->onlyFactor()) {
			visitFactorNode(ter->getFactor(0));
		} else if(!ter->operatorEmpty()) {
			visitFactorNode(ter->getFactor(0));
			visitFactorNode(ter->getFactor(1));
			visitTermOp(ter->getOperator(0));
			for(int i=2;i<ter->getFactorSize();i++) {
				visitFactorNode(ter->getFactor(i));
				visitTermOp(ter->getOperator(i-1));
			}
		} else {
			return; // error
		}
	} else {
		return; // error
	}
}
void Builder::visitExprNode(ExprNode *expr) {
	if(!expr->factorEmpty()) {
		if(expr->onlyFactor()) {
			visitTermNode(expr->getFactor(0));
		} else if(!expr->operatorEmpty()) {
			visitTermNode(expr->getFactor(0));
			visitTermNode(expr->getFactor(1));
			visitExprOp(expr->getOperator(0));
			for(int i=2;i<expr->getFactorSize();i++) {
				visitTermNode(expr->getFactor(i));
				visitExprOp(expr->getOperator(i-1));
			}
		} else {
			return; // error
		}
	} else {
		return; // error
	}
}

void Builder::visitAssignNode(AssignNode *ass) {
	if(ass->getFactor()) { // make exprNode
		visitExprNode(ass->getFactor());
		if(ass->getIdentifier()) { // 
			std::string id=ass->getIdentifier()->getData();
			if (!variableTable.count(id)) {
				variableTable[id]=idCur++;
			}
			makeByteCode(STORE, variableTable[id]);
		}
	}
	
}
void Builder::visitStatExprNode(StatExprNode *stat) {
	if(stat) {
		for(int i=0;i<stat->getFactorSize();i++) {
			visitAssignNode(stat->getFactor(i));
		}
	}
}

void Builder::building() {
	visitStatExprNode(stat);
}

std::vector<byte> Builder::getCode() const {
	return this->byteCode;
}

void Builder::showByteCode() {
	printf("\n");
	for(int i=0; i<byteCode.size(); i+=2) {
		printf("%d %d\n",byteCode.at(i),byteCode.at(i+1));
	}
}