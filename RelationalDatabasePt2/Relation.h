//
//  Relation.h
//  Relation
//
//  Created by Jonathan Armknecht on 7/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Relation_h
#define Relation_h

#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "scheme.h"
#include "fact.h"

class Relation {
public:
   Relation();
   //Relation(Scheme scheme, std::set<std::vector<std::string>> facts); //need??
   ~Relation();
   
   Relation* Select(Relation r, int index, std::string findValue);
   Relation* Select(Relation r, int firstIndx, int secondIndx);
   Relation* SingleIDSelect(Relation r, int firstIndx, int secondIndx);
   Relation* Project(Relation r, std::vector<int> columns);
   Relation* Rename(Relation r, std::vector<std::string> names);
   
  // std::string ToString();
   
   std::set<std::vector<std::string>> rows; //my set of tuples
   std::string rName; //name of relation
   std::vector<std::string> schema; //vector of schemas
};


#endif /* Relation_h */
