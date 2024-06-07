// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning tokens to AST.

#include <string>
#include "Uparser.h"


namespace compiler {

Parser::Parser()
	: pos(0), stat(nullptr),parser_state(RUNNING) {
}

Parser::~Parser() {
}

void Parser::throwSyntaxWrong(std::string exceptedStr) {
	if(pos>=tokenList_Main.getSize()) pos=pos-1;
	printf("unique.compiler.parser.SyntaxWrong Error:\n"\
	"\tIn %d:%d, excpted %s, before token'%s'\n"        \
	,tokenList_Main.getToken(getPos()).getLine()                       \
	,tokenList_Main.getToken(getPos()).getRow()                        \
	,exceptedStr.c_str()                                \
	,tokenList_Main.getToken(getPos()).getData().c_str()               );
	exit(SyntaxWrong);
}

bool Parser::isNumTerminal() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find num terminal)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_NUM;
}

bool Parser::isIdnTerminal() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find idn terminal)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_WORD;
}

bool Parser::isTermOp() {
	if(parser_state==ENDING) {
		//printf("OOR");
		//throwSyntaxWrong("OOR(find term op)");
		return false;
	}
	return (tokenList_Main.getToken(getPos()).getType()==T_MUL || tokenList_Main.getToken(getPos()).getType()==T_DIV);
}

bool Parser::isExprOp() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find exp op)");
		return false;
	}
	return (tokenList_Main.getToken(getPos()).getType()==T_ADD || tokenList_Main.getToken(getPos()).getType()==T_SUB);
}

bool Parser::isLeftPth() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find left pth)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_PTHL;
}

bool Parser::isRightPth() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find right pth)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_PTHR;
}

bool Parser::isAssignment() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find ass)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_ASS;
}

bool Parser::isNegativeStart() {
	if(parser_state==ENDING) {
		//throwSyntaxWrong("OOR(find neg)");
		return false;
	}
	return tokenList_Main.getToken(getPos()).getType()==T_SUB;
}

bool Parser::isFactorStart() {
	return (isNumTerminal() || isIdnTerminal() || isLeftPth() || isNegativeStart());
}

bool Parser::isTermStart() {
	return isFactorStart();
}

bool Parser::isExprStart() {
	return isTermStart();
}

bool Parser::isAssignStart() {
	return isIdnTerminal();
}

bool Parser::isStatStart() {
	return isAssignStart();
}

void Parser::next() {
	pos = pos + 1;
	if(pos>=tokenList_Main.getSize()) {
		//printf("next OOR! pos[%d]\n",pos);
		parser_state = ENDING;
	}
}

Terminal_Pointer Parser::getPos() {
	if(pos>=tokenList_Main.getSize()) {
		printf("get OOR! pos[%d]\n",pos);
		parser_state = ENDING;
		return -1;
	}
	return pos;
}

Terminal_Pointer Parser::number() {
	if(!isNumTerminal()) {
		throwSyntaxWrong("couldn't find num");
		return 0x0;
	}
	return getPos();
}

Terminal_Pointer Parser::identifier() {
	if(!isIdnTerminal()) {
		throwSyntaxWrong("couldn't find idn");
		return 0x0;
	}
	return getPos();
}

Terminal_Pointer Parser::termOp() {
	if(!isTermOp()) {
		return 0x0;
	}
	return getPos();
}

Terminal_Pointer Parser::exprOp() {
	if(!isExprOp()) {
		return 0x0;
	}
	return getPos();
}

NegativeNode *Parser::negative() {
	if(!isNegativeStart()) {return 0x0;}
	next();
	NegativeNode *negt = new NegativeNode;
	negt->setNumber(number());
	next();
	return negt;
}

// factor -> PTHL expr PTHR | NUM | IDN | negative
FactorNode *Parser::factor() {
	if(!isFactorStart()) {
		return 0x0; // [ParserError]factor error.
	} else {
		FactorNode *fac=new FactorNode;
		if(isNumTerminal()) {
			fac->setOperand(number()); next();
		} else if(isIdnTerminal()) {
			fac->setOperand(identifier()); next();
		} else if(isNegativeStart()) {
			fac->setNegtFactor(negative());
		} else if(isLeftPth()) {
			next();// skip "("
			if(isExprStart()) {
				fac->setExprFactor(expr());
			} else {
				delete fac;
				throwSyntaxWrong("{factor} '(' | number | word | neg-number");
				return 0x0;
			}
			if(isRightPth()) {
				next(); // skip ")"
			} else {
				delete fac;
				throwSyntaxWrong("')'");
				return 0x0;
			}
		}
		return fac;
	}
}

// term -> factor ((MUL|DIV) factor)*
TermNode *Parser::term() {
	if(!isTermStart()) {
		throwSyntaxWrong(" {term} '(' | number | word | neg-number");
		return 0x0;
	} else {
		TermNode *ter = new TermNode;
		ter->addFactor(factor());
		while(isTermOp()) {
			ter->addOperator(termOp());
			next();
			ter->addFactor(factor());
		}
		return ter;
	}
}

// expr -> term ((ADD|SUB) term)*
ExprNode *Parser::expr() {
	if(!isExprStart()) {
		throwSyntaxWrong(" {expr} '(' | number | word | neg-number");
		return 0x0;
	} else {
		ExprNode *expr = new ExprNode;
		expr->addFactor(term());
		while(isExprOp()) {
			expr->addOperator(exprOp());
			next();
			expr->addFactor(term());		
		}
		return expr;
	}
}

// assign -> IDN ASS expr
AssignNode *Parser::assign() {
	if(!isAssignStart()) {
		throwSyntaxWrong("a word");
		return 0x0;
	} else {
		AssignNode *ass = new AssignNode;
		ass->setIdentifier(identifier()); next();
		if(isAssignment()) {
			next(); // skip "="
		} else {
			throwSyntaxWrong("'='");
			return 0x0;
		}
		ass->setFactor(expr());
		return ass;
	}
}


// statExpr -> assign+
StatExprNode *Parser::statExpr() {
	if(!isStatStart()) {
		throwSyntaxWrong("a word");
		return 0x0;
	} else {
		StatExprNode *stat = new StatExprNode;
		while (isAssignStart()) {
			stat->addFactor(assign());
		}
		return stat;
	}
}

int Parser::parsing() {
	stat=statExpr();
	return 0;
}

void Parser::showAST() {
	if(stat) {
		stat->show();
	}
}

StatExprNode *Parser::getAST() const {
	return this->stat;
}

} // namespace compiler