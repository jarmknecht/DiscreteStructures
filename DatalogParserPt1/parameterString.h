//
//  parameterString.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef parameterString_h
#define parameterString_h

#include "parameter.h"

class ParameterString: public Parameter {

public:
   ParameterString();
   ~ParameterString();
   ParameterString(std::string str);
   std::string GetParameter();
   std::string toString();

private:
   std::string STRING;
};


#endif /* parameterString_h */
