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

Relation* Relation::Select(Relation r, int index, std::string findValue) { //make an overload for more than one select test case for this one as well
   
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
