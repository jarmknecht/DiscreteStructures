//
//  parameterID.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef parameterID_h
#define parameterID_h

#include "parameter.h"


class ParameterID: public Parameter {
   
public:
   ParameterID();
   ~ParameterID();
   ParameterID(std::string str);
   std::string GetParameter();
   std::string GetTokenType();
   
   std::string toString();
   
private:
   std::string myID;
};

#endif /* parameterID_h */
