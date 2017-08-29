//
//  parameterID.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "parameterID.h"

ParameterID::ParameterID() {
   
}

ParameterID::~ParameterID() {
   
}

ParameterID::ParameterID(std::string str) {
   this->myID = str;
}

std::string ParameterID::GetParameter() {
   return this->myID;
}

std::string ParameterID::GetTokenType() {
   return "ID";
}
