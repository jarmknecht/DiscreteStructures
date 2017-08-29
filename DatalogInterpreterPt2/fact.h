//
//  fact.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef fact_h
#define fact_h

#include <vector>
#include <string>

class Fact {
public:
   Fact();
   ~Fact();
   Fact(std::string factId, std::vector<std::string> strings);
   std::vector<std::string> GetStrings();
   
   std::string toString();
   
   std::string myID;
   std::vector<std::string> myStrings;
};

#endif /* fact_h */
