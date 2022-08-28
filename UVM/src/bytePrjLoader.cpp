// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is load source code project to executing.

#include "bytePrjLoader.h"

namespace virtualMachine {

BytePrjLoader::BytePrjLoader(std::string workDir)
	: workDir(workDir) {
}

BytePrjLoader::~BytePrjLoader() {}

void BytePrjLoader::initFile(std::string fileName) {
	std::ifstream inf(workDir+"/"+fileName,std::ios::in);
	if(!inf) {
		printf("can't open the file '%s'.\n",fileName.c_str());
		exit(-1);
		return;
	}
	char getHead[6];
	inf.read((char*)&getHead,6);
	char head[] = {0x3C, 0x2B, 0x1C, 0x2E, 0x3C, 0x0E};
	for (int i=0;i<6;i++) {
		if (getHead[i] != head[i]) {
			printf("the file isn't unique byte code file.");
			return;
		}
	}
	char bCode[2] = {0,0};
	while (inf.read(bCode,sizeof(bCode))) {
		if(*bCode==(char)EOF || inf.bad()) {
			break;
		} else {
			ByteCode bc((opCode)bCode[0],bCode[1]);
			bCodes.push_back(bc);
		}
	}
	inf.close();
}

std::vector<ByteCode> BytePrjLoader::getCodes() const {
	return this->bCodes;
}

} // namespace virtualMachine