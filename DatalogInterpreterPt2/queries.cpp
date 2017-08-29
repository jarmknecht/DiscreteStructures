//
//  queries.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "queries.h"
#include <sstream>

Query::Query() {
   
}

Query::~Query() {
   delete predicate;
}

Query::Query(Predicate* queryPred) {
   this->predicate = queryPred;
}

std::string Query::toString() {
   std::stringstream myString;
   
   myString << this->predicate->toString();
   myString << "?";
   
   return myString.str();
}
