// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is load byte code project to executing.

#ifndef UNIQUE_UCM_BYTEPRJLOADER_H_
#define UNIQUE_UCM_BYTEPRJLOADER_H_

#include <string>
#include <vector>
#include <fstream>
#include "def.h"
#include "byteCode.h"

class BytePrjLoader {
private:
	std::string workDir;
	std::vector<ByteCode> bCodes;
public:
	BytePrjLoader(std::string workDir);
	~BytePrjLoader();
	void initFile(std::string fileName);
	std::vector<ByteCode> getCodes() const;
};

#endif // UNIQUE_UCM_BYTEPRJLOADER_H_