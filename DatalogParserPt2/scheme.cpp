//
//  scheme.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "scheme.h"
#include <sstream>

Scheme::Scheme() {
   
}

Scheme::~Scheme() {
   
}

Scheme::Scheme(std::string id, std::vector<std::string> ids) {
   this->myID = id;
   this->IDs = ids;
}

std::string Scheme::toString() {
   std::stringstream myString;
   
   myString << this->myID << "(";
   for (unsigned int i = 0; i < this->IDs.size(); i++) {
      myString << this->IDs.at(i);
      if (i < this->IDs.size() - 1) {
         myString << ",";
      }
   }
   myString << ")";
   
   return myString.str();
}
