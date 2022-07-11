#include <iostream>
#include "share.h"
#include "lexer.h"
#include "parser.h"

int main()
{
	printf("Unique 0.0.4 (2022.7.10 11:20)\nInput 'q' to quit this program\n");

	while (true)
	{
		char code[75];
		printf("Plsace input the code:");
		scanf("%s",code);
		if(code[0]=='q') break;
		Lexer lexer;
		lexer.setCode(code);
		lexer.lexing();
		TokenList *tls = lexer.getTokenList();
		if(lexer.isError()) {continue;}
		for(int i=0;i<tls->getSize();i++) {
			printf("{ type: %d, data: %s }\n",tls->getTokenType(i), tls->getTokenData(i).c_str());
		}
		Parser parser;
		parser.setTokenList(tls);
		parser.parsing();
		//parser.showAST(); // the AST is to ugly, so ...
		int res=parser.getResult();
		printf("[result] %d\n",res);
	}
	return 0;
}