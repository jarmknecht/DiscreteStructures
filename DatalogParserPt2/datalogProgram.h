//
//  datalogProgram.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef datalogProgram_h
#define datalogProgram_h

#include "scheme.h"
#include "fact.h"
#include "rule.h"
#include "queries.h"

#include <vector>
#include <set>

//#include <algorithm>

class DataLog {

public:
   DataLog();
   ~DataLog();
   
   void AddSchemes(std::vector<Scheme*> addSchemes);
   void AddFacts(std::vector<Fact*> addFacts);
   void AddRules(std::vector<Rule*> addRules);
   void AddQueries(std::vector<Query*> addQueries);
   
   std::string toString();

private:
   std::vector<Scheme*> schemes;
   std::vector<Fact*> facts;
   std::vector<Rule*> rules;
   std::vector<Query*> queries;
   std::set<std::string> domain;
   void PopulateDomain();
   void SortDomain();
};

#endif /* datalogProgram_h */
