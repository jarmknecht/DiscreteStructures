//
//  parameter.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 7/9/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef parameter_h
#define parameter_h

#include <string>


class Parameter {
public:
   Parameter();
   virtual ~Parameter();
   virtual std::string GetParameter() = 0;
   virtual std::string GetTokenType() = 0;
};

#endif /* parameter_h */
