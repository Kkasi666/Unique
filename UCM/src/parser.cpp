// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is make tokens to ast.

#include <iostream>
#include <string>
#include "parser.h"

Parser::Parser()
	: tkl(nullptr), pos(0), stat(nullptr) {
}

Parser::~Parser() {
}

bool Parser::isNumTerminal() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_NUM;
}

bool Parser::isIdnTerminal() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_IDN;
}

bool Parser::isTermOp() {
	if(pos>=tkl->getSize()) return false;
	return (tkl->getToken(pos)->getType()==T_MUL || tkl->getToken(pos)->getType()==T_DIV);
}
bool Parser::isExprOp() {
	if(pos>=tkl->getSize()) return false;
	return (tkl->getToken(pos)->getType()==T_ADD || tkl->getToken(pos)->getType()==T_SUB);
}

bool Parser::isLeftPth() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_PTHL;
}

bool Parser::isRightPth() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_PTHR;
}

bool Parser::isAssignment() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_ASS;
}

bool Parser::isFactorStart() {
	return (isLeftPth() || isNumTerminal() || isIdnTerminal());
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
	if(pos>=tkl->getSize()) return;
	pos++;
}

Terminal *Parser::number() {
	if(!isNumTerminal()) {
		return 0x0;
	}
	return tkl->getToken(pos++);
}

Terminal *Parser::identifier() {
	if(!isIdnTerminal()) {
		return 0x0;
	}
	return tkl->getToken(pos++);
}

Terminal *Parser::termOp() {
	if(!isTermOp()) {
		return 0x0;
	}
	return tkl->getToken(pos++);
}
Terminal *Parser::exprOp() {
	if(!isExprOp()) {
		return 0x0;
	}
	return tkl->getToken(pos++);
}

// factor -> PTHL expr PTHR | NUM | IDN
FactorNode *Parser::factor() {
	if(!isFactorStart()) {
		return 0x0; // [ParserError]factor error.
	} else {
		FactorNode *fac=new FactorNode;
		if(isNumTerminal()) {
			fac->setOperand(number());
		} else if(isIdnTerminal()) {
			fac->setOperand(identifier());
		} else if(isLeftPth()) {
			next();// skip "("
			if(isExprStart()) {
				fac->setFactor(expr());
			} else {
				delete fac;
				printf("[ParserError]factor error, had '(', but hadn't expr.");
				return 0x0;
			}
			if(isRightPth()) {
				next(); // skip ")"
			} else {
				delete fac;
				printf("[ParserError]factor error, had expr, but hadn't ')'.");
				return 0x0;
			}
		}
		return fac;
	}
}

// term -> factor ((MUL|DIV) factor)*
TermNode *Parser::term() {
	if(!isTermStart()) {
		printf("[ParserError]make TermNode error, you use '%s'.\n", tkl->getToken(pos)->getData().c_str());
		return 0x0;
	} else {
		TermNode *ter = new TermNode;
		ter->addFactor(factor());
		while(isTermOp()) {
			ter->addOperator(termOp());
			ter->addFactor(factor());
		}
		return ter;
	}
}

// expr -> term ((ADD|SUB) term)*
ExprNode *Parser::expr() {
	if(!isTermStart()) {
		printf("[ParserError]make ExprNode error.\n");
		return 0x0;
	} else {
		ExprNode *expr = new ExprNode;
		expr->addFactor(term());
		while(isExprOp()) {
			expr->addOperator(exprOp());
			expr->addFactor(term());
			
		}
		return expr;
	}
}

// assign -> IDN ASS expr
AssignNode *Parser::assign() {
	if(!isAssignStart()) {
		printf("[ParserError]make AssignNode error.\n");
		return 0x0;
	} else {
		AssignNode * ass = new AssignNode;
		ass->setIdentifier(identifier());
		if(isAssignment()) {
			next(); // skip "="
		} else {
			printf("[ParserError]Assign error, expect '=', you use '%s'.\n",ass->getIdentifier()->getData().c_str());
			return 0x0;
		}
		ass->setFactor(expr());
		return ass;
	}
}


// statExpr -> assign+
StatExprNode *Parser::statExpr() {
	if(!isStatStart()) {
		printf("[ParserError]statExpr error.\n");
		return 0x0;
	} else {
		StatExprNode *stat = new StatExprNode;
		while (isAssignStart()) {
			stat->addFactor(assign());
		}
		return stat;
	}
}

void Parser::setTokenList(TokenList *tkl) {
	this->tkl=tkl;
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