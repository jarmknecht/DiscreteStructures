//
//  Token.h
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Token_h
#define Token_h

#include <string>
#include <iostream>
#include <map>
#include <sstream>


enum TokenType {
   COMMA, //token is a ,
   PERIOD, //token is a .
   Q_MARK, //token is a ?
   LEFT_PAREN, //token is a (
   RIGHT_PAREN, //token is a )
   COLON, //token is a :
   COLON_DASH, //token is a :-
   MULTIPLY, //token is *
   ADD, //token is +
   SCHEMES, //token is keyword Schemes
   FACTS, //token is keyword Facts
   RULES, //token is keyword Rules
   QUERIES, //token is keyword Queries
   ID, //token is a letter followed by 0 or more chars|nums
   STRING, //token starts with ' and ends with ' with anything in between
   COMMENT, //token starts with # or #| for multiline comments ends with # or |#
   WHITESPACE, //just a place holder does not become a token
   UNDEFINED, //token is not recognized as part of the languange
   MYEOF //token is the EOF
};

class Token {
   public:
      Token();
      Token(TokenType type, std::string data, int startLine);
      ~Token();
      std::string GetType();
      std::string GetValue() const;
      int GetStartingLine() const;
   
   private:
      TokenType typeOfToken;
      std::string tokenValue;
      int lineTokenStarts;
      std::map<TokenType, std::string> tokenTypes = {{COMMA, "COMMA"}, {PERIOD, "PERIOD"}, {Q_MARK, "Q_MARK"}, {LEFT_PAREN, "LEFT_PAREN"}, {RIGHT_PAREN, "RIGHT_PAREN"}, {COLON, "COLON"}, {COLON_DASH, "COLON_DASH"}, {MULTIPLY, "MULTIPLY"}, {ADD, "ADD"}, {SCHEMES, "SCHEMES"}, {FACTS, "FACTS"}, {RULES, "RULES"}, {QUERIES, "QUERIES"}, {ID, "ID"}, {STRING, "STRING"}, {COMMENT, "COMMENT"}, {WHITESPACE, "WHITESPACE"}, {UNDEFINED, "UNDEFINED"}, {MYEOF, "EOF"}};
};


#endif /* Token_h */
