//
//  Token.cpp
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Token.h"

Token::Token() {
   this->typeOfToken = UNDEFINED;
   this->tokenValue = "";
   this->lineTokenStarts = 0;
   
}

Token::Token(TokenType type, std::string data, int startLine) {
   this->typeOfToken = type;
   this->tokenValue = data;
   this->lineTokenStarts = startLine;
}

Token::~Token() {
   
}

std::string Token::GetType() { //maps the current token to the correct string
   
   if(this->tokenTypes.find(this->typeOfToken) != this->tokenTypes.end()) {
      return this->tokenTypes[this->typeOfToken];
   }
   return "NOT A KNOWN TOKEN";
}

std::string Token::GetValue() const {
   return this->tokenValue;
}

int Token::GetStartingLine() const {
   return this->lineTokenStarts;
}
