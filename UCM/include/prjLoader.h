// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is load source code project to compile.

#ifndef UNIQUE_UCM_PROLOADER_H_
#define UNIQUE_UCM_PROLOADER_H_

#include <string>
#include <fstream>
#include "def.h"

class PrjLoader {
private:
	std::string workDir;
	std::string buffer;
	usint maxLen;
	usint len;
public:
	PrjLoader(std::string workDir, usint maxLen);
	void initFile(std::string fileName);
	std::string getBuffer() const;
	~PrjLoader();
};

#endif // UNIQUE_UCM_PROLOADER_H_