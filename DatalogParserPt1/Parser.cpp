//
//  Parser.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Parser.h"

Parser::Parser() {
   
}

Parser::~Parser() {
   
}

Parser::Parser(std::vector<Token*> tokens) {
   for (unsigned int i = 0; i < tokens.size(); i++) {
      if (tokens.at(i)->GetType() == "COMMENT") {
         //do not add to the queue
      }
      else if (tokens.at(i)->GetType() == "UNDEFINED") {
         std::stringstream ss;
         ss << "(" << tokens.at(i)->GetType() << ",\"" << tokens.at(i)->GetValue() << "\"," << tokens.at(i)->GetStartingLine() << ")";
         throw (ss.str());
      }
      else {
         this->qtokens.push_back(tokens.at(i));
      }
   }
}

bool Parser::CheckToken(std::string expected) {
   Token* given = this->qtokens.front();
   
   if (given->GetType() != expected) {
      std::stringstream ss;
      ss << "(" << given->GetType() << ",\"" << given->GetValue() << "\"," << given->GetStartingLine() << ")";
      throw (ss.str());
   }
   return true;
}

void Parser::ParseInput() {
   DataLog myLog;
   
   CheckToken("SCHEMES");
   this->qtokens.pop_front();
   CheckToken("COLON");
   this->qtokens.pop_front();
   std::vector<Scheme*> schemes = parseSchemes();
   myLog.AddSchemes(schemes);
   
   CheckToken("FACTS");
   this->qtokens.pop_front();
   CheckToken("COLON");
   this->qtokens.pop_front();
   std::vector<Fact*> facts = parseFacts();
   myLog.AddFacts(facts);
   
   
   CheckToken("RULES");
   this->qtokens.pop_front();
   CheckToken("COLON");
   this->qtokens.pop_front();
   std::vector<Rule*> rules = parseRules();
   myLog.AddRules(rules);
   
   CheckToken("QUERIES");
   this->qtokens.pop_front();
   CheckToken("COLON");
   this->qtokens.pop_front();
   std::vector<Query*> queries = parseQueries();
   myLog.AddQueries(queries);
   
   
   CheckToken("EOF");
   std::cout << myLog.toString();
}

std::vector<Query*> Parser::parseQueries() {
   std::vector<Query*> queries;
   
   do {
      queries.push_back(parseQuery());
   } while (this->qtokens.front()->GetType() != "EOF");
   
   return queries;
}

Query* Parser::parseQuery() {
   Predicate* queryPred = parsePredicate();
   CheckToken("Q_MARK");
   this->qtokens.pop_front();
   
   return new Query(queryPred);
}

std::vector<Rule*> Parser::parseRules() {
   std::vector<Rule*> rules;
   
   do {
      rules.push_back(parseRule());
   } while (this->qtokens.front()->GetType() != "QUERIES");
   
   return rules;
}

Rule* Parser::parseRule() {
   HeadPredicate* headPred = parseHeadPred();
   CheckToken("COLON_DASH");
   this->qtokens.pop_front();
   
   std::vector<Predicate*> preds = parsePreds();
   CheckToken("PERIOD");
   this->qtokens.pop_front();
   
   return new Rule(headPred, preds);
   
}

Scheme* Parser::parseScheme() {
   std::string id;
   std::vector<std::string> extraIds;
   
   CheckToken("ID");
   id = this->qtokens.front()->GetValue();
   this->qtokens.pop_front();
   CheckToken("LEFT_PAREN");
   this->qtokens.pop_front();
   
   extraIds = parseIds();
   CheckToken("RIGHT_PAREN");
   this->qtokens.pop_front();
   
   return new Scheme(id, extraIds);
}

std::vector<Scheme*> Parser::parseSchemes() {
   std::vector<Scheme*> schemes;
   
   do {
      schemes.push_back(parseScheme());
   } while (this->qtokens.front()->GetType() != "FACTS");
   
   return schemes;
}

Fact* Parser::parseFact() {
   std::string id;
   std::vector<std::string> strings;
   
   CheckToken("ID");
   id = this->qtokens.front()->GetValue();
   this->qtokens.pop_front();
   CheckToken("LEFT_PAREN");
   this->qtokens.pop_front();
   
   strings = parseStrings();
   CheckToken("RIGHT_PAREN");
   this->qtokens.pop_front();
   CheckToken("PERIOD");
   this->qtokens.pop_front();
   
   return new Fact(id, strings);
}

