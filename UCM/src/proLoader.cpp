// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is load source code project to compile.

#include "proLoader.h"

ProLoader::ProLoader(std::string workDir, usint maxLen)
	: workDir(workDir), maxLen(maxLen), len(0) {
}

void ProLoader::initFile(std::string fileName) {
	std::ifstream inf(workDir+"/"+fileName+".que",std::ios::in);
	while (len<maxLen) {
		char temC = inf.get();
		if(temC=='\n') {
			len++;
		} else if(temC==(char)EOF) {
			break;
		}
		buffer += temC;
	}
	inf.close();
}

std::string ProLoader::getBuffer() const {
	std::string tempStr=this->buffer;
	return tempStr;
}

ProLoader::~ProLoader() {}