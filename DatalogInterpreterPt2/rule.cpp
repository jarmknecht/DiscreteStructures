//
//  rule.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "rule.h"
#include <sstream>

Rule::Rule() {
   
}

Rule::~Rule() {
   delete myHeadPredicate;
   
   for (unsigned int i = 0; i < predicates.size(); i++) {
      delete predicates.at(i);
      predicates.at(i) = NULL;
   }
}

Rule::Rule(HeadPredicate* headPred, std::vector<Predicate*> preds) {
   this->myHeadPredicate = headPred;
   this->predicates = preds;
}

std::string Rule::toString() {
   std::stringstream myString;
   
   myString << this->myHeadPredicate->toString() << " :- ";
   
   for (unsigned int i = 0; i < this->predicates.size(); i++) {
      myString << this->predicates.at(i)->toString();
      if (i < this->predicates.size() - 1) {
         myString << ",";
      }
   }
   
   myString << ".";
   
   return myString.str();
}
