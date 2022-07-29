// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is defined some about file's operate.

#include <direct.h>
#include "fileOperate.h"

std::string getWorkPath() {
	char *buffer = new char[512];
	std::string workPath;
	buffer = getcwd(nullptr, 512);
	workPath = buffer;
	delete[] buffer;
	return workPath;
}