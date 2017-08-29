//
//  parameterString.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "parameterString.h"

ParameterString::ParameterString() {
   
}

ParameterString::~ParameterString() {
   
}

ParameterString::ParameterString(std::string str) {
   this->STRING = str;
}

std::string ParameterString::GetParameter() {
   return this->STRING;
}

/*void ParameterString::SetParameter(std::string s) {
   this->STRING = s;
}*/

std::string ParameterString::GetTokenType() {
   return "STRING";
}
