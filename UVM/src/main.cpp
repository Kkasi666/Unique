// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is main, a VM.

#include <iostream>
#include "fileOperate.h"
#include "bytePrjLoader.h"
#include "executer.h"

int main(int argc, char **argv) {
	/* head */
	printf("Unique VM 0.1.1\n");
	std::string fileName, workDir;
	if(argc==2) {
		workDir = getWorkPath();
		fileName = argv[1];
	} else if (argc==3) {
		workDir = argv[1];
		fileName = argv[2];
	} else {
		printf("the call way is wrong!\ntrue way:\nquev [workDir] (proName)\n");
		return -1;
	}

	/* Load byte project */
	BytePrjLoader pler(workDir);
	pler.initFile(fileName);
	printf("[ByteProjectLoader] Loading complete!\n");
	// printf("code:\n%s\n",scode.c_str());

	/* executing */
	Executer executer(pler.getCodes());
	executer.executing();
	printf("[Executer] Executing complete!\n");

	return 0;
}
