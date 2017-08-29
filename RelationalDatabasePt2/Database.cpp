//
//  Database.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/19/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Database.h"
#include <sstream>
#include <iostream>

Database::Database() {
   
}

Database::~Database() {
   for (unsigned int i = 0; i < this->myRelations.size(); i++) {
      delete this->myRelations.at(i);
      this->myRelations.at(i) = NULL;
   }
   for (unsigned int j = 0; j < this->newRelFromQs.size(); j++) {
      delete this->newRelFromQs.at(j);
      this->newRelFromQs.at(j) = NULL;
   }
}

void Database::AddRelation(Relation* r) {
   this->myRelations.push_back(r);
}

void Database::FillDatabase(std::vector<Scheme*> schemes, std::vector<Fact*> facts, std::vector<Query*> queries) {
   this->mySchemes = schemes;
   this->myFacts = facts;
   this->myQueries = queries;
   
   for (unsigned int i = 0; i < this->mySchemes.size(); i++) {
      Relation* r = new Relation();
      r->rName = mySchemes.at(i)->myID;
      r->schema = mySchemes.at(i)->IDs;
      
      for (unsigned int j = 0; j < this->myFacts.size(); j++) {
         if (r->rName == myFacts.at(j)->myID) {
            r->rows.insert(this->myFacts.at(j)->myStrings);
         }
      }
      AddRelation(r);
   }
   evalQueries(queries);
}

void Database::evalQueries(std::vector<Query *> qs) {
   std::string queryRel;
   Relation temp;
   Relation* newRel = NULL;
   std::vector<int> indexes;
   std::vector<std::string> names;
   
   for (unsigned int i = 0; i < qs.size(); i++) {
      queryRel = qs.at(i)->predicate->leftId; //give me the name of what relation the query needs to look into
      
      for (unsigned int k = 0; k < myRelations.size(); k++) {
         if (queryRel == myRelations.at(k)->rName) {
            temp = *myRelations.at(k);
         }
      }
      newRel = evalParameters(qs, temp, i);
      
      for (unsigned int j = 0; j < qs.at(i)->predicate->parameters.size(); j++) {
         if (qs.at(i)->predicate->parameters.at(j)->GetTokenType() != "STRING") {
            indexes.push_back(j);
            names.push_back(qs.at(i)->predicate->parameters.at(j)->GetParameter());
         }
      }
      
      newRel = newRel->Project(*newRel, indexes);
      newRel = newRel->Rename(*newRel, names);

      
      this->newRelFromQs.push_back(newRel);
      indexes.clear();
      names.clear();
      
      std::cout << toString(this->newRelFromQs.at(i), i);
   }
}

Relation* Database::evalParameters(std::vector<Query*> qs, Relation source, unsigned int index) {
   Relation* newRelation = NULL;

   for (unsigned int i = 0; i < qs.at(index)->predicate->parameters.size(); i++) {
      if(qs.at(index)->predicate->parameters.at(i)->GetTokenType() == "STRING") { //parameter is a string
         if (newRelation == NULL) { //use source to make the newRelation
            newRelation = source.Select(source, i, qs.at(index)->predicate->parameters.at(i)->GetParameter());
         }
         else { //used newRelation as the source to overwrite the old one
            newRelation = newRelation->Select(*newRelation, i, qs.at(index)->predicate->parameters.at(i)->GetParameter());
         }
      }
      else if (qs.at(index)->predicate->parameters.at(i)->GetTokenType() == "ID") { //parameter is an ID need to look for extra IDs
         if (newRelation == NULL) { //use source to make the newRelation
            if (CheckForDupIDs(qs.at(index)->predicate->parameters)) {
               newRelation = duplicateIDs(qs, source, index, i);
            }
            else {
               newRelation = singleID(qs, source, index, i);
            }
         }
         else { //use newRelation to make newRelation
            if (CheckForDupIDs(qs.at(index)->predicate->parameters)) {
               newRelation = duplicateIDs(qs, *newRelation, index, i);
            }
            else {
               newRelation = singleID(qs, *newRelation, index, i);
            }
         }
      }
   }
   return newRelation;
}

