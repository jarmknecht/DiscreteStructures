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
#include <iostream>

class Relation {
public:
   Relation();
   //Relation(std::string relationName, std::vector<std::string> schemes, std::set<std::vector<std::string>> facts);
   ~Relation();
   
   Relation* Select(Relation r, int index, std::string findValue);
   Relation* Select(Relation r, int firstIndx, int secondIndx);
   Relation* SingleIDSelect(Relation r, int firstIndx, int secondIndx, bool rules = false);
   Relation* Project(Relation r, std::vector<int> columns);
   Relation* Rename(Relation r, std::vector<std::string> names);
   
   Relation* Union(Relation one, Relation two);
   Relation* Join(Relation one, Relation two);
   
   int GetNumOfTuples(Relation r);
   
   //std::string ToString();
   
   std::set<std::vector<std::string>> rows; //my set of tuples
   std::string rName;
   std::vector<std::string> schema; ///my Scheme vector here for part 2
private:
   Relation* CartesianProduct(Relation one, Relation two, std::vector<std::string> schema);
   void CartProduct(std::vector<std::string> v, std::vector<std::string> v2, Relation* cartR);
   Relation* NaturalJoin(Relation one, Relation two, std::vector<std::string> schema, std::vector<int> colsSameInR1, std::vector<int> colsSameInR2);
   void NatJoin(std::vector<std::string> v, std::vector<std::string> v2, Relation* natR, std::vector<int> colsSameInR2);
   bool CanJoin(std::vector<std::string> v, std::vector<std::string> v2, std::vector<int> colsSameInR1, std::vector<int> colsSameInR2);
};


#endif /* Relation_h */
