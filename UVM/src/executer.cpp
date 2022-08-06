// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is executing the byte code.

#include "executer.h"

Executer::Executer(std::vector<ByteCode> bCodes)
	: bCodes(bCodes),ip(0) {}
Executer::~Executer() {}

bool Executer::isVstackCode() {
	ByteCode bCode = bCodes.at(ip);
	return bCode.getOpCode()==PUSH || bCode.getOpCode()==POP;
}
bool Executer::isOpCode() {
	ByteCode bCode = bCodes.at(ip);
	return bCode.getOpCode()==ADD || bCode.getOpCode()==SUB ||
	       bCode.getOpCode()==MUL || bCode.getOpCode()==DIV;
}
bool Executer::isVarPoolCode() {
	ByteCode bCode = bCodes.at(ip);
	return bCode.getOpCode()==STORE || bCode.getOpCode()==LOAD;
}

void Executer::visitVstackCode() {
	ByteCode bCode = bCodes.at(ip);
	switch(bCode.getOpCode()) {
		case PUSH: vstack.push(bCode.getOperand()); break;
		case POP:  vstack.pop(); break;
		default: break;
	}
}

void Executer::visitOpCode() {
	ByteCode bCode = bCodes.at(ip);
	int op1,op2;
	switch(bCode.getOpCode()) {
		case ADD: op1 = vstack.top(); vstack.pop();
		          op2 = vstack.top(); vstack.pop();
		          vstack.push(op1 + op2); break;
		case SUB: op1 = vstack.top(); vstack.pop();
		          op2 = vstack.top(); vstack.pop();
		          vstack.push(op1 - op2); break;
		case MUL: op1 = vstack.top(); vstack.pop();
		          op2 = vstack.top(); vstack.pop();
		          vstack.push(op1 * op2); break;
		case DIV: op1 = vstack.top(); vstack.pop();
		          op2 = vstack.top(); vstack.pop();
		          vstack.push(op1 / op2); break;
		default: break;
	}
}
void Executer::visitVarPoolCode() {
	ByteCode bCode = bCodes.at(ip);
	switch(bCode.getOpCode()) {
		case STORE: variablePool.push_back(vstack.top()); vstack.pop(); break;
		case LOAD: vstack.push(variablePool.at(bCode.getOperand())); break;
		default: break;
	}
}
void Executer::executing() {
	ip=0;
	while(bCodes.size()>ip) {
		if(isVstackCode()) {
			visitVstackCode();
		} else if (isOpCode()) {
			visitOpCode();
		} else if (isVarPoolCode()) {
			visitVarPoolCode();
		} else {
			return;
		}
		ip++;
	}
	for(int i=0;i<variablePool.size();i++) {
		printf("[Executer] %d : %d\n",i,variablePool.at(i));
	}
}