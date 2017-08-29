//
//  Lexer.h
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Lexer_h
#define Lexer_h

#include "Token.h"
#include <string>
#include <vector>
#include <fstream>
#include <map>

class Lexer {
   public:
      Lexer();
      ~Lexer();
      bool ReadFile(std::string fileName);
      int GetCurrentLine() const;
      Token* CheckIfKeywordOrID(std::ifstream& inFS);
      Token* ObtainString(std::ifstream& inFS);
      Token* LineComment(std::ifstream& inFS);
      Token* BlockComment(std::ifstream& inFS);
      std::string ToString() const;
   
   private:
      std::vector<Token*> tokens;
      std::map<std::string, TokenType> tokenKeywords = {{"Schemes", SCHEMES}, {"Facts", FACTS}, {"Rules", RULES}, {"Queries", QUERIES}}; //maps keywords to strings
      char currentChar;
      int currentLine;
      Token* GenerateToken(std::ifstream& inFS);
      Token* MakeColonToken (std::ifstream& inFS);
      Token* MakeCommentToken(std::ifstream& inFS);
      Token* MakeKeywordOrIDToken(std::ifstream& inFS);
};

#endif /* Lexer_h */
