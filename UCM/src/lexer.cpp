#include <iostream>
#include "lexer.h"
#include <vector>

bool isNumber(char chr) {
	return chr>='0' && chr<='9';
}

bool isWord(char chr) {
	return (chr>='a' && chr<='z') || (chr>='A' && chr<='Z');
}

enum tokenType getBraType(const char chr) {
	switch (chr) {
		case '(': return PTHL; break;
		case ')': return PTHR; break;
		// case '[': return BRKL; break;
		// case ']': return BRKR; break;
		// case '{': return MUL; break;
		// case '}': return DIV; break;
		default:  return TNULL; break;
	}
}

enum tokenType getOpType(const char *chr, int row, usint &len) {
	switch (chr[0]) {
		case '+': len=1; return ADD; break;
		case '-': len=1; return SUB; break;
		case '*': len=1; return MUL; break;
		case '/': len=1; return DIV; break;
		default:  return TNULL; break;
	}
}

/* class Token */

Token::Token()
	: type(TNULL), data("\0"), line(0), row(0) {
}
Token::Token(enum tokenType type,const std::string data,int line,int row)
	: type(type), data(data), line(line), row(row) {
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

void Token::show() {
	printf("{ \"type\": %d , \"data\" : \"%s\" }",type,data.c_str());
}

int Token::toInt() {
	bool isNeg=false;
	if(data[0]=='-') {
		isNeg=true;
	}
	int index=1, res=0;
	for(int i=data.size()-1;i>=isNeg;i--) {
		res+=(data[i]-'0')*index;
		index*=10;
	}
	if(isNeg) res*=-1;
	return res;
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
	: code("\0"), tkl(nullptr), pos(0), isErr(false) {
}

Lexer::~Lexer() {
}

bool Lexer::isError() {
	return this->isErr;
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
	isErr=false;
	tkl = new TokenList;
	std::string data;
	usint dataLen=0;
	int line=1,row=1;
	while(pos<code.size()) {
		if(code[pos]=='\n') { // is enter?
			pos++; line++; row=1;
		} else if(code[pos]==' ' || code[pos]=='\t') { // is space or tab?
			pos++; row++;
		} else if (code[pos]=='/' && code[pos]==code[pos+1]) { // is comment?
			for(;pos<code.size() && code[pos]!='\n';pos++);
			pos++; line++; row=1;
		} else if(getOpType(&code[pos],row,dataLen)) { // is oparetor?
			enum tokenType opT = getOpType(&code[pos],row,dataLen);
			if (code[pos]=='-' && row==1 && isNumber(code[++pos])) { // is neg-number?
				data.push_back('-');
				while(isNumber(code[pos]) && pos<code.size()) {
					data.push_back(code[pos++]);
				}
				row+=(data.size()+1);
				tkl->addToken(Token(NUM,data,line,row));
			} else { // is oparetor.
				for(int j=0; j<dataLen; j++) {
					data.push_back(code[pos+j]);
				}
				pos+=dataLen;
				row+=data.size();
				tkl->addToken(Token(opT,data,line,row));
			}
		} else if(isNumber(code[pos])) { // is number
			while(isNumber(code[pos]) && pos<code.size()) {
				data.push_back(code[pos++]);
			}
			row+=data.size();
			tkl->addToken(Token(NUM,data,line,row));
		} else if(isWord(code[pos])) { // is identifier?
			while(isWord(code[pos]) && pos<code.size()) {
				data.push_back(code[pos++]);
			}
			row+=data.size();
			tkl->addToken(Token(WORD,data,line,row));
		} else if(getBraType(code[pos])) { // is braket?
			enum tokenType opT = getBraType(code[pos]);
			data.push_back(code[pos]);
			tkl->addToken(Token(opT,data,line,row));
			pos++;
			row++;
		} else {
			printf("[lexerError]: line: %d row: %d, '%c' isn't define.\n",line,row,code[pos]);
			isErr=true;
			return;
		}
		data.clear();
	}
}