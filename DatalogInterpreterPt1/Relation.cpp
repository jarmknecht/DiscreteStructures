//
//  Relation.cpp
//  Relation
//
//  Created by Jonathan Armknecht on 7/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Relation.h"

Relation::Relation() {
   
}

Relation::~Relation() {

}

Relation::Relation(std::string relationName, std::vector<std::string> schemes, std::set<std::vector<std::string>> facts) {
   this->rName = relationName;
   this->schema = schemes;
   this->rows = facts;
}

Relation* Relation::Select(Relation r, int index, std::string findValue) {   
   Relation* newSelectR = new Relation();
   
   newSelectR->rName = r.rName;
   newSelectR->schema = r.schema;
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = r.rows.begin(); iter != r.rows.end(); iter++) {
      std::vector<std::string> vex = *iter;
      
      if (vex.at(index) == findValue) {
         newSelectR->rows.insert(vex);
      }
   }
   
   return newSelectR;
}

Relation* Relation::Select(Relation r, int firstIndx, int secondIndx) {
   Relation* newSelectR = new Relation();
   
   newSelectR->rName = r.rName;
   newSelectR->schema = r.schema;
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = r.rows.begin(); iter != r.rows.end(); iter++) {
      std::vector<std::string> vex = *iter;
      if (vex.at(firstIndx) == vex.at(secondIndx)) {
         newSelectR->rows.insert(vex);
      }
   }
   return newSelectR;
}

Relation* Relation::SingleIDSelect(Relation r, int firstIndx, int secondIndx) {
   Relation* newSelectR = new Relation();
   
   newSelectR->rName = r.rName;
   newSelectR->schema = r.schema;
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = r.rows.begin(); iter != r.rows.end(); iter++) {
      std::vector<std::string> vex = *iter;
      if (vex.at(firstIndx) != vex.at(secondIndx)) {
         newSelectR->rows.insert(vex);
      }
   }
   return newSelectR;
}

Relation* Relation::Project(Relation r, std::vector<int> columns) {
   
   Relation* newProjectR = new Relation();
   
   newProjectR->rName = r.rName;
   
   for (unsigned int i = 0; i < columns.size(); i++) {
      newProjectR->schema.push_back(r.schema.at(columns.at(i)));
   }
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = r.rows.begin(); iter != r.rows.end(); iter++) {
      std::vector<std::string> addTuple;
      
      std::vector<std::string> vex = *iter;
      
      for (unsigned int i = 0; i < columns.size(); i++) {
         addTuple.push_back(vex.at(columns.at(i)));
      }
      newProjectR->rows.insert(addTuple);
   }
   
   return newProjectR;
}

Relation* Relation::Rename(Relation r, std::vector<std::string> names) {
   Relation* newRenameR = new Relation();
   
   newRenameR->rName = r.rName; //only copy over the name of the relation not schema since they will change
   
   for (unsigned int i = 0; i < names.size(); i++) {
      newRenameR->schema.push_back(names.at(i));
   }
   newRenameR->rows = r.rows;
   
   return newRenameR;
}

Relation* Relation::Union(Relation one, Relation two) {
   Relation* newUnionR = new Relation();
   std::stringstream ssUnion;
   
   if (one.schema.size() != two.schema.size()) { //can't union to relations that don't have same size of schema
      return NULL;
   }
   
   std::set<std::vector<std::string>> tuples;
   
   ssUnion << one.rName << " U " << two.rName;
   
   newUnionR->rName = ssUnion.str(); //What should I name this??
   
   for (unsigned int i = 0; i < one.schema.size(); i++) {
      newUnionR->schema.push_back(one.schema.at(i));
      for (unsigned int j = 0; j < two.schema.size(); j++) {
         if (one.schema.at(i) == two.schema.at(j)) {
            break; //found a match don't need to keep looking to rename
         }
         else {
            Rename(two, newUnionR->schema);
         }
      }
   }
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = one.rows.begin(); iter != one.rows.end(); iter++) {
      std::vector<std::string> vex = *iter;
      
      tuples.insert(vex);
   }
   
   std::set<std::vector<std::string>>::iterator iter2;
   for (iter2 = two.rows.begin(); iter2 != two.rows.end(); iter2++) {
      std::vector<std::string> vex2 = *iter2;
      
      tuples.insert(vex2);
   }
   
   newUnionR->rows = tuples;
   
   return newUnionR;
}

Relation* Relation::Join(Relation one, Relation two) {
   
   Relation* newJoinR = new Relation();
   std::stringstream ssJoin;
   
   std::vector<int> colsSameInR1;
   
   std::vector<int> colsSameInR2;
   
   ssJoin << one.rName << " |x| " << two.rName; // what should i name this??
   
   for (unsigned int i = 0; i < one.schema.size(); i++) { //push back all schema from the first relation
      newJoinR->schema.push_back(one.schema.at(i));
   }
   
   unsigned long int schemesSize = newJoinR->schema.size(); //save the size of the scheme vector before adding schemes from relation 2 to same computing time
   
   for (unsigned int j= 0; j < two.schema.size(); j++) { //take one scheme from second relation at a time
      bool sameSchema = false;
      
      for (unsigned int k = 0; k < schemesSize; k++) { //see if that scheme has already been added
         if (two.schema.at(j) == newJoinR->schema.at(k)) {
            colsSameInR1.push_back(k); //save col num of same schema from relation 1
            colsSameInR2.push_back(j); //save col num of same schema from relation 2
            sameSchema = true;
         }
      }
      if (!sameSchema) { //if scheme is not in the vector already add it otherwise don't
         newJoinR->schema.push_back(two.schema.at(j));
      }
   }
   
   if (newJoinR->schema.size() == (one.schema.size() + two.schema.size())) { //if schema size is both schemas added together then its a cartesian product
      newJoinR = CartesianProduct(one, two, newJoinR->schema);
   }
   else { //anything else is a natural join
      newJoinR = NaturalJoin(one, two, newJoinR->schema, colsSameInR1, colsSameInR2);
   }
   
   newJoinR->rName = ssJoin.str();
   
   return newJoinR;
}

Relation* Relation::NaturalJoin(Relation one, Relation two, std::vector<std::string> schema, std::vector<int> colsSameInR1, std::vector<int> colsSameInR2) {
   Relation* newNatJoin = new Relation();
   
   newNatJoin->schema = schema;
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = one.rows.begin(); iter != one.rows.end(); iter++) {
      std::vector<std::string> v = *iter;
      
      std::set<std::vector<std::string>>::iterator iter2;
      
      for (iter2 = two.rows.begin(); iter2 != two.rows.end(); iter2++) {
         std::vector<std::string> v2 = *iter2;
         if (CanJoin(v, v2, colsSameInR1, colsSameInR2)) {
            NatJoin(v, v2, newNatJoin, colsSameInR2);
         }
      }
   }
   
   return newNatJoin;
}

bool Relation::CanJoin(std::vector<std::string> v, std::vector<std::string> v2, std::vector<int> colsSameInR1, std::vector<int> colsSameInR2) {
   
   for (unsigned int i = 0; i < colsSameInR1.size(); i++) {
      if (v.at(colsSameInR1.at(i)) == v2.at((colsSameInR2.at(i)))) {
         continue;
      }
      else {
         return false;
      }
   }
   
   return true;
}

void Relation::NatJoin(std::vector<std::string> v, std::vector<std::string> v2, Relation* natR, std::vector<int> colsSameInR2) {
   std::vector<std::string> tuple;
   
   for (unsigned int i = 0; i < v.size(); i++) {
      tuple.push_back(v.at(i));
   }
   
   for (unsigned int j = 0; j < v2.size(); j++) {
      bool toAdd = true;
      
      for (unsigned int k = 0; k < colsSameInR2.size(); k++) {
         if (j == colsSameInR2.at(k)) {
            toAdd = false;
         }
      }
      if (toAdd) {
         tuple.push_back(v2.at(j));
      }
   }
   natR->rows.insert(tuple);
}

Relation* Relation::CartesianProduct(Relation one, Relation two, std::vector<std::string> schema) {
   Relation* newCartesianR = new Relation();
   std::set<std::vector<std::string>> tuples;
   
   newCartesianR->schema = schema;
   
   tuples = one.rows;
   
   std::set<std::vector<std::string>>::iterator iter;
   
   for (iter = one.rows.begin(); iter != one.rows.end(); iter++) {
      std::vector<std::string> v = *iter;
      
      std::set<std::vector<std::string>>::iterator iter2;
      
      for (iter2 = two.rows.begin(); iter2 != two.rows.end(); iter2++) {
         std::vector<std::string> v2 = *iter2;
         CartProduct(v, v2, newCartesianR);
      }
   }
   
   return newCartesianR;
}

void Relation::CartProduct(std::vector<std::string> v, std::vector<std::string> v2, Relation* cartR) {
   std::vector<std::string> tuple;
   
   for (unsigned int i = 0; i < v.size(); i++) {
      tuple.push_back(v.at(i));
   }
   for (unsigned int j = 0; j < v2.size(); j++) {
      tuple.push_back(v2.at(j));
   }
   
   cartR->rows.insert(tuple);
}

std::string Relation::ToString() {
   std::stringstream ss;
   std::set<std::vector<std::string>>::iterator iter;
   
   ss << this->rName << std::endl;
   
   for (unsigned int i = 0; i < this->schema.size(); i++) {
      ss << this->schema.at(i);
      if (i < this->schema.size() - 1) {
         ss << ", ";
      }
   }
   ss << std::endl;
   
   for (iter = rows.begin(); iter != rows.end(); iter++) {
      
      std::vector<std::string> vex = *iter;
      
      for (unsigned int i = 0; i < vex.size(); i++) {
         ss << vex.at(i);
      }
      ss << std::endl;
   }
   
   return ss.str();
}