std::vector<Fact*> Parser::parseFacts() {
   std::vector<Fact*> facts;
   
   do {
      facts.push_back(parseFact());
   } while (this->qtokens.front()->GetType() != "RULES");
   
   return facts;
}

std::vector<std::string> Parser::parseStrings() {
   std::vector<std::string> strings;
   
   CheckToken("STRING");
   strings.push_back(this->qtokens.front()->GetValue());
   this->qtokens.pop_front();
   
   while (this->qtokens.front()->GetType() != "RIGHT_PAREN") {
      CheckToken("COMMA");
      this->qtokens.pop_front();
      CheckToken("STRING");
      strings.push_back(this->qtokens.front()->GetValue());
      this->qtokens.pop_front();
   }
   
   return strings;
}

std::vector<std::string> Parser::parseIds() {
   std::vector<std::string> ids;
   
   CheckToken("ID");
   ids.push_back(this->qtokens.front()->GetValue());
   this->qtokens.pop_front();
   
   while (this->qtokens.front()->GetType() != "RIGHT_PAREN") {
      CheckToken("COMMA");
      this->qtokens.pop_front();
      CheckToken("ID");
      ids.push_back(this->qtokens.front()->GetValue());
      this->qtokens.pop_front();
   }
   return ids;
}

HeadPredicate* Parser::parseHeadPred() {
   std::string id;
   std::vector<std::string> extraIds;
   
   CheckToken("ID");
   id = this->qtokens.front()->GetValue();
   this->qtokens.pop_front();
   CheckToken("LEFT_PAREN");
   this->qtokens.pop_front();
   extraIds = parseIds();
   CheckToken("RIGHT_PAREN");
   this->qtokens.pop_front();
   return new HeadPredicate(id, extraIds);
}

std::vector<Predicate*> Parser::parsePreds() { //problem is here stops when comma is next
   std::vector<Predicate*> preds;
   bool firstIteration = true;
   
   while (this->qtokens.front()->GetType() != "PERIOD") {
      if (!firstIteration) {
         CheckToken("COMMA");
         this->qtokens.pop_front();
      }
      firstIteration = false;
    
      preds.push_back(parsePredicate());
   }
   return preds;
}

Predicate* Parser::parsePredicate() {
   std::string id;
   std::vector<Parameter*> extraParameters;
   
   CheckToken("ID");
   id = this->qtokens.front()->GetValue();
   this->qtokens.pop_front();
   CheckToken("LEFT_PAREN");
   this->qtokens.pop_front();
   extraParameters = parseParameters();
   CheckToken("RIGHT_PAREN");
   this->qtokens.pop_front();
         
   return new Predicate(id, extraParameters);
}

std::vector<Parameter*> Parser::parseParameters() { //for multiple ones
   std::vector<Parameter*> parameters;
   bool firstIteration = true;
   
   while (this->qtokens.front()->GetType() != "RIGHT_PAREN") {
      if (!firstIteration) {
         CheckToken("COMMA");
         this->qtokens.pop_front();
      }
      firstIteration = false;
      parameters.push_back(parseParam());
   }
   return parameters;
}

Parameter* Parser::parseParam() { //a single parameter
   if (this->qtokens.front()->GetType() == "STRING") {
      Token* tmp = this->qtokens.front();
      this->qtokens.pop_front();
      return new ParameterString(tmp->GetValue());
   }
   else if (this->qtokens.front()->GetType() == "ID") {
      Token* tmp = this->qtokens.front();
      this->qtokens.pop_front();
      return new ParameterID(tmp->GetValue());
   }
   else {
      return parseExpression();
   }
}

Parameter* Parser::parseExpression() {
   Parameter* leftParam = NULL;
   Parameter* rightParam = NULL;
   std::string myOperator;
   
   CheckToken("LEFT_PAREN");
   this->qtokens.pop_front();
   leftParam = parseParam();
   if (this->qtokens.front()->GetType() == "ADD" || this->qtokens.front()->GetType() == "MULTIPLY") {
      myOperator = this->qtokens.front()->GetValue();
      this->qtokens.pop_front();
      rightParam = parseParam();
      }
   else {
      Token* given = qtokens.front();
      throw (given);
   }
   return new Expressions(leftParam, myOperator, rightParam);
}
