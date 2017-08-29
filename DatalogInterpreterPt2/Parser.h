//
//  Parser.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Parser_h
#define Parser_h


#include "Token.h"
#include "datalogProgram.h"
#include "headPredicate.h"
#include "predicate.h"
#include "parameter.h"
#include "parameterString.h"
#include "parameterID.h"
#include "expressions.h"
#include "scheme.h"
#include "Database.h"

#include <deque>
#include <exception>

class Parser {
      
   public:
      Parser();
      Parser(std::vector<Token*> tokens);
      ~Parser();
      
      void ParseInput();
      bool CheckToken(std::string expected);
      HeadPredicate* parseHeadPred();
      std::vector<std::string> parseIds();
      std::vector<Predicate*> parsePreds();
      Predicate* parsePredicate();
      std::vector<Parameter*> parseParameters();
      Parameter* parseParam();
      Parameter* parseExpression();
      Scheme* parseScheme();
      std::vector<Scheme*>  parseSchemes();
      Fact* parseFact();
      std::vector<Fact*> parseFacts();
      std::vector<Rule*> parseRules();
      Rule* parseRule();
      std::vector<std::string> parseStrings();
      std::vector<Query*> parseQueries();
      Query* parseQuery();
   
   
   private:
      std::deque<Token*> qtokens;
   
};


#endif /* Parser_h */
