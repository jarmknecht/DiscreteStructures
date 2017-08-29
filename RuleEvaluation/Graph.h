//
//  Graph.h
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 8/5/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include "Node.h"
#include "Database.h"
#include <stack>

class Graph {
public:
   Graph();
   Graph(std::vector<Rule*> rs);
   ~Graph();
   
   std::vector<std::vector<Rule*>> StrongConnections();
   
private:
   void BuildTrees();
   void BuildPostOrder();
   //bool CheckPredParasToHeadPredParas(std::vector<Predicate*> preds, std::vector<std::string> headPred);
   void DFSStack(Node* n);
   std::vector<Rule*> dfsVector(Node* n);
   Node* FindNodeByID(std::string ID);
   Rule* FindRuleByID(std::string name);
   
   std::vector<std::vector<Rule*>> SortForest(std::vector<std::vector<Rule*>> trees);
   
   std::vector<Rule*> rules;
   std::vector<Node*> forward_tree;
   std::vector<Node*> backward_tree;
   std::stack<Node*> postorder;
};


#endif /* Graph_h */
