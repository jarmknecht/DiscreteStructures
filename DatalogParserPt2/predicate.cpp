//
//  predicate.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "predicate.h"
#include <sstream>

Predicate::Predicate() {

}

Predicate::~Predicate() {
   for (unsigned int i = 0; i < this->parameters.size(); i++) {
      delete parameters.at(i);
      parameters.at(i) = NULL;
   }
}

Predicate::Predicate(std::string myID, std::vector<Parameter*> extraParameters) {
   this->leftId = myID;
   this->parameters = extraParameters;
}

std::string Predicate::toString() {
   std::stringstream myString;
   
   myString << this->leftId << "(";
   
   for (unsigned int i = 0; i < this->parameters.size(); i++) {
      myString << this->parameters.at(i)->GetParameter();
      if (i < this->parameters.size() - 1) {
         myString << ",";
      }
   }
   
   myString << ")";
   
   return myString.str();
}
