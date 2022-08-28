// Copyright 2022 Source Speace Studio
// License(GPLv3.0)
// Author: Kkasi
// This is turning source code into tokens.

#ifndef UNIQUE_UCM_LEXER_H_
#define UNIQUE_UCM_LEXER_H_

#include <string>
#include <vector>
#include "def.h"

enum tokenType {
	T_NULL=0,
	T_NUM,
	T_WORD,
	T_ASS,
	T_ADD,
	T_SUB,
	T_MUL,
	T_DIV,
	T_PTHL, // parentheses left
	T_PTHR, 
	T_BRKL, // bracket left
	T_BRKR,
	T_BRCL, // Braces left
	T_BRCR
};

enum tokenType getBraType(const char chr);
enum tokenType getOpType(const char chr);

class Token {
private:
	enum tokenType type;
	std::string data;
	usint line,row;
	int value;
public:
	Token();
	Token(enum tokenType type,const std::string data,int line,int row);
	~Token();
	enum tokenType getType() const;
	std::string getData() const;
	int getLine() const;
	int getRow() const;
	int getValue() const;
	void show();
};

class TokenList {
private:
	std::vector<Token*> tlist;
public:
	TokenList();
	~TokenList();

	void addToken(Token t);
	Token *getToken(usint pos) const;
	usint getSize() const;
	enum tokenType getTokenType(usint index) const;
	std::string getTokenData(usint index) const;
};

class Lexer {
private:
	std::string code;
	std::string readData;
	TokenList *tkl;
	usint pos, line, row;
protected:
	void next();
	void nextRow(int step=1);
	void nextLine();
	void Word();
	void Number();
	void Oparetor();
	void AssignSymbol();
	void Braket();
public:
	Lexer();
	~Lexer();
	void setCode(std::string code);
	std::string getCode() const;
	TokenList *getTokenList();
	void lexing();
};

#endif // UNIQUE_UCM_LEXER_H_