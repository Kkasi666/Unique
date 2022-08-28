// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is main, a compiler.

#include <iostream>
#include "fileOperate.h"
#include "prjLoader.h"
#include "lexer.h"
#include "parser.h"
#include "constructer.h"
#include "byteWriter.h"

#define CODEMAXLEN 100

int main(int argc, char **argv) {
	/* head */
	// printf("Unique compiler 0.1.3\n");
	std::string fileName, workDir, fileNameBase;
	if(argc==2) {
		workDir = getWorkPath();
		fileName = argv[1];
		if(fileName.substr(fileName.find_last_of('.')+1)!="que") {
			printf("unique.callexe.IsntQueFile Error:\n"\
				"\tthe file '%s' isn't unique file.\n"\
				"\t(Maybe you input fileName isn't add suffix.)\n",fileName.c_str());
			exit(IsntQueFile);
		}
	} else {
		printf("unique.callexe.CallWayWrong Error:\n"\
			"\tthe call way is wrong!\n"\
			"\ttrue way:\n"\
			"\tquec (proName)\n");
		exit(CallWayWrong);
	}

	/* Load project */
	PrjLoader pjler(workDir,CODEMAXLEN);
	pjler.initFile(fileName);
	std::string scode=pjler.getBuffer();
	// printf("[ProjectLoader] Loading complete!\n");
	// printf("code:\n%s\n",scode.c_str());

	/* Lexing */
	Lexer lexer;
	lexer.setCode(scode);
	lexer.lexing();
	TokenList *tls = lexer.getTokenList();
	// printf("[Lexer] Lexing complete!\n");
	// for(int i=0;i<tls->getSize();i++) {
	// 	tls->getToken(i)->show();
	// 	printf("\n");
	// }

	/* Parsing */
	Parser parser;
	parser.setTokenList(tls);
	parser.parsing();
	// printf("[Praser] Prasing complete!\n");
	// parser.showAST();

	/* Constructing */
	Constructer constructer(parser.getAST());
	constructer.constructing();
	// printf("[Constructer] Constructing complete!\n");
	// constructer.showByteCode();

	/* Writing byte code into file */
	fileNameBase = fileName.substr(0,fileName.find_last_of('.'));
	ByteWriter bWriter(workDir,fileNameBase);
	bWriter.setCode(constructer.getCode());
	bWriter.writing();
	// printf("[ByteWriter] Writing complete!\n");

	return 0;
}
