//
//  rule.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef rule_h
#define rule_h

#include "headPredicate.h"
#include "predicate.h"

class Rule {
public:
   Rule();
   ~Rule();
   Rule(HeadPredicate* headPred, std::vector<Predicate*> preds);
   
   std::string toString();
   
   HeadPredicate* myHeadPredicate;
   std::vector<Predicate*> predicates;
};


#endif /* rule_h */
