//
//  expressions.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/8/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "expressions.h"
#include <sstream>

Expressions::Expressions() {
   
}

Expressions::~Expressions() {
   delete leftParameter;
   delete rightParameter;
}

std::string Expressions::GetParameter() {
   std::stringstream toString;
   
   toString << "(" << this->leftParameter->GetParameter() << this->myOperator << this->rightParameter->GetParameter() << ")";
   
   return toString.str();
}

Expressions::Expressions(Parameter* leftParam, std::string myOp, Parameter* rightParam) {
   this->leftParameter = leftParam;
   this-> myOperator = myOp;
   this->rightParameter = rightParam;
}
