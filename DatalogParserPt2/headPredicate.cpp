//
//  headPredicate.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "headPredicate.h"
#include <sstream>

HeadPredicate::HeadPredicate() {

}

HeadPredicate::~HeadPredicate() {
   
}

HeadPredicate::HeadPredicate(std::string myID, std::vector<std::string> extraIds) {
   this->leftId = myID;
   this->IDs = extraIds;
}

std::string HeadPredicate::toString() {
   std::stringstream myString;
   
   myString << this->leftId << "(";
   
   for (unsigned int i = 0; i < this->IDs.size(); i++) {
      myString << this->IDs.at(i);
      if (i < this->IDs.size() - 1) {
         myString << ",";
      }
   }
   myString << ")";
   
   return myString.str();
}
