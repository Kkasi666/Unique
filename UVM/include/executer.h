// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is executing the byte code.

#ifndef UNIQUE_UCM_EXECUTER_H_
#define UNIQUE_UCM_EXECUTER_H_

#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include "def.h"
#include "byteCode.h"

class Executer {
private:
	std::vector<ByteCode> bCodes;
	std::stack<int> vstack;
	std::vector<int> variablePool;
	usint ip;
protected:
	bool isVstackCode();
	bool isOpCode();
	bool isVarPoolCode();
	void visitVstackCode();
	void visitOpCode();
	void visitVarPoolCode();
public:
	Executer(std::vector<ByteCode> bCodes);
	~Executer();
	void executing();
};

#endif // UNIQUE_UCM_EXECUTER_H_