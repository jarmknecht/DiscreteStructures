//
//  expressions.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef expressions_h
#define expressions_h

#include "parameter.h"

class Expressions: public Parameter {

public:
   Expressions();
   ~Expressions();
   Expressions(Parameter* leftParam, std::string myOp, Parameter* rightParam);
   std::string GetParameter();
   
   std::string myOperator;
   Parameter* leftParameter;
   Parameter* rightParameter;
};

#endif /* expressions_h */
