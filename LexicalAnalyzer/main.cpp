//
//  main.cpp
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Lexer.h"
#include "Token.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
   
   Lexer myLexer;
   bool fileIsOpen = false;
   string fileName = argv[1];
   
   fileIsOpen = myLexer.ReadFile(fileName);
   
   if (!fileIsOpen) {
      return 0; //program failed to read the file and ends
   }
   
   cout << myLexer.ToString();
      
    return 0;
}
