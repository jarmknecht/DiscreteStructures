//
//  Node.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 8/5/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Node.h"

Node::Node() {
   this->ID = "";
   this->visited = false;
}

Node::~Node() {
   
}

Node::Node(std::string ID) {
   this->ID = ID;
   this->visited = false;
}

bool Node::AddChild(Node* node) {
   if (this->FindByID(node->ID) != NULL) { //no duplicates
      return false;
   }
   if (this->children.size() == 0) {
      this->children.push_back(node);
      return true;
   }
   for (unsigned int i = 0; i < this->children.size(); i++) {
      if (node->ID < (this->children.at(i)->ID)) {
         this->children.insert(this->children.begin() + i, node);
         return true;
      }
   }
   this->children.push_back(node);
   return true;
}

Node* Node::FindByID(std::string ID) {
   for (unsigned int i = 0; i < this->children.size(); i++) {
      if (ID == this->children.at(i)->ID) {
         return this->children.at(i);
      }
   }
   return NULL;
}
