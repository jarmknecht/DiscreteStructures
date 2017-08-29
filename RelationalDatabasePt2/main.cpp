//
//  main.cpp
//  LexicalAnalyzer Project 1 CS 236
//
//  Created by Jonathan Armknecht on 7/1/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Lexer.h"
#include "Token.h"
#include "datalogProgram.h"
#include "Parser.h"
#include "Database.h"

#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

int main(int argc, const char * argv[]) {
   
   Lexer myLexer;
   bool fileIsOpen = false;
   string fileName = argv[1];
   
   //string fileName = "test9.txt";
   
   fileIsOpen = myLexer.ReadFile(fileName);
   
   if (!fileIsOpen) {
      return 0; //program failed to read the file and ends
   }
   
   //cout << myLexer.ToString();
   
   
   try {
      Parser myParser(myLexer.GetVector());
      myParser.ParseInput();
   }
   
   catch (string str) {
      cout << "Failure!" << endl << "  " << str << endl;
   }

    return 0;
}
