//
//  scheme.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef scheme_h
#define scheme_h

#include <vector>
#include <string>

class Scheme {
public:
   Scheme();
   ~Scheme();
   Scheme(std::string id, std::vector<std::string> ids);
   
   std::string toString();
   
   std::string myID;
   std::vector<std::string> IDs;
};

#endif /* scheme_h */
