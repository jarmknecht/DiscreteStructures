//
//  headPredicate.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef headPredicate_h
#define headPredicate_h

#include <vector>
#include <string>

class HeadPredicate {
   public:
      HeadPredicate();
      ~HeadPredicate();
      HeadPredicate(std::string myID, std::vector<std::string> extraIds);
   
      std::string toString();
   
      std::string leftId;
      std::vector<std::string> IDs;
};


#endif /* headPredicate_h */
