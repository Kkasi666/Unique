// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This define hasOperand.

#include "byteCode.h"

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