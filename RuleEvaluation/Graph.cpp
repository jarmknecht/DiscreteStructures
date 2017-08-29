//
//  Graph.cpp
//  LexicalAnalyzer
//
//  Created by Jonathan Armknecht on 8/5/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Graph.h"

Graph::Graph() {
   
}

Graph::~Graph() {
   for (unsigned int i = 0; i < this->forward_tree.size(); i++) {
      delete this->forward_tree.at(i);
      this->forward_tree.at(i) = NULL;
   }
   for (unsigned int i = 0; i < this->backward_tree.size(); i++) {
      delete this->backward_tree.at(i);
      this->backward_tree.at(i) = NULL;
   }
}

Graph::Graph(std::vector<Rule*> rs) {
   //this is assigning an ID to each rule
   
   for (unsigned int i = 0; i < rs.size(); i++) {
      std::stringstream ss;
      ss.clear();
      std::string ID = "";
      ss << "R" << i;
      ID = ss.str();
      
      rs.at(i)->ID = ID;
      
      Node* forwardNode = new Node(ID);
      Node* backwardNode = new Node(ID);
      this->rules.push_back(rs.at(i));
      this->forward_tree.push_back(forwardNode);
      this->backward_tree.push_back(backwardNode);
   }
   this->BuildTrees();
   this->BuildPostOrder();
}

/*bool Graph::CheckPredParasToHeadPredParas(std::vector<Predicate*> preds, std::vector<std::string> headPred) {
   bool reflexiveRule = false;
   std::vector<std::string> headPredIDs;
   std::vector<std::string> predIDs;
   
   headPredIDs = headPred;
   
   for (unsigned int i = 0; i < preds.size(); i++) {
      for (unsigned int j = 0; j < preds.at(i)->parameters.size(); j++) {
         predIDs.push_back(preds.at(i)->parameters.at(j)->GetParameter());
      }
   }
   
   for (unsigned int l = 0; l < predIDs.size(); l++) {
      for (unsigned int k = l + 1; k < predIDs.size() - 1; k++) {
         if (predIDs.at(l) == predIDs.at(k)) {
            predIDs.erase(predIDs.begin() + k);
         }
      }
   }
   
   if (headPredIDs == predIDs) {
      reflexiveRule = true;
   }
   
   return reflexiveRule;
}*/

void Graph::BuildTrees() { //children added here
   //this function builds both forward and backward adjacency lists
   for (unsigned int i = 0; i < this->rules.size(); i++) {
      for (unsigned int j = 0; j < this->rules.at(i)->predicates.size(); j++) {
         for (unsigned int k = 0; k < this->rules.size(); k++) {
            std::string predID = this->rules.at(i)->predicates.at(j)->leftId;
            std::string ruleID = this->rules.at(k)->myHeadPredicate->leftId;
            if (predID == ruleID) {
                  this->forward_tree.at(i)->AddChild(this->forward_tree.at(k));
                  this->backward_tree.at(k)->AddChild(this->backward_tree.at(i));
            }
         }
      }
   }
   
   std::cout << "Dependency Graph" << std::endl;
   
   //print just the forward tree
   for (unsigned int i = 0; i < this->forward_tree.size(); i++) {
      std::cout << this->forward_tree.at(i)->ID << ":";
      for (unsigned int j = 0; j < this->forward_tree.at(i)->children.size(); j++) {
         if (j > 0) {
            std::cout << ",";
         }
         std::cout << this->forward_tree.at(i)->children.at(j)->ID;
      }
      std::cout << std::endl;
   }
}

void Graph::BuildPostOrder() {
   for (unsigned int i = 0; i < this->backward_tree.size(); i++) {
      Node* node = this->backward_tree.at(i);
      if (!node->visited) {
         this->DFSStack(node);
      }
   }
}

std::vector<std::vector<Rule*>> Graph::StrongConnections() {
   std::vector<std::vector<Rule*>> forest;
   
   while (this->postorder.size()) {
      Node* backward_node = postorder.top();
      postorder.pop();
      Node* forward_node = this->FindNodeByID(backward_node->ID);
      if (!forward_node->visited) {
         forest.push_back(this->dfsVector(forward_node));
      }
   }
   return this->SortForest(forest);
}

std::vector<std::vector<Rule*>> Graph::SortForest(std::vector<std::vector<Rule *> > trees) {
   for (unsigned int i = 0; i < trees.size(); i++) {
      for (unsigned int j = 0; j < trees.at(i).size(); j++) {
         for (unsigned int k = j + 1; k < trees.at(i).size(); k++) {
            if (trees.at(i).at(j)->ID > trees.at(i).at(k)->ID) {
               Rule* temp = trees.at(i).at(j);
               trees.at(i).at(j) = trees.at(i).at(k);
               trees.at(i).at(k) = temp;
            }
         }
      }
   }
   return trees;
}

void Graph::DFSStack(Node *n) {
   n->visited = true;
   for (unsigned int i = 0; i < n->children.size(); i++) {
      if (!n->children.at(i)->visited) {
         DFSStack(n->children.at(i));
      }
   }
   this->postorder.push(n);
}

std::vector<Rule*> Graph::dfsVector(Node *n) {
   n->visited = true;
   std::vector<Rule*> tree;
   tree.push_back(this->FindRuleByID(n->ID));
   for (unsigned int i = 0; i < n->children.size(); i++) {
      if (n->children.at(i) == n) {
         tree.back()->reflexive = true;
      }
      if (!n->children.at(i)->visited) {
         std::vector<Rule*> subTree = dfsVector(n->children.at(i));
         tree.insert(tree.end(), subTree.begin(), subTree.end());
      }
   }
   return tree;
}

Node* Graph::FindNodeByID(std::string ID) {
   for (unsigned int i = 0; i < this->forward_tree.size(); i++) {
      if (ID == this->forward_tree.at(i)->ID) {
         return this->forward_tree.at(i);
      }
   }
   return NULL;
}

Rule* Graph::FindRuleByID(std::string name) {
   for (unsigned int i = 0; i < this->rules.size(); i++) {
      if (name == this->rules.at(i)->ID) {
         return this->rules.at(i);
      }
   }
   return NULL;
}
