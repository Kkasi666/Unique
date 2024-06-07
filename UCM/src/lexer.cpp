// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning source code into tokens.

#include "lexer.h"

namespace compiler {

	TokenList tokenList_Main = TokenList();

enum tokenType getBraType(const char chr) {
	switch (chr) {
		case '(': return T_PTHL; break;
		case ')': return T_PTHR; break;
		case '[': return T_BRKL; break;
		case ']': return T_BRKR; break;
		case '{': return T_BRCL; break;
		case '}': return T_BRCR; break;
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
	: type(T_NULL), data("\0"), line(0), row(0), info(0) {}

Token::Token(enum tokenType type,const std::string data, int info)
	: type(type), data(data), line(0), row(0), info(info) {
	if(this->type==T_NUM) {
		int index=1, res=0;
		for(int i=data.size()-1;i>=0;i--) {
			res+=(data[i]-'0')*index;
			index*=10;
		}
		this->info = res;
	}
}

Token::~Token() {}

void Token::setPosition(usint line,usint row) {
	this->line=line;
	this->row=row;
}

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

int Token::getInfo() const {
	return this->info;
}

void Token::show() {
	printf("{ \"linerow\": \"%d:%d\" , \"type\": %d , \"data\" : \"%s\" }\n", line,row,type, data.c_str());
}

/* class TokenList */

TokenList::TokenList() {}

TokenList::~TokenList() {}

void TokenList::addToken(Token t) {
	this->tlist.push_back(t);
}

Token TokenList::getToken(usint pos) const {
	return this->tlist.at(pos);
}

usint TokenList::getSize() const {
	return this->tlist.size();
}

enum tokenType TokenList::getTokenType(usint pos) const {
	return this->tlist[pos].getType();
}

std::string TokenList::getTokenData(usint pos) const{
	return this->tlist[pos].getData();
}

void TokenList::show() {
	for (auto &token : tlist) {
		token.show();
	}
}

/* class Lexer */

Lexer::Lexer()
	: code("\0"), pos(0), line(1), row(1), state(S_NULL) {
}

Lexer::~Lexer() {}

bool Lexer::isOutOfCodeRange() {
	return pos>=code.size();
}

void Lexer::next() {
	if(isOutOfCodeRange()) {
		printf("unique.compiler.lexer.PtrPosOutOfRandge Error:\n"\
		 "\tRead ptr 'pos' is out of range.\n"\
		 "\t(Is %d, but range max only is %d.)\n",pos,code.size());
		exit(PtrPosOutOfRandge);
	}
	this->pos++;
}

void Lexer::addToken(Token t) {
	t.setPosition(line,row);
	tokenList_Main.addToken(t);
	usint tokenStrLen = t.getData().size();
	row+=tokenStrLen;
}

void Lexer::Number() {
	while(isdigit(code[pos]) && !isOutOfCodeRange()) {
		readData.push_back(code[pos]);
		next();
	}
	addToken(Token(T_NUM,readData));
}

void Lexer::Word() {
	while(isalpha(code[pos]) && !isOutOfCodeRange()) {
		readData.push_back(code[pos]);
		next();
	}
	for (int index = 0; index < 4; index++) {
		if(readData==keywordTable[index]) {
			addToken(Token(T_KEYWORD,readData,index));
			return;
		}
	}
	addToken(Token(T_WORD,readData));
}

void Lexer::String() {
	while(!isOutOfCodeRange() && !(code[pos]=='\"')) {
		readData.push_back(code[pos]);
		next();
	}
	addToken(Token(T_STR,readData));
}

void Lexer::Oparetor() {
	enum tokenType opT = getOpType(code[pos]);
	readData.push_back(code[pos]);
	addToken(Token(opT,readData));
	next();
}

void Lexer::AssignSymbol() {
	readData.push_back(code[pos]);
	addToken(Token(T_ASS,readData));
	next();
}

void Lexer::Braket() {
	enum tokenType bkT = getBraType(code[pos]);
	readData.push_back(code[pos]);
	addToken(Token(bkT,readData));
	next();
}

void Lexer::DoubleQuotationMark() {
	readData.push_back(code[pos]);
	addToken(Token(T_DQM,readData));
	next();
}



std::string Lexer::getCode() const {
	return this->code;
}

void Lexer::setCode(std::string code) {
	this->code=code;
}

void Lexer::lexing() {
	while(!isOutOfCodeRange()) {
		if(code[pos]=='\n') { // is enter.
			next(); this->line++; this->row=1;
		} else if(code[pos]==' ' || code[pos]=='\t') { // is space or tab.
			next(); this->row++;
		} else if (code[pos]=='/' && code[pos]==code[pos+1]) { // is comment.
			for(;!isOutOfCodeRange() && code[pos]!='\n';next());
			// go to "is enter" and nextRow.
		} else if (isalpha(code[pos])) { // is word.
			Word();
		} else if (code[pos]=='=') { // is assign symbol.
			AssignSymbol();
		} else if (isdigit(code[pos])) { // is number.
			Number();
		} else if (getOpType(code[pos])) { // is oparetor.
			Oparetor();
		} else if (getBraType(code[pos])) { // is braket.
			Braket();
		} else if (code[pos]=='\"') { // is double quotation mark
			DoubleQuotationMark();
			String();
		} else { // is unexecpted token.
			printf("unique.compiler.lexer.UnexceptedToken Error:\n"\
			 "\tIn line: %d row: %d, unexcepted token '%c'.\n",line,row,code[pos]);
			exit(UnexceptedToken);
		}
		readData.clear();
	}
}

} // namespace compiler