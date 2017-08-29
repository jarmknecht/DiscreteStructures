//
//  queries.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef queries_h
#define queries_h

#include "predicate.h"

class Query {
public:
   Query();
   ~Query();
   Query(Predicate* queryPred);
   
   std::string toString();
   
   Predicate* predicate;
};

#endif /* queries_h */
