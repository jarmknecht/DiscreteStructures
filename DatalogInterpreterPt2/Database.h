//
//  Database.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/19/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include "Relation.h"
#include "datalogProgram.h"
#include "parameter.h"

class Database {
   public:
      Database();
      ~Database();
   
      std::vector<Relation*> myRelations; //relations from schema and facts
   
      std::vector<Relation*> newRelFromQs; //relations to print from the queries looked at
   
      std::vector<Relation*> newFacts;
   
      std::vector<Scheme*> mySchemes;
      std::vector<Fact*> myFacts;
      std::vector<Rule*> myRules;
      std::vector<Query*> myQueries;
   
      void AddRelation(Relation* r);
      void FillDatabase(std::vector<Scheme*> schemes, std::vector<Fact*> facts, std::vector<Rule*> rules, std::vector<Query*> queries);
   
      void ClearOldFacts();
      int lookAtRules(std::vector<Rule*> rs);
      int GetSize();
      void evalRules(std::vector<Rule*> rs);
      void evalRulePreds(std::vector<Predicate*> rPreds);
      Relation* evalRuleParameters(std::vector<Predicate*> rPreds, Relation source, unsigned int index);
      void evalRulesNewFacts(Relation* one, Relation* two, Relation* three, Relation* projectR, Relation* unionR, Relation* toUnion, unsigned int i);
      Relation* Find (std::string myString);
      Relation* dupIDRule(std::vector<Predicate*> rPreds , Relation r, int temp, int temp2);
      Relation* sinIDRule(std::vector<Predicate*> rPreds , Relation r, int temp, int temp2);
      void CheckDupSchemes(std::vector<Relation*> nFacts);
      bool Contains(std::string curr, std::vector<std::string> schemes);
      std::vector<int> GetProjCols(Relation* r, Rule* rule);
      Relation* CheckIfUnionIsNull(Relation* toUnion, unsigned int i);
   
      void evalQueries(std::vector<Query*> qs);
      Relation* singleID(std::vector<Query*> qs, Relation r, int temp, int temp2);
      Relation* duplicateIDs(std::vector<Query*> qs, Relation r, int temp, int temp2);
      Relation* evalParameters(std::vector<Query*> qs, Relation source, unsigned int index);
      bool CheckForDupIDs(std::vector<Parameter*> parameters);
      bool SeenID(std::vector<std::string> seenIDs, std::string findValue);
      bool CheckRemainingSchema(std::vector<std::string> schemes, int index, std::vector<std::string> seen);
      void PrintSchemes(std::stringstream& ss, Relation* newRelFromQ, std::vector<std::string> seenIDs, std::vector<std::string> vex);
      std::string toString(Relation* newRelFromQ, int index);
};


#endif /* Database_h */
