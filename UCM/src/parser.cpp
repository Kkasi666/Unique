// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning tokens to AST.

#include <string>
#include "parser.h"

namespace compiler {

Parser::Parser()
	: tkl(nullptr), pos(0), stat(nullptr) {
}

Parser::~Parser() {
}

void Parser::throwSyntaxWrong(std::string exceptedStr) {
	if(pos>=tkl->getSize()) pos=tkl->getSize()-1;
	printf("unique.compiler.parser.SyntaxWrong Error:\n"\
	"\tIn %d:%d, excpted %s, before token'%s'\n"\
	,tkl->getToken(pos)->getLine()\
	,tkl->getToken(pos)->getRow()\
	,exceptedStr.c_str()\
	,tkl->getToken(pos)->getData().c_str());
	exit(SyntaxWrong);
}

bool Parser::isNumTerminal() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_NUM;
}

bool Parser::isIdnTerminal() {
	if(pos>=tkl->getSize()) return false;
	return tkl->getToken(pos)->getType()==T_WORD;
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
	return tkl->getToken(pos);
}

Terminal *Parser::identifier() {
	if(!isIdnTerminal()) {
		return 0x0;
	}
	return tkl->getToken(pos);
}

Terminal *Parser::termOp() {
	if(!isTermOp()) {
		return 0x0;
	}
	return tkl->getToken(pos);
}

Terminal *Parser::exprOp() {
	if(!isExprOp()) {
		return 0x0;
	}
	return tkl->getToken(pos);
}

// factor -> PTHL expr PTHR | NUM | IDN
FactorNode *Parser::factor() {
	if(!isFactorStart()) {
		return 0x0; // [ParserError]factor error.
	} else {
		FactorNode *fac=new FactorNode;
		if(isNumTerminal()) {
			fac->setOperand(number());
			next();
		} else if(isIdnTerminal()) {
			fac->setOperand(identifier());
			next();
		} else if(isLeftPth()) {
			next();// skip "("
			if(isExprStart()) {
				fac->setFactor(expr());
			} else {
				delete fac;
				throwSyntaxWrong("'(' | number | word");
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
		throwSyntaxWrong("'(' | number | word");
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
		throwSyntaxWrong("'(' | number | word");
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
		AssignNode * ass = new AssignNode;
		ass->setIdentifier(identifier());
		next();
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

} // namespace compiler