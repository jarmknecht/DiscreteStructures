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

class Relation {
   public:
      Relation();
      Relation(std::string relationName, std::vector<std::string> schemes, std::set<std::vector<std::string>> facts);
      ~Relation();
   
      Relation* Select(Relation r, int index, std::string findValue);
      Relation* Select(Relation r, int firstIndx, int secondIndx);
      Relation* Project(Relation r, std::vector<int> columns);
      Relation* Rename(Relation r, std::vector<std::string> names);
   
      std::string ToString();
   
      std::set<std::vector<std::string>> rows; //my set of tuples
      std::string rName;
      std::vector<std::string> schema; ///my Scheme vector here for part 2
};


#endif /* Relation_h */
