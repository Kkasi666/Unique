#ifndef SGLR_SCM_LEXER_H_
#define SGLR_SCM_LEXER_H_

#include <string>
#include <vector>
#include "share.h"

enum tokenType {
	TNULL=0,
	NUM,
	WORD,
	ADD,
	SUB,
	MUL,
	DIV,
	PTHL, // parentheses left
	PTHR, 
	// BRKL, // bracket left
	// BRKR,
	// BRCL, // Braces left
	// BRCR,
	CMT // comment
};

bool isNumber(char chr);
bool isWord(char chr);
enum tokenType getBraType(const char chr);
enum tokenType getOpType(const char *chr, int row, usint &len);

class Token {
public:
	Token();
	Token(enum tokenType type,const std::string data,int line,int row);
	~Token();
	enum tokenType getType() const;
	std::string getData() const;
	int getLine() const;
	int getRow() const;
	void show();
	int toInt();
private:
	enum tokenType type;
	std::string data;
	usint line,row;
};

class TokenList {
public:
	TokenList();
	~TokenList();

	void addToken(Token t);
	Token *getToken(usint pos) const;
	usint getSize() const;
	enum tokenType getTokenType(usint index) const;
	std::string getTokenData(usint index) const;
private:
	std::vector<Token*> tlist;
};

class Lexer {
private:
	std::string code;
	TokenList *tkl;
	usint pos;
	bool isErr;
public:
	Lexer();
	~Lexer();
	bool isError();
	void setCode(std::string code);
	std::string getCode() const;
	TokenList *getTokenList();
	void lexing();
};

#endif // SGLR_SCM_LEXER_H_