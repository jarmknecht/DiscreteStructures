//
//  tests.cpp
//  Relation
//
//  Created by Jonathan Armknecht on 7/16/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

#include "Relation.h"

using namespace std;

/* Tests for project rename and select
 void Test1() {//Test 1 checks to see if Select function will return the correct relation of a with just ac
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   
   Relation* newSelect = r.Select(r, 0, "a");
   
   if (newSelect->ToString() == "Relation SK\nA, B\nac\n") {
      cout << "Test 1 Passed!" << endl;
   }
   else {
      cout << "Test 1 failed.." << endl;
   }
   
   delete newSelect;
}

void Test2() { //Tests to see if a query for SK(A, 'c')? works correctly after a selection on c and projection on scheme A
   
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 1, "c");
   
   vector<int> columns;
   columns.push_back(0);
   
   Relation* newProject = newSelect->Project(*newSelect, columns);
   
   if (newProject->ToString() == "Relation SK\nA\na\nb\n") {
      cout << "Test 2 Passed!" << endl;
   }
   else {
      cout << "Test 2 failed.." << endl;
   }
   
   delete newProject;
   delete newSelect;
}

void Test3() {//Testing the query for SK('b',B)? should return b and c in schema B
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 0, "b");
   
   vector<int> columns;
   columns.push_back(1);
   
   Relation* newProject = newSelect->Project(*newSelect, columns);
   
   if (newProject->ToString() == "Relation SK\nB\nb\nc\n") {
      cout << "Test 3 Passed!" << endl;
   }
   else {
      cout << "Test 3 failed.." << endl;
   }
   
   delete newProject;
   delete newSelect;
}

void Test4() {//Testing the QUERY for SK(A,'b','c')? should return a and b in schema A
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   myStrings.push_back("d");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   myStrings.push_back("e");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("a");
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   vector<int> columns;
   columns.push_back(0);
   
   Relation* newSelect = r.Select(r, 2, "c"); //find c first
   
   Relation* newSelect2 = newSelect->Select(*newSelect, 1, "b"); //find b second
   
   Relation* newProject = newSelect2->Project(*newSelect2, columns); //find what A is
   
   if (newProject->ToString() == "Relation SK\nA\na\nb\n") {
      cout << "Test 4 Passed!" << endl;
   }
   else {
      cout << "Test 4 failed.." << endl;
   }
   
   delete newProject;
   delete newSelect;
   delete newSelect2;
}

void Test5() { //Testing the QUERY for SK(A,B)? should return a b b in schema A and c b c in schema B, makes sure that duplicate facts are not stored in the relation
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   if (r.ToString() == "Relation SK\nA, B\nac\nbb\nbc\n") {
      cout << "Test 5 Passed!" << endl;
   }
   else {
      cout << "Test 5 failed.." << endl;
   }
}

void Test6() { //Testing the QUERY for ab('joe', 'jim')? should return just the relation with only joe and jim in it
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("joe");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("jim");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("joe");
   myStrings.push_back("jim");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("bob");
   myStrings.push_back("bob");
   tuples.insert(myStrings);

   Relation r("Relation ab", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 1, "jim"); //find all tuples with jim in the second place
   
   Relation* newSelect2 = newSelect->Select(*newSelect, 0, "joe"); //out of those tuples find where joe is first
   
   if (newSelect2->ToString() == "Relation ab\nA, B\njoejim\n") {
      cout << "Test 6 Passed!" << endl;
   }
   else {
      cout << "Test 6 failed.." << endl;
   }
   delete newSelect;
   delete newSelect2;
}

void Test7() { //Testing the QUERY for ab('joe', anyone)? should return bob and jim as schema of anyone tests the select, rename, and project functions all at one
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("joe");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("jim");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("joe");
   myStrings.push_back("jim");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("bob");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   Relation r("Relation ab", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 0, "joe"); //looking for joe in first place
   
   vector<string> newNames;
   newNames.push_back("A");
   newNames.push_back("anyone");
   
   Relation* newRename = newSelect->Rename(*newSelect, newNames); //rename B to anybody
   
   vector<int> columns;
   columns.push_back(1);
   
   Relation* newProject = newRename->Project(*newRename, columns);
   
   if (newProject->ToString() == "Relation ab\nanyone\nbob\njim\n") {
      cout << "Test 7 Passed!" << endl;
   }
   else {
      cout << "Test 7 failed.." << endl;
   }
   
   delete newSelect;
   delete newRename;
   delete newProject;
}

void Test8() {//checks to make sure project can project more than one column at once
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("joe");
   myStrings.push_back("bob");
   myStrings.push_back("jon");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("jim");
   myStrings.push_back("bob");
   myStrings.push_back("jonathan");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("joe");
   myStrings.push_back("jim");
   myStrings.push_back("john");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("bob");
   myStrings.push_back("bob");
   myStrings.push_back("jb");
   tuples.insert(myStrings);
   
   Relation r("Relation ab", mySchemes, tuples);
   
   vector<int> columns;
   columns.push_back(0);
   columns.push_back(2);
   
   Relation* newProject = r.Project(r, columns); //will only project facts from schema A and C
   
   if (newProject->ToString() == "Relation ab\nA, C\nbobjb\njimjonathan\njoejohn\njoejon\n") {
      cout << "Test 8 Passed!" << endl;
   }
   else {
      cout << "Test 8 failed.." << endl;
   }
   
   delete newProject;
}

void Test9() {//checks to make sure rename can rename more than one column at once while keeping the middle one the same
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("joe");
   myStrings.push_back("bob");
   myStrings.push_back("jon");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("jim");
   myStrings.push_back("bob");
   myStrings.push_back("jonathan");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("joe");
   myStrings.push_back("jim");
   myStrings.push_back("john");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("bob");
   myStrings.push_back("bob");
   myStrings.push_back("jb");
   tuples.insert(myStrings);
   
   Relation r("Relation ab", mySchemes, tuples);
   
   vector<string> newNames;
   newNames.push_back("J");
   newNames.push_back("B");
   newNames.push_back("Z");
   
   Relation* newRename = r.Rename(r, newNames);
   
   if (newRename->ToString() == "Relation ab\nJ, B, Z\nbobbobjb\njimbobjonathan\njoebobjon\njoejimjohn\n") {
      cout << "Test 9 Passed!" << endl;
   }
   else {
      cout << "Test 9 failed.." << endl;
   }
   delete newRename;
}

void Test10() {//checks to make sure it can handle a QUERY with two relations made employer('ralph','howard')?
   vector<string> mySchemes;
   mySchemes.push_back("person1");
   mySchemes.push_back("person2");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("joe");
   myStrings.push_back("bob");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("jamie");
   myStrings.push_back("ken");
   tuples.insert(myStrings);
   
   Relation r1("Relation people", mySchemes, tuples);
   
   mySchemes.clear();
   mySchemes.push_back("boss");
   mySchemes.push_back("employee");
   tuples.clear();
   myStrings.clear();
   myStrings.push_back("ralph");
   myStrings.push_back("howard");
   tuples.insert(myStrings);
   
   Relation r2("Relation employer", mySchemes, tuples);
   
   Relation* newSelect = r2.Select(r2, 1, "howard"); //find howard first in the second position
   
   Relation* newSelect2 = newSelect->Select(*newSelect, 0, "ralph"); //find ralph as boss in first position
   
   if (newSelect2->ToString() == "Relation employer\nboss, employee\nralphhoward\n") {
      cout << "Test 10 Passed!" << endl;
   }
   else {
      cout << "Test 10 failed.." << endl;
   }
   
   delete newSelect;
   delete newSelect2;
}

void Test11() { //checks to make sure a QUERY of SK(X,X)? returns just b in schema A and B
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 0, 1);
   
   if (newSelect->ToString() == "Relation SK\nA, B\nbb\n") {
      cout << "Test 11 Passed!" << endl;
   }
   else {
      cout << "Test 11 failed.." << endl;
   }
   
   delete newSelect;
}

void Test12() { //checks to make sure a QUERY of SK(X,X,"c",X) returns a a c a
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   mySchemes.push_back("D");

   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("a");
   myStrings.push_back("c");
   myStrings.push_back("a");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("a");
   myStrings.push_back("c");
   myStrings.push_back("a");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   myStrings.push_back("a");
   myStrings.push_back("a");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("a");
   myStrings.push_back("d");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSelect = r.Select(r, 0, 1);
   
   Relation* newSelect2 = newSelect->Select(*newSelect, 0, 3);
   
   Relation* newSelect3 = newSelect2->Select(*newSelect2, 2, "c");
   
   if (newSelect3->ToString() == "Relation SK\nA, B, C, D\naaca\n") {
      cout << "Test 12 Passed!" << endl;
   }
   else {
      cout << "Test 12 failed.." << endl;
   }
   
   delete newSelect;
   delete newSelect2;
   delete newSelect3;
}

void Test13() {
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSingleSelect = r.SingleIDSelect(r, 0, 1);
   
   cout << newSingleSelect->ToString();
   
   delete newSingleSelect;
}

void Test14() {
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("b");
   myStrings.push_back("a");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("Relation SK", mySchemes, tuples);
   
   Relation* newSingleSelect = r.SingleIDSelect(r, 0, 1);
   
   Relation* newSingleSelect2 = newSingleSelect->SingleIDSelect(*newSingleSelect, 0, 2);
   
   Relation* newSingleSelect3 = newSingleSelect2->SingleIDSelect(*newSingleSelect2, 1, 2);
   
   cout << newSingleSelect3->ToString();
   
   delete newSingleSelect;
   delete newSingleSelect2;
   delete newSingleSelect3;
}*/

void Test1() { //Tests to make sure it can union two relations together correctly
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("b");
   myStrings.push_back("c");
   tuples.insert(myStrings);
   
   Relation r("SK", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("B");
   mySchemes2.push_back("A");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("z");
   myStrings2.push_back("j");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("e");
   myStrings2.push_back("4");
   tuples2.insert(myStrings2);
   
   Relation r2("KS", mySchemes2, tuples2);
   
   Relation* rUnion = r.Union(r, r2);
   
   if (rUnion->ToString() == "SK U KS\nA, B\nac\nbc\ne4\nzj\n") {
      cout << "Test 1 Passed!" << endl;
   }
   else {
      if (rUnion == NULL) {
         cout << "Cannot union these two relations. Schema don't match!" << endl;
      }
      cout << "Test 1 failed.." << endl;
   }
   
   delete rUnion;
}

void Test2() { //Tests to see if union works and calls rename when the schema don't match
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("J");
   mySchemes.push_back("X");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("b");
   myStrings.push_back("c");
   myStrings.push_back("d");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("e");
   myStrings.push_back("f");
   myStrings.push_back("g");
   myStrings.push_back("h");
   tuples.insert(myStrings);
   
   Relation r("SK", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("B");
   mySchemes2.push_back("A");
   mySchemes2.push_back("Z");
   mySchemes2.push_back("J");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("i");
   myStrings2.push_back("j");
   myStrings2.push_back("k");
   myStrings2.push_back("l");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("m");
   myStrings2.push_back("n");
   myStrings2.push_back("o");
   myStrings2.push_back("p");
   tuples2.insert(myStrings2);
   
   Relation r2("KS", mySchemes2, tuples2);
   
   Relation* rUnion = r.Union(r, r2);
   
   if (rUnion->ToString() == "SK U KS\nA, B, J, X\nabcd\nefgh\nijkl\nmnop\n") {
      cout << "Test 2 Passed!" << endl;
   }
   
   else {
      cout << "Test 2 failed.." << endl;
   }
   
   delete rUnion;
}

void Test3() { //Tests to make sure the Cartesian Product works correctly when schemas don't match
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("a");
   myStrings.push_back("b");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("c");
   myStrings.push_back("d");
   tuples.insert(myStrings);
   
   Relation r("SK", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("D");
   mySchemes2.push_back("E");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("e");
   myStrings2.push_back("f");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("g");
   myStrings2.push_back("h");
   tuples2.insert(myStrings2);
   
   Relation r2("KS", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "SK |x| KS\nA, B, D, E\nabef\nabgh\ncdef\ncdgh\n") {
      cout << "Test 3 Passed!" << endl;
   }
   
   else {
      cout << "Test 3 failed.." << endl;
   }

   delete newJoin;
}

void Test4() { //Tests the natural join function to make sure it can handle joining just one overlapping schema
   vector<string> mySchemes;
   mySchemes.push_back("X");
   mySchemes.push_back("Y");
   mySchemes.push_back("Z");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("1");
   myStrings.push_back("2");
   myStrings.push_back("3");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("1");
   myStrings.push_back("2");
   myStrings.push_back("2");
   tuples.insert(myStrings);
   
   Relation r("SK", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Z");
   mySchemes2.push_back("J");
   mySchemes2.push_back("R");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("3");
   myStrings2.push_back("4");
   myStrings2.push_back("5");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("1");
   myStrings2.push_back("2");
   myStrings2.push_back("4");
   tuples2.insert(myStrings2);
   
   Relation r2("KS", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "SK |x| KS\nX, Y, Z, J, R\n12345\n") {
      cout << "Test 4 Passed!" << endl;
   }
   else {
      cout << "Test 4 failed.." << endl;
   }
   
   delete newJoin;
}

void Test5() {//Tests the natural join function where two of the schemas overlap
   vector<string> mySchemes;
   mySchemes.push_back("X");
   mySchemes.push_back("Y");
   mySchemes.push_back("Z");
   mySchemes.push_back("W");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("1");
   myStrings.push_back("2");
   myStrings.push_back("3");
   myStrings.push_back("4");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("2");
   myStrings.push_back("2");
   myStrings.push_back("2");
   myStrings.push_back("7");
   tuples.insert(myStrings);
   
   Relation r("PS", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Z");
   mySchemes2.push_back("J");
   mySchemes2.push_back("R");
   mySchemes2.push_back("X");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("3");
   myStrings2.push_back("4");
   myStrings2.push_back("5");
   myStrings2.push_back("1");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("3");
   myStrings2.push_back("2");
   myStrings2.push_back("9");
   myStrings2.push_back("1");
   tuples2.insert(myStrings2);
   
   Relation r2("TY", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "PS |x| TY\nX, Y, Z, W, J, R\n123429\n123445\n") {
      cout << "Test 5 Passed!" << endl;
   }
   else {
      cout << "Test 5 failed.." << endl;
   }
   
   delete newJoin;
}

void Test6() {//Tests to make sure natural join can join two relations that do not have same size of schema
   vector<string> mySchemes;
   mySchemes.push_back("X");
   mySchemes.push_back("Y");
   mySchemes.push_back("Z");
   mySchemes.push_back("W");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("1");
   myStrings.push_back("2");
   myStrings.push_back("3");
   myStrings.push_back("4");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("2");
   myStrings.push_back("2");
   myStrings.push_back("2");
   myStrings.push_back("7");
   tuples.insert(myStrings);
   
   Relation r("PS", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Z");
   mySchemes2.push_back("X");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("3");
   myStrings2.push_back("1");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("1");
   myStrings2.push_back("2");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("5");
   myStrings2.push_back("6");
   tuples2.insert(myStrings2);
   
   Relation r2("TY", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "PS |x| TY\nX, Y, Z, W\n1234\n") {
      cout << "Test 6 Passed!" << endl;
   }
   else {
      cout << "Test 6 failed.." << endl;
   }

   delete newJoin;
}

void Test7() {//Tests the natural join that when both of the schemas are the same in both relations that it just produces a relation based on an intersection of the two
   vector<string> mySchemes;
   mySchemes.push_back("X");
   mySchemes.push_back("Z");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("1");
   myStrings.push_back("2");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("3");
   myStrings.push_back("4");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("2");
   myStrings.push_back("2");
   tuples.insert(myStrings);
   
   Relation r("PS", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Z");
   mySchemes2.push_back("X");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("2");
   myStrings2.push_back("1");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("4");
   myStrings2.push_back("3");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("5");
   myStrings2.push_back("6");
   tuples2.insert(myStrings2);
   
   Relation r2("TY", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "PS |x| TY\nX, Z\n12\n34\n") {
      cout << "Test 7 Passed!" << endl;
   }
   else {
      cout << "Test 7 failed.." << endl;
   }
   
   delete newJoin;
}

void Test8() {//Tests natural join with having all the same schema except for one in the first relation
   vector<string> mySchemes;
   mySchemes.push_back("A");
   mySchemes.push_back("B");
   mySchemes.push_back("C");
   mySchemes.push_back("D");
   mySchemes.push_back("E");
   mySchemes.push_back("X");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("1");
   myStrings.push_back("2");
   myStrings.push_back("3");
   myStrings.push_back("4");
   myStrings.push_back("5");
   myStrings.push_back("6");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("7");
   myStrings.push_back("8");
   myStrings.push_back("9");
   myStrings.push_back("10");
   myStrings.push_back("11");
   myStrings.push_back("12");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("7");
   myStrings.push_back("7");
   myStrings.push_back("7");
   myStrings.push_back("7");
   myStrings.push_back("7");
   myStrings.push_back("2");
   tuples.insert(myStrings);
   
   Relation r("PS", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Z");
   mySchemes2.push_back("A");
   mySchemes2.push_back("B");
   mySchemes2.push_back("C");
   mySchemes2.push_back("D");
   mySchemes2.push_back("E");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("6");
   myStrings2.push_back("1");
   myStrings2.push_back("2");
   myStrings2.push_back("3");
   myStrings2.push_back("4");
   myStrings2.push_back("5");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("4");
   myStrings2.push_back("7");
   myStrings2.push_back("8");
   myStrings2.push_back("9");
   myStrings2.push_back("10");
   myStrings2.push_back("11");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("a");
   myStrings2.push_back("7");
   myStrings2.push_back("7");
   myStrings2.push_back("7");
   myStrings2.push_back("7");
   myStrings2.push_back("1");
   tuples2.insert(myStrings2);
   
   Relation r2("TY", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "PS |x| TY\nA, B, C, D, E, X, Z\n1234566\n7891011124\n") {
      cout << "Test 8 Passed!" << endl;
   }
   else {
      cout << "Test 8 failed.." << endl;
   }
   
   delete newJoin;
}

void Test9() {//Tests natural join with having every other schema match
   vector<string> mySchemes;
   mySchemes.push_back("Name");
   mySchemes.push_back("Hair");
   mySchemes.push_back("Eyes");
   mySchemes.push_back("Age");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("Jon");
   myStrings.push_back("Brown");
   myStrings.push_back("Hazel");
   myStrings.push_back("26");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("Bo");
   myStrings.push_back("Blonde");
   myStrings.push_back("Blue");
   myStrings.push_back("24");
   tuples.insert(myStrings);
   
   Relation r("Student", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Name");
   mySchemes2.push_back("Car");
   mySchemes2.push_back("Eyes");
   mySchemes2.push_back("Subject");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("Jon");
   myStrings2.push_back("Mustang");
   myStrings2.push_back("Hazel");
   myStrings2.push_back("CS");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("Jim");
   myStrings2.push_back("Ford");
   myStrings2.push_back("Blue");
   myStrings2.push_back("Biology");
   tuples2.insert(myStrings2);
   
   Relation r2("Teacher", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   if (newJoin->ToString() == "Student |x| Teacher\nName, Hair, Eyes, Age, Car, Subject\nJonBrownHazel26MustangCS\n") {
      cout << "Test 9 Passed!" << endl;
   }
   else {
      cout << "Test 9 failed.." << endl;
   }
   
   delete newJoin;
}

void Test10() {//Tests natural join with the project function
   vector<string> mySchemes;
   mySchemes.push_back("Name");
   mySchemes.push_back("Hair");
   mySchemes.push_back("Eyes");
   mySchemes.push_back("Age");
   
   set<vector<string>> tuples;
   vector<string> myStrings;
   
   myStrings.push_back("Jon");
   myStrings.push_back("Brown");
   myStrings.push_back("Hazel");
   myStrings.push_back("26");
   tuples.insert(myStrings);
   
   myStrings.clear();
   myStrings.push_back("Bo");
   myStrings.push_back("Blonde");
   myStrings.push_back("Blue");
   myStrings.push_back("24");
   tuples.insert(myStrings);
   
   Relation r("Student", mySchemes, tuples);
   
   vector<string> mySchemes2;
   mySchemes2.push_back("Name");
   mySchemes2.push_back("Car");
   mySchemes2.push_back("Eyes");
   mySchemes2.push_back("Subject");
   
   set<vector<string>> tuples2;
   vector<string> myStrings2;
   
   myStrings2.push_back("Jon");
   myStrings2.push_back("Mustang");
   myStrings2.push_back("Hazel");
   myStrings2.push_back("CS");
   tuples2.insert(myStrings2);
   
   myStrings2.clear();
   myStrings2.push_back("Jim");
   myStrings2.push_back("Ford");
   myStrings2.push_back("Blue");
   myStrings2.push_back("Biology");
   tuples2.insert(myStrings2);
   
   Relation r2("Teacher", mySchemes2, tuples2);
   
   Relation* newJoin = r.Join(r, r2);
   
   std::vector<int> columns;
   columns.push_back(0);
   columns.push_back(3);
   
   
   Relation* newProject = newJoin->Project(*newJoin, columns);
   
   if (newProject->ToString() == "Student |x| Teacher\nName, Age\nJon26\n") {
      cout << "Test 10 Passed!" << endl;
   }
   else {
      cout << "Test 10 failed.." << endl;
   }
   
   delete newJoin;
   delete newProject;
}

int main(int argc, const char * argv[]) {
   
   /*
   Tests for part 1 with select project and rename
   Test1(); //Test 1 checks to see if Select function will return the correct relation of a with just ac
   Test2(); //Tests to see if a QUERY for SK(A, 'c')? works correctly after a selection on c and projection on scheme A
   Test3(); //Testing the QUERY for SK('b',B)? should return b and c in schema B
   Test4(); //Testing the QUERY for SK(A,'b','c')? should return a and b in schema A
   Test5(); //Testing the QUERY for SK(A,B)? should return a b b in schema A and c b c in schema B, makes sure that duplicate facts are not stored in the relation
   Test6(); //Testing the QUERY for ab('joe', 'jim')? should return just the relation with only joe and jim in it
   Test7(); //Testing the QUERY for ab('joe', anyone)? should return bob and jim as schema of anyone tests the select, rename, and project functions all at one
   Test8(); //checks to make sure project can project more than one column at once
   Test9(); //checks to make sure rename can rename more than one column at once while keeping the middle one the same
   Test10(); //checks to make sure it can handle a QUERY with two relations made employer('ralph','howard')?
   Test11(); //checks to make sure a QUERY of SK(X,X)? returns just b in schema A and B
   Test12(); //checks to make sure a QUERY of SK(X,X,"c",X) returns a a c a
   Test13();
   Test14();*/
   
   Test1(); //Tests to make sure it can union two relations together correctly
   Test2(); //Tests to see if union works and calls rename when the schema don't match
   Test3(); //Tests to make sure the Cartesian Product works correctly when schemas don't match
   Test4(); //Tests the natural join function to make sure it can handle joining just one overlapping schema
   Test5(); //Tests the natural join function where two of the schemas overlap
   Test6(); //Tests to make sure natural join can join two relations that do not have same size of schema
   Test7(); //Tests the natural join that when both of the schemas are the same in both relations that it just produces a relation based on an intersection of the two
   Test8(); //Tests natural join with having all the same schema except for one in the first relation
   Test9(); //Tests natural join with having every other schema match
   Test10(); //Tests natural join with the project function
   
   
   return 0;
}
