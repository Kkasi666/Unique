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
	printf("Unique compiler 0.1.2\n");
	std::string fileName, workDir;
	if(argc==2) {
		workDir = getWorkPath();
		fileName = argv[1];
	} else if (argc==3) {
		workDir = argv[1];
		fileName = argv[2];
	} else {
		printf("the call way is wrong!\ntrue way:\nquec [workDir] (proName)\n");
		return -1;
	}

	/* Load project */
	PrjLoader pjler(workDir,CODEMAXLEN);
	pjler.initFile(fileName);
	std::string scode=pjler.getBuffer();
	printf("[ProjectLoader] Loading complete!\n");
	// printf("code:\n%s\n",scode.c_str());

	/* Lexing */
	Lexer lexer;
	lexer.setCode(scode);
	lexer.lexing();
	TokenList *tls = lexer.getTokenList();
	if(lexer.isError()) {return -2;}
	printf("[Lexer] Lexing complete!\n");
	/*
	for(int i=0;i<tls->getSize();i++) {
		printf("{ type: %d, data: %s }\n",tls->getTokenType(i), tls->getTokenData(i).c_str());
	}
	*/

	/* Parsing */
	Parser parser;
	parser.setTokenList(tls);
	parser.parsing();
	printf("[Praser] Prasing complete!\n");
	// parser.showAST();

	/* Constructing */
	Constructer constructer(parser.getAST());
	constructer.constructing();
	printf("[Constructer] Constructing complete!\n");
	// constructer.showByteCode();

	/* Writing byte code into file */
	ByteWriter bWriter(workDir,fileName);
	bWriter.setCode(constructer.getCode());
	bWriter.writing();
	printf("[ByteWriter] Writing complete!\n");

	return 0;
}
