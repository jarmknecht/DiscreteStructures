//
//  Lexer.cpp
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Lexer.h"

#include <cctype>

Lexer::Lexer() {
   this->currentChar = '%'; //initialized to unknown char
   this->currentLine = 0;
}

Lexer::~Lexer() {
   for (unsigned int i = 0; i < this->tokens.size(); i++) {
      delete tokens.at(i);
      tokens.at(i) = NULL;
   }
}

int Lexer::GetCurrentLine() const {
   return this->currentLine;
}

bool Lexer::ReadFile(std::string fileName) {
   std::ifstream inFS;
   
   this->currentLine = 1;
   
   inFS.open(fileName);
   
   if (!inFS.is_open()) {
      std::cout << "Cannot open file with the name " << fileName << "." << std::endl; //prints out error message if can't read file
      
      return false; //will return false and quit the program if it can't read file
   }
   
   while (!inFS.eof()) {
      this->currentChar = inFS.get();
      if (inFS.good()) { //if the char could be read into c then continue onto a different state my Finite State Automaton
         Token* tmp = GenerateToken(inFS);
         if (tmp != NULL) {
            this->tokens.push_back(tmp);
         }
      }
   }
   this->tokens.push_back(new Token(MYEOF, "", GetCurrentLine()));
   
   inFS.close();
   
   return true;
}

Token* Lexer::BlockComment(std::ifstream& inFS) {
   std::stringstream toString;
   int startLine = GetCurrentLine(); //this will keep track of where string started and allow currentLine to move around while reading input
   
   toString << "#" << this->currentChar; //both # and |(currentChar) were already read by get
   
   while (true) {
      this->currentChar = inFS.get();
      if (inFS.eof()) { //if currentChar is equal to EOF undefined token
         return new Token(UNDEFINED, toString.str(), startLine);
      }
      if (this->currentChar == '|' && inFS.peek() == '#') { //end of block comment found
         toString << this->currentChar; //adds | to toString
         this->currentChar = inFS.get();
         toString << this->currentChar; //adds # to toString
         return new Token(COMMENT, toString.str(), startLine);
      }
      if (this->currentChar == '\n') {
         this->currentLine++;
      }
      toString << this->currentChar;
   }
   
}

Token* Lexer::LineComment(std::ifstream& inFS) {
   std::stringstream toString;
   int startLine = GetCurrentLine(); //this will keep track of where string started and allow currentLine to move around while reading input
   
   toString << this->currentChar; //puts # into stream
   
   while(true) {
      this->currentChar = inFS.get();
      if (inFS.eof()) { //end of file reached comment is done
         break;
      }
      if (this->currentChar == '\n') {
         this->currentLine++; //line ends so does comment line increase line count and break
         break;
      }
      toString << this->currentChar;
   }
   return new Token(COMMENT, toString.str(), startLine);
}

Token* Lexer::ObtainString(std::ifstream& inFS) {
   std::stringstream toString;
   int startLine = GetCurrentLine(); //this will keep track of where string started and allow currentLine to move around while reading input
   
   toString << "'"; //add the opening ' found from the automaton above
   
   while (true) {
      this->currentChar = inFS.get();
      if (inFS.eof()) { //if currentChar is equal to EOF undefined token
         return new Token(UNDEFINED, toString.str(), startLine);
      }
      
      if (this->currentChar == '\'') {
         if (inFS.peek() == '\'') { //shows ' is an apostrophe
            toString << this->currentChar;
            this->currentChar = inFS.get();
         }
         else { //show ' is end of string and not an apostrophe
            toString << this->currentChar;
            return new Token(STRING, toString.str(), startLine);
         }
      }
      if (this->currentChar == '\n') {
         this->currentLine++;
      }
      toString << this->currentChar;
   }
}

Token* Lexer::CheckIfKeywordOrID(std::ifstream& inFS) {
   std::stringstream toString;
   
   while (isalnum(inFS.peek())) {
      this->currentChar = inFS.get();
      toString << this->currentChar;
   }
   
   if (this->tokenKeywords.find(toString.str()) != this->tokenKeywords.end()) {
      return new Token(this->tokenKeywords[toString.str()], toString.str(), GetCurrentLine());
   }
   return new Token(ID, toString.str(), GetCurrentLine());
}

std::string Lexer::ToString() const {
   std::stringstream toString;
   
   for (unsigned int i = 0; i < this->tokens.size(); i++) {
      toString << "(" << this->tokens.at(i)->GetType() << ",\"" << this->tokens.at(i)->GetValue() << "\"," << this->tokens.at(i)->GetStartingLine() << ")" << std::endl;
   }
   toString << "Total Tokens = " << tokens.size() << std::endl;
   
   return toString.str();
}

Token* Lexer::GenerateToken(std::ifstream& inFS) {
   switch (this->currentChar) { //make a function that just looks at currentChar
      case ',':
         return new Token(COMMA, ",", GetCurrentLine());
         
      case '.':
         return new Token(PERIOD, ".", GetCurrentLine());
         
      case '?':
         return new Token(Q_MARK, "?", GetCurrentLine());
         
      case '(':
         return new Token(LEFT_PAREN, "(", GetCurrentLine());
         
      case ')':
         return new Token(RIGHT_PAREN, ")", GetCurrentLine());
         
      case ':': //this will look at : and :-
         return MakeColonToken(inFS);
         
      case '*':
         return new Token(MULTIPLY, "*", GetCurrentLine());
         
      case '+':
         return new Token(ADD, "+", GetCurrentLine());
         
      case '\'':
         return ObtainString(inFS);
         
      case '#':
         return MakeCommentToken(inFS);
         
      case ' ':
         //Found whitespace ignore and move onto next char
         return NULL; //not a token
         
      case '\n':
         this->currentLine++;
         return NULL; //not a token
         
      default:
         return MakeKeywordOrIDToken(inFS);
   }
}

Token* Lexer::MakeColonToken(std::ifstream& inFS) {
   if (inFS.peek() == '-') {
      this->currentChar = inFS.get();
      return new Token(COLON_DASH, ":-", GetCurrentLine());
   }
   else {
      return new Token(COLON, ":", GetCurrentLine());
   }
}

Token* Lexer::MakeCommentToken(std::ifstream& inFS) {
   if (inFS.peek() == '|') { //means comment may be a block comment or undefined
      this->currentChar = inFS.get();
      return BlockComment(inFS);
   }
   else { //it must be a single line comment or undefined
      return LineComment(inFS);
   }
}

Token* Lexer::MakeKeywordOrIDToken(std::ifstream& inFS) { //makes keyword or ID or undefined if nothing else
   if (!isalpha(this->currentChar)) {
      std::stringstream toString;
      toString << this->currentChar;
      return new Token (UNDEFINED, toString.str(), GetCurrentLine());
   }
   else {
      inFS.putback(this->currentChar); //put char back into inFS to be read to a toString
      return CheckIfKeywordOrID(inFS);
   }
}

std::vector<Token*> Lexer::GetVector() const {
   return this->tokens;
}
