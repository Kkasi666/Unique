// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This define something.

#ifndef UNIQUE_UCM_DEF_H_
#define UNIQUE_UCM_DEF_H_

#define usint unsigned int
#define byte char

enum errType {
	CallWayWrong=1,
	IsntQueFile,
	CannotOpenFile,

	PtrPosOutOfRandge,
	UnexceptedToken,
	SyntaxWrong
};
#endif // UNIQUE_UCM_DEF_H_