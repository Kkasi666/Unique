// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This define opCodes.

#ifndef UNIQUE_UCM_BYTECODE_
#define UNIQUE_UCM_BYTECODE_

namespace virtualMachine {

enum opCode {
	NOP   = 0x0000,
	PUSH  = 0x0001,
	POP   = 0x0002,
	ADD   = 0x0003,
	SUB   = 0x0004,
	MUL   = 0x0005,
	DIV   = 0x0006,
	LOAD  = 0x0007, // load [ip]
	STORE = 0x0008 // store [ip]
};

class ByteCode {
private:
	opCode oc;
	int operand;
protected:
public:
	ByteCode();
	ByteCode(opCode oc,int operand);
	~ByteCode();
	opCode getOpCode() const;
	int getOperand() const;
};

} // namespace virtualMachine

#endif // UNIQUE_UCM_BYTECODE_