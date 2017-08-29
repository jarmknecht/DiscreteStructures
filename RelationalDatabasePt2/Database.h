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
   
      std::vector<Scheme*> mySchemes;
      std::vector<Fact*> myFacts;
      std::vector<Query*> myQueries;
   
      void AddRelation(Relation* r);
      void FillDatabase(std::vector<Scheme*> schemes, std::vector<Fact*> facts, std::vector<Query*> queries);
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
