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

void Database::FillDatabase(std::vector<Scheme*> schemes, std::vector<Fact*> facts, std::vector<Rule*> rules, std::vector<Query*> queries) {
   this->mySchemes = schemes;
   this->myFacts = facts;
   this->myRules = rules;
   this->myQueries = queries;
   
   int numOfPasses = 0;
   
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
   numOfPasses = lookAtRules(this->myRules);
   
   std::cout << "Schemes populated after " << numOfPasses << " passes through the Rules." << std::endl;
   
   evalQueries(this->myQueries);
}

int Database::GetSize() {
   int size = 0;
   
   for (unsigned int i = 0; i < myRelations.size(); i++) {
      size += myRelations.at(i)->GetNumOfTuples(*myRelations.at(i));
   }
   
   return size;
}

int Database::lookAtRules(std::vector<Rule *> rs) {
   int numOfPasses = 0;
   bool keepLooking = true;
   int sizeOfRelationBefore = 0;
   int sizeOfRelationAfter = 0;
   
   while (keepLooking) {
      sizeOfRelationBefore = GetSize();
      evalRules(rs);
      numOfPasses++;
      sizeOfRelationAfter = GetSize();
      
      if (sizeOfRelationBefore == sizeOfRelationAfter) {
         keepLooking = false;
      }
   }
   
   return numOfPasses;
}

void Database::ClearOldFacts() {
   for (unsigned int i = 0; i < this->newFacts.size(); i++) {
      delete this->newFacts.at(i);
      this->newFacts.at(i) = NULL;
   }
   this->newFacts.clear();
}

void Database::evalRules(std::vector<Rule *> rs) {
   Relation* one = NULL;
   Relation* two= NULL;
   Relation* three = NULL;
   Relation* clear = NULL;
   
   Relation* projectR = NULL;
   Relation* unionR = NULL;
   Relation* toUnion = NULL;
   
   std::vector<int> indexes;
   std::vector<std::string> names;
   
   for (unsigned int i = 0; i < rs.size(); i++) {
      one = clear;
      two = clear;
      three = clear;
      
      ClearOldFacts();
      indexes.clear();
      names.clear();
      
      evalRulePreds(rs.at(i)->predicates);
      CheckDupSchemes(newFacts);
      
      if (newFacts.size() < 1) {
         //no new facts do nothing!!
      }
      else if (newFacts.size() == 1) {
         indexes = GetProjCols(newFacts.at(0), rs.at(i));
         projectR = newFacts.at(0)->Project(*newFacts.at(0), indexes);
         toUnion = Find(rs.at(i)->myHeadPredicate->leftId);
         if (toUnion == NULL) {
            Relation* newUnion = new Relation();
            
            newUnion->rName = rs.at(i)->myHeadPredicate->leftId;
            for (unsigned int m = 0; m < rs.at(i)->myHeadPredicate->IDs.size(); m++) {
               newUnion->schema.push_back(rs.at(i)->myHeadPredicate->IDs.at(m));
            }
            toUnion = newUnion;
         }
         unionR = projectR->Union(*projectR, *toUnion);
         delete toUnion;
         
         myRelations.push_back(unionR);
      }
      else {
         evalRulesNewFacts(one, two, three, projectR, unionR, toUnion, i);
      }
   }
}

Relation* Database::CheckIfUnionIsNull(Relation* toUnion, unsigned int i) {
   if (toUnion == NULL) {
      Relation* newUnion = new Relation();
      
      newUnion->rName = this->myRules.at(i)->myHeadPredicate->leftId;
      for (unsigned int m = 0; m < this->myRules.at(i)->myHeadPredicate->IDs.size(); m++) {
         newUnion->schema.push_back(this->myRules.at(i)->myHeadPredicate->IDs.at(m));
      }
      toUnion = newUnion;
   }
   return toUnion;
}

void Database::evalRulesNewFacts(Relation* one, Relation* two, Relation* three, Relation* projectR, Relation* unionR, Relation* toUnion, unsigned int i) {
   std::vector<int> indexes;
   
   for (unsigned int j = 0; j < newFacts.size(); j++) {
      Relation temp1 = *newFacts.at(j);
      
      if (one == NULL) {
         if (j < newFacts.size() - 1) {
            j++;
            Relation temp2 = *newFacts.at(j);
            
            one = one->Join(temp1, temp2);
            
            if (j == newFacts.size() - 1) {
               indexes = GetProjCols(one, this->myRules.at(i));
               projectR = one->Project(*one, indexes);
               toUnion = Find(this->myRules.at(i)->myHeadPredicate->leftId);
               toUnion = CheckIfUnionIsNull(toUnion, i);
               unionR = projectR->Union(*projectR, *toUnion);
               delete toUnion;
               
               myRelations.push_back(unionR);
            }
         }
         else {
            two = two->Join(*one, temp1);
            indexes = GetProjCols(two, this->myRules.at(i));
            projectR = two->Project(*two, indexes);
            toUnion = Find(this->myRules.at(i)->myHeadPredicate->leftId);
            toUnion = CheckIfUnionIsNull(toUnion, i);
            unionR = projectR->Union(*projectR, *toUnion);
            
            delete toUnion;
            myRelations.push_back(unionR);
         }
      }
      else {
         three = three->Join(*one, temp1);
         one = three;
         if (j == newFacts.size() - 1) {
            indexes = GetProjCols(one, this->myRules.at(i));
            projectR = one->Project(*one, indexes);
            toUnion = Find(this->myRules.at(i)->myHeadPredicate->leftId);
            toUnion = CheckIfUnionIsNull(toUnion, i);
            
            unionR = projectR->Union(*projectR, *toUnion);
            delete toUnion;
            myRelations.push_back(unionR);
         }
      }
   }
}

Relation* Database::Find (std::string myString) {
   Relation* temp = NULL;
   
   for (unsigned int i = 0; i < myRelations.size(); i++) {
      if (myRelations.at(i)->rName == myString) {
         temp = myRelations.at(i);
         myRelations.erase(myRelations.begin() + i);
         return temp;
      }
   }
   return temp;
}

std::vector<int> Database::GetProjCols(Relation* r, Rule* rule) {
   std::vector<int> indexes;
   
   for (unsigned int i = 0; i < rule->myHeadPredicate->IDs.size(); i++) {
      for (unsigned int j = 0; j < r->schema.size(); j++) {
            if (rule->myHeadPredicate->IDs.at(i) == r->schema.at(j)) {
               indexes.push_back(j);
               break; //found matching id so speed it up
            }
      }
   }
   return indexes;
}

void Database::CheckDupSchemes(std::vector<Relation*> nFacts) {
   std::string currScheme;
   
   for (unsigned int i = 0; i < nFacts.size(); i ++) {
      std::vector<std::string> newScheme;
      
      Relation curr = *nFacts.at(i);
      std::vector<std::string> schemes = nFacts.at(i)->schema;
      
      if (schemes.size() > 1) {
         for (unsigned int j = 0; j < schemes.size(); j++) {
            currScheme = schemes.at(j);
            
            if (!Contains(currScheme, newScheme)) {
               newScheme.push_back(currScheme);
            }
         }
         nFacts.at(i)->schema = newScheme;
      }
   }
}

bool Database::Contains(std::string curr, std::vector<std::string> schemes) {
   for (unsigned int i = 0; i < schemes.size(); i++) {
      std::string temp = schemes.at(i);
      if (temp == curr) {
         return true;
      }
   }
   return false;
}

void Database::evalRulePreds(std::vector<Predicate*> rPreds) {
   std::string ruleRel;
   
   Relation* newReltoAdd = NULL;
   
   for (unsigned int i = 0; i < rPreds.size(); i++) {
      Relation* temp = new Relation();
      
      ruleRel = rPreds.at(i)->leftId;
      
      for (unsigned int k = 0; k < myRelations.size(); k++) {
         if (ruleRel == myRelations.at(k)->rName) {
            temp = myRelations.at(k);
            temp->schema.clear();
            for (unsigned int j = 0; j < rPreds.at(i)->parameters.size(); j++) {
               temp->schema.push_back(rPreds.at(i)->parameters.at(j)->GetParameter());
            }
         }
      }
      if (temp->rName == "") { //relation is not in the database yet so need to make it and add it to myRelations
         temp->rName = ruleRel;
         for (unsigned int j = 0; j < rPreds.at(i)->parameters.size(); j++) {
            temp->schema.push_back(rPreds.at(i)->parameters.at(j)->GetParameter());
         }
         this->myRelations.push_back(temp);
      }
      newReltoAdd = evalRuleParameters(rPreds, *temp, i);
      newFacts.push_back(newReltoAdd);
   }
}

Relation* Database::evalRuleParameters(std::vector<Predicate*> rPreds, Relation source, unsigned int index) {
   Relation* newRelation = NULL;
   
   for (unsigned int i = 0; i < rPreds.at(index)->parameters.size(); i++) {
      if(rPreds.at(index)->parameters.at(i)->GetTokenType() == "STRING") { //parameter is a string
         if (newRelation == NULL) { //use source to make the newRelation
            newRelation = source.Select(source, i, rPreds.at(index)->parameters.at(i)->GetParameter());
         }
         else { //used newRelation as the source to overwrite the old one
            newRelation = newRelation->Select(*newRelation, i, rPreds.at(index)->parameters.at(i)->GetParameter());
         }
      }
      else if (rPreds.at(index)->parameters.at(i)->GetTokenType() == "ID") { //parameter is an ID need to look for extra IDs
         if (newRelation == NULL) { //use source to make the newRelation
            if (CheckForDupIDs(rPreds.at(index)->parameters)) {
               newRelation = dupIDRule(rPreds, source, index, i);
            }
            else {
               newRelation = sinIDRule(rPreds, source, index, i);
            }
         }
         else { //use newRelation to make newRelation
            if (CheckForDupIDs(rPreds.at(index)->parameters)) {
               newRelation = dupIDRule(rPreds, *newRelation, index, i);
            }
            else {
               newRelation = sinIDRule(rPreds, *newRelation, index, i);
            }
         }
      }
   }
   return newRelation;
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

Relation* Database::sinIDRule(std::vector<Predicate*> rPreds , Relation r, int temp, int temp2) {
   Relation* newSingleSelect = new Relation();
   
   newSingleSelect->rName = r.rName;
   newSingleSelect->schema = r.schema;
   newSingleSelect->rows = r.rows;
   
   for (unsigned int i = temp2 + 1; i < rPreds.at(temp)->parameters.size(); i++) {
      if (rPreds.at(temp)->parameters.at(temp2)->GetParameter() != rPreds.at(temp)->parameters.at(i)->GetParameter()) {
         newSingleSelect = newSingleSelect->SingleIDSelect(*newSingleSelect, temp2, i, true);
      }
   }
   return newSingleSelect;
}

Relation* Database::singleID(std::vector<Query*> qs, Relation r, int temp, int temp2) {
   Relation* newSingleSelect = new Relation();
   
   newSingleSelect->rName = r.rName;
   newSingleSelect->schema = r.schema;
   newSingleSelect->rows = r.rows;
   
   for (unsigned int i = temp2 + 1; i < qs.at(temp)->predicate->parameters.size(); i++) {
      if (qs.at(temp)->predicate->parameters.at(temp2)->GetParameter() != qs.at(temp)->predicate->parameters.at(i)->GetParameter()) {
         newSingleSelect = newSingleSelect->SingleIDSelect(*newSingleSelect, temp2, i, true);
      }
   }
   return newSingleSelect;
}

Relation* Database::dupIDRule(std::vector<Predicate*> rPreds , Relation r, int temp, int temp2) {
   Relation* newDoubleSelect = new Relation();
   
   newDoubleSelect->rName = r.rName;
   newDoubleSelect->schema = r.schema;
   newDoubleSelect->rows = r.rows;
   
   for (unsigned int j = temp2; j < rPreds.at(temp)->parameters.size(); j++) {
      for (unsigned int i = j + 1; i < rPreds.at(temp)->parameters.size(); i++) {
         if (rPreds.at(temp)->parameters.at(j)->GetParameter() == rPreds.at(temp)->parameters.at(i)->GetParameter()) {
            newDoubleSelect = newDoubleSelect->Select(*newDoubleSelect, j, i);
         }
      }
   }
   
   return newDoubleSelect;
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
