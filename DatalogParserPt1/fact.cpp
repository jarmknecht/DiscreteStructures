//
//  fact.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "fact.h"
#include <sstream>

Fact::Fact() {
   
}

Fact::~Fact() {
   
}

Fact::Fact(std::string factId, std::vector<std::string> strings) {
   this->myID = factId;
   this->myStrings = strings;
}

std::string Fact::toString() {
   std::stringstream myString;
   
   myString << myID << "(";
   
   for (unsigned int i = 0; i < this->myStrings.size(); i++) {
      myString << this->myStrings.at(i);
      if (i < this->myStrings.size() - 1) {
         myString << ",";
      }
   }
   
   myString << ").";
   
   
   return myString.str();
}

std::vector<std::string> Fact::GetStrings() {
   return this->myStrings;
}

