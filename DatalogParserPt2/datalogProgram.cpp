//
//  datalogProgram.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "datalogProgram.h"
#include <sstream>

DataLog::DataLog() {
   
}

DataLog::~DataLog() {
   for (unsigned int i = 0; i < schemes.size(); i++) {
      delete schemes.at(i);
      schemes.at(i) = NULL;
   }
   
   for (unsigned int i = 0; i < facts.size(); i++) {
      delete facts.at(i);
      facts.at(i) = NULL;
   }
   
   for (unsigned int i = 0; i < rules.size(); i++) {
      delete rules.at(i);
      rules.at(i) = NULL;
   }
   
   for (unsigned int i = 0; i < queries.size(); i++) {
      delete queries.at(i);
      queries.at(i) = NULL;
   }
}

void DataLog::AddSchemes(std::vector<Scheme*> addSchemes) {
   for (unsigned int i = 0; i < addSchemes.size(); i++) {
      this->schemes.push_back(addSchemes.at(i));
   }
}

void DataLog::AddFacts(std::vector<Fact*> addFacts) {
   for (unsigned int i = 0; i < addFacts.size(); i++) {
      this->facts.push_back(addFacts.at(i));
   }
}

void DataLog::AddRules(std::vector<Rule*> addRules) {
   for (unsigned int i = 0; i < addRules.size(); i++) {
      this->rules.push_back(addRules.at(i));
   }
}

void DataLog::AddQueries(std::vector<Query*> addQueries) {
   for (unsigned int i = 0; i < addQueries.size(); i++) {
      this->queries.push_back(addQueries.at(i));
   }
}

void DataLog::PopulateDomain() {
   for (unsigned int i = 0; i < facts.size(); i++ ) {
      for(std::string str : facts.at(i)->GetStrings()) {
         this->domain.insert(str);
      }
   }
}

/*void DataLog::SortDomain() { //don't need this since a set is already organized
   sort(this->domain.begin(), this->domain.end());
}*/

std::string DataLog::toString() {
   std::stringstream myString;
   
   myString << "Success!" << std::endl;
   myString << "Schemes(" << this->schemes.size() << "):" << std::endl;
   
   for (unsigned int i = 0; i < this->schemes.size(); i++) {
      myString << "  " << this->schemes.at(i)->toString() << std::endl;
   }
   
   myString << "Facts(" << this->facts.size() << "):" << std::endl;
   
   for (unsigned int i = 0; i < this->facts.size(); i++) {
      myString << "  " << this->facts.at(i)->toString() << std::endl;
   }
   
   myString << "Rules(" << this->rules.size() << "):" << std::endl;
   
   for (unsigned int i = 0; i < this->rules.size(); i++) {
      myString << "  " << this->rules.at(i)->toString() << std::endl;
   }
   
   myString << "Queries(" << this->queries.size() << "):" << std::endl;
   
   for (unsigned int i = 0; i < this->queries.size(); i++) {
      myString << "  " << this->queries.at(i)->toString() << std::endl;
   }
   
   PopulateDomain();
   myString << "Domain(" << this->domain.size() << "):" << std::endl;
   for (auto f : this->domain) {
      myString << "  " << f << std::endl;
   }
   
   return myString.str();
}

