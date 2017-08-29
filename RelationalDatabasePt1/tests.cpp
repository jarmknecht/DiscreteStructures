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

int main(int argc, const char * argv[]) {
   
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
   
   return 0;
}