Relation* Database::singleID(std::vector<Query*> qs, Relation r, int temp, int temp2) {
   Relation* newSingleSelect = new Relation();
   
   newSingleSelect->rName = r.rName;
   newSingleSelect->schema = r.schema;
   newSingleSelect->rows = r.rows;
   
   for (unsigned int i = temp2 + 1; i < qs.at(temp)->predicate->parameters.size(); i++) {
      if (qs.at(temp)->predicate->parameters.at(temp2)->GetParameter() != qs.at(temp)->predicate->parameters.at(i)->GetParameter()) {
         newSingleSelect = newSingleSelect->SingleIDSelect(*newSingleSelect, temp2, i);
      }
   }
   return newSingleSelect;
}

Relation* Database::duplicateIDs(std::vector<Query*> qs, Relation r, int temp, int temp2) {
   Relation* newDoubleSelect = new Relation();
   
   newDoubleSelect->rName = r.rName;
   newDoubleSelect->schema = r.schema;
   newDoubleSelect->rows = r.rows;
   
   for (unsigned int j = temp2; j < qs.at(temp)->predicate->parameters.size(); j++) {
      for (unsigned int i = j + 1; i < qs.at(temp)->predicate->parameters.size(); i++) {
         if (qs.at(temp)->predicate->parameters.at(j)->GetParameter() == qs.at(temp)->predicate->parameters.at(i)->GetParameter()) {
            newDoubleSelect = newDoubleSelect->Select(*newDoubleSelect, j, i);
         }
      }
   }
   
   return newDoubleSelect;
   
}

bool Database::CheckForDupIDs(std::vector<Parameter*> parameters) {
   for (unsigned int i = 0; i < parameters.size(); i++) {
      for (unsigned int j = i + 1; j < parameters.size(); j++) {
         if (parameters.at(i)->GetParameter() == parameters.at(j)->GetParameter()) {
            return true;
         }
      }
   }
   return false;
}

bool Database::SeenID(std::vector<std::string> seenIDs, std::string findValue) {
   
   for (unsigned int i = 0; i < seenIDs.size(); i++) {
      if (seenIDs.at(i) == findValue) {
         return true;
      }
   }
   return false;
}

bool Database::CheckRemainingSchema(std::vector<std::string> schemes, int index, std::vector<std::string> seen) {
   
   for (unsigned int j = index + 1; j < schemes.size(); j++) {
      if (!SeenID(seen, schemes.at(j))) {
         return true;
      }
   }
   return false;
}

void Database::PrintSchemes(std::stringstream& ss, Relation* newRelFromQ, std::vector<std::string> seenIDs, std::vector<std::string> vex) {
   for (unsigned int j = 0; j < newRelFromQ->schema.size(); j++) {
      // if we haven't seen the schema yet
      if (!SeenID(seenIDs, newRelFromQ->schema.at(j))) {
         ss << newRelFromQ->schema.at(j) << "=" << vex.at(j);
         seenIDs.push_back(newRelFromQ->schema.at(j));
         if (j != newRelFromQ->schema.size() - 1 && (CheckRemainingSchema(newRelFromQ->schema, j, seenIDs))) {
            ss << ", ";
         }
      }
   }
}

std::string Database::toString(Relation* newRelFromQ, int index) {
   std::stringstream ss;
   
   ss << this->myQueries.at(index)->toString();
   if (newRelFromQ->rows.size() > 0) {
      ss << " Yes(" << newRelFromQ->rows.size() << ")" << std::endl;
      std::set<std::vector<std::string>>::iterator iter;
      for (iter = newRelFromQ->rows.begin(); iter != newRelFromQ->rows.end(); iter++) {
         std::vector<std::string> seenIDs;
         std::vector<std::string> vex = *iter;
         
         if (newRelFromQ->schema.size() > 0 ) {
            ss << "  ";
            PrintSchemes(ss, newRelFromQ, seenIDs, vex);
            
            ss << std::endl;
         }
      }
   }
   else {
      ss << " No" << std::endl;
   }

   return ss.str();
}
