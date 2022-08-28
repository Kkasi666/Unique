// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning source code into tokens.

#include "lexer.h"

namespace compiler {

enum tokenType getBraType(const char chr) {
	switch (chr) {
		case '(': return T_PTHL; break;
		case ')': return T_PTHR; break;
		case '[': return T_BRKL; break;
		case ']': return T_BRKR; break;
		case '{': return T_MUL; break;
		case '}': return T_DIV; break;
		default:  return T_NULL; break;
	}
}

enum tokenType getOpType(const char chr) {
	switch (chr) {
		case '+': return T_ADD; break;
		case '-': return T_SUB; break;
		case '*': return T_MUL; break;
		case '/': return T_DIV; break;
		default:  return T_NULL; break;
	}
}

/* class Token */

Token::Token()
	: type(T_NULL), data("\0"), line(0), row(0), value(0) {}

Token::Token(enum tokenType type,const std::string data,int line,int row)
	: type(type), data(data), line(line), row(row),value(0) {
	if(this->type==T_NUM) {
		int index=1, res=0;
		for(int i=data.size()-1;i>=0;i--) {
			res+=(data[i]-'0')*index;
			index*=10;
		}
		this->value = res;
	}
}

Token::~Token() {}

enum tokenType Token::getType() const {
	return this->type;
}

std::string Token::getData() const {
	return this->data;
}

int Token::getLine() const {
	return this->line;
}

int Token::getRow() const {
	return this->row;
}

int Token::getValue() const {
	return this->value;
}

void Token::show() {
	printf("{ %d:%d \"type\": %d , \"data\" : \"%s\" }", line,row,type, data.c_str());
}

/* class TokenList */

TokenList::TokenList() {
}

TokenList::~TokenList() {
	for(usint i=0;this->tlist.size();i++) {
		delete this->tlist[i];
	}
}

void TokenList::addToken(Token t) {
	Token *tokenPtr= new Token(t);
	this->tlist.push_back(tokenPtr);
}

Token *TokenList::getToken(usint pos) const {
	return this->tlist.at(pos);
}

usint TokenList::getSize() const {
	return this->tlist.size();
}

enum tokenType TokenList::getTokenType(usint pos) const {
	return this->tlist[pos]->getType();
}

std::string TokenList::getTokenData(usint pos) const{
	return this->tlist[pos]->getData();
}

/* class Lexer */

Lexer::Lexer()
	: code("\0"), tkl(nullptr), pos(0), line(1), row(1) {
}

Lexer::~Lexer() {}

void Lexer::next() {
	if(pos>=code.size()) {
		printf("unique.compiler.lexer.PtrPosOutOfRandge Error:\n"\
		 "\tRead ptr 'pos' is out of range.\n"\
		 "\t(Is %d, but range max only is %d.)\n",pos,code.size());
		exit(PtrPosOutOfRandge);
	}
	this->pos++;
}

void Lexer::nextRow(int step) {
	this->row+=step;
}


void Lexer::nextLine() {
	this->line++;
	this->row=1;
}

void Lexer::Word() {
	while(isalpha(code[pos]) && pos<code.size()) {
		readData.push_back(code[pos]);
		next();
	}
	tkl->addToken(Token(T_WORD,readData,line,row));
	nextRow(readData.size());
}

void Lexer::Number() {
	while(isdigit(code[pos]) && pos<code.size()) {
		readData.push_back(code[pos]);
		next();
	}
	tkl->addToken(Token(T_NUM,readData,line,row));
	nextRow(readData.size());
}

void Lexer::Oparetor() {
	enum tokenType opT = getOpType(code[pos]);
	readData.push_back(code[pos]);
	tkl->addToken(Token(opT,readData,line,row));
	next();
}

void Lexer::AssignSymbol() {
	readData.push_back(code[pos]);
	tkl->addToken(Token(T_ASS,readData,line,row));
	next();
	nextRow();
}

void Lexer::Braket() {
	enum tokenType opT = getBraType(code[pos]);
	readData.push_back(code[pos]);
	tkl->addToken(Token(opT,readData,line,row));
	next();
	nextRow();
}

std::string Lexer::getCode() const {
	return this->code;
}

void Lexer::setCode(std::string code) {
	this->code=code;
}

TokenList *Lexer::getTokenList() {
	return this->tkl;
}

void Lexer::lexing() {
	tkl = new TokenList;
	while(pos<code.size()) {
		if(code[pos]=='\n') { // is enter.
			next();
			nextLine();
		} else if(code[pos]==' ' || code[pos]=='\t') { // is space or tab.
			next();
			nextRow();
		} else if (code[pos]=='/' && code[pos]==code[pos+1]) { // is comment.
			for(;pos<code.size() && code[pos]!='\n';next());
			// go to "is enter" and nextLine.
		} else if(isalpha(code[pos])) { // is word.
			Word();
		} else if(code[pos]=='=') { // is assign symbol.
			AssignSymbol();
		} else if(isdigit(code[pos])) { // is number.
			Number();
		} else if(getOpType(code[pos])) { // is oparetor.
			Oparetor();
		} else if(getBraType(code[pos])) { // is braket.
			Braket();
		} else { // is unexecpted token.
			printf("unique.compiler.lexer.UnexceptedToken Error:\n"\
			 "\tIn line: %d row: %d, unexcepted token '%c'.\n",line,row,code[pos]);
			exit(UnexceptedToken);
		}
		readData.clear();
	}
}

} // namespace compiler