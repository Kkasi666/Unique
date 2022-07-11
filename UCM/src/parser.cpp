#include <iostream>
#include <string>
#include "share.h"
#include "lexer.h"
#include "parser.h"

Parser::Parser()
	: tkl(nullptr), pos(0), stat(nullptr) {
}

Parser::~Parser() {
}

bool Parser::Parser::isNumTerminal() {
	return tkl->getToken(pos)->getType()==NUM;
}

bool Parser::isTermOp() {
	if(pos>=tkl->getSize()) return false;
	return (tkl->getToken(pos)->getType()==MUL || tkl->getToken(pos)->getType()==DIV);
}
bool Parser::isExprOp() {
	if(pos>=tkl->getSize()) return false;
	return (tkl->getToken(pos)->getType()==ADD || tkl->getToken(pos)->getType()==SUB);
}

bool Parser::isLeftPth() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==PTHL;
}

bool Parser::isRightPth() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==PTHR;
}

bool Parser::isFactorStart() {
	return (isLeftPth() || isNumTerminal());
}

bool Parser::isTermStart() {
	return isFactorStart();
}
bool Parser::isExprStart() {
	return isTermStart();
}
bool Parser::isStatStart() {
	return isExprStart();
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

// factor -> PTHL expr PTHR | NUM
FactorNode *Parser::factor() {
	if(!isFactorStart()) {
		return 0x0; // [ParserError]factor error.
	}
	FactorNode *fac=new FactorNode;
	if(isNumTerminal()) {
		fac->setNumber(number());
	} else if(isLeftPth()) {
		next();// jump out the braket
		if(isExprStart()) {
			fac->setFactor(expr());
		} else {
			delete fac;
			printf("[ParserError]factor error, had '(', but hadn't expr.");
			return 0x0;
		}
		if(isRightPth()) {
			next(); // jump out the braket
		} else {
			delete fac;
			printf("[ParserError]factor error, had expr, but hadn't ')'.");
			return 0x0;
		}
	}
	return fac;
}

// term -> factor (MSYM factor)*
TermNode *Parser::term() {
	if(!isTermStart()) {
		printf("[ParserError]make TermNode error.\n");
		return 0x0;
	} else {
		TermNode *ter= new TermNode;
		ter->addFactor(factor());
		while(isTermOp()) {
			ter->addOperator(termOp());
			ter->addFactor(factor());
		}
		return ter;
	}
}

// expr -> term (ASYM term)*
ExprNode *Parser::expr() {
	if(!isTermStart()) {
		printf("[ParserError]make ExprNode error.\n");
		return 0x0;
	} else {
		ExprNode *expr= new ExprNode;
		expr->addFactor(term());
		while(isExprOp()) {
			expr->addOperator(exprOp());
			expr->addFactor(term());
			
		}
		return expr;
	}
}

// statExpr -> expr
StatExprNode *Parser::statExpr() {
	if(!isStatStart()) {
		printf("[ParserError]statExpr error.\n");
		return 0x0;
	}
	StatExprNode *stat = new StatExprNode;
	stat->setFactor(expr());
	return stat;
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

int Parser::getResult() {
	if(stat) return stat->getResult();
	else return 0;
}