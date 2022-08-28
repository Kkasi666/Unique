// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is load source code project to compile.

#include "prjLoader.h"

PrjLoader::PrjLoader(std::string workDir, usint maxLen)
	: workDir(workDir), maxLen(maxLen), len(0) {
}

void PrjLoader::initFile(std::string fileName) {
	std::ifstream inf(workDir+"/"+fileName,std::ios::in);
	if(!inf) {
		printf("unique.compiler.projectLoader.CannotOpenFile Error:\n"\
			"\tcan't open the file '%s'.\n",fileName.c_str());
		exit(CannotOpenFile);
	}
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

std::string PrjLoader::getBuffer() const {
	std::string tempStr=this->buffer;
	return tempStr;
}

PrjLoader::~PrjLoader() {}