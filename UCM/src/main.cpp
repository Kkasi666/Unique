#include <iostream>
#include "fileAPI.h"
#include "proLoader.h"
#include "lexer.h"
#include "parser.h"
#include "builder.h"
#include "byteWriter.h"


#define CODEMAXLEN 100

int main(int argc, char **argv) {
	printf("Unique 0.1.1 (build for mingw32)\n");
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

	ProLoader pler(workDir,CODEMAXLEN);
	pler.initFile(fileName);
	std::string scode=pler.getBuffer();
	// printf("code:\n%s\n",scode.c_str());

	Lexer lexer;
	lexer.setCode(scode);
	lexer.lexing();
	TokenList *tls = lexer.getTokenList();
	if(lexer.isError()) {return -2;}
	/*
	for(int i=0;i<tls->getSize();i++) {
		printf("{ type: %d, data: %s }\n",tls->getTokenType(i), tls->getTokenData(i).c_str());
	}
	*/

	Parser parser;
	parser.setTokenList(tls);
	parser.parsing();
	// parser.showAST();

	Builder builder(parser.getAST());
	builder.building();
	// builder.showByteCode();

	ByteWriter bWriter(workDir,fileName);
	bWriter.setCode(builder.getCode());
	bWriter.writing();

	printf("[Compiler] Compilation finish!\n");

	return 0;
}
