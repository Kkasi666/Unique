// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This define hasOperand.

#include "byteCode.h"

namespace virtualMachine {

int hasOperand[] {
	[NOP]   = 0,
	[PUSH]  = 1,
	[POP]   = 0,
	[ADD]   = 0,
	[SUB]   = 0,
	[MUL]   = 0,
	[DIV]   = 0,
	[LOAD]  = 1,
	[STORE] = 1
};

ByteCode::ByteCode() {}

ByteCode::ByteCode(opCode opc,int operand)
	: oc(opc), operand(operand) {}

ByteCode::~ByteCode() {}

opCode ByteCode::getOpCode() const {
	return this->oc;
}

int ByteCode::getOperand() const {
	return this->operand;
}

} // namespace virtualMachine