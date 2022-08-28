// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This define opCodes.

#ifndef UNIQUE_UCM_BYTECODE_
#define UNIQUE_UCM_BYTECODE_

namespace compiler {

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

} // namespace compiler

#endif // UNIQUE_UCM_BYTECODE_