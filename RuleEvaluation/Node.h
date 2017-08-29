//
//  Node.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 8/5/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <set>
#include <string>
#include <vector>

class Node {
public:
   Node();
   Node(std::string ID);
   ~Node();
   
   bool AddChild(Node* node);
   Node* FindByID(std::string ID);
   
   bool visited;
   std::string ID;

   std::vector<Node*> children;
};


#endif /* Node_h */
