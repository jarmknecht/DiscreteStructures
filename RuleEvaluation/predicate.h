//
//  predicate.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef predicate_h
#define predicate_h

#include "parameter.h"

#include <vector>

class Predicate {
public:
   Predicate();
   ~Predicate();
   Predicate(std::string myID, std::vector<Parameter*> extraParameters);
   std::string toString();
   
   std::string leftId; //name of query
   std::vector<Parameter*> parameters;
};


#endif /* predicate_h */
