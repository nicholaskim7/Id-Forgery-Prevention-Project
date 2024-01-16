#include <iostream>
#include <algorithm>
#include "ArgumentManager.h"
#include <stack>
#include <queue>
#include "ll.h"
using namespace std;

int main(int argc, char* argv[]) {
  // *** You need to open files using argumentmanager when submit your assignment ***
   ArgumentManager am(argc, argv);
   ifstream input(am.get("input"));
   ofstream out(am.get("output"));
 // ifstream input("input13.txt");
 // ofstream out("output13.txt");
  string inStr = "";
  string idStr = "";
  int pCount = 0;
  stack<char> s;
  queue<char> q;
  string temp = "";
  linkedList bar1, bar2, guilty, innocent;
  bool addBar1 = false;
  bool addBar2 = false;

  while(getline(input, inStr)) {
    inStr.erase(remove(inStr.begin(), inStr.end(), '\n'), inStr.end());
    inStr.erase(remove(inStr.begin(), inStr.end(), '\r'), inStr.end());
    if(inStr.size()==0){
      continue;  
    }

    if (inStr.length() >= 3) {
      if (inStr.substr(0,4) == "Bar1") {
        addBar1 = true;
        addBar2 = false;
        continue;
      }
      if (inStr.substr(0,4) == "Bar2") {
        addBar1 = false;
        addBar2 = true;
        continue;
      }
    }
    
    for(int i = 0; i < inStr.length(); i++){
      if(pCount == 0 && isdigit(inStr[i])){
        idStr += inStr[i];
      }
      else if(inStr[i] == '('){
        s.push('(');
        pCount++;
      }
      else if(pCount > 0 && isdigit(inStr[i])){ 
        s.push(inStr[i]);
      }
      else if(inStr[i] == ')' && pCount > 1){
        if(inStr[i] != ')'){
          s.push(inStr[i]);
        }
        while(s.top() != '('){
          q.push(s.top());
          s.pop();
        }
        s.pop();
        while(!q.empty()){
          s.push(q.front());
          q.pop();
          //if(pCount > 0 && pCount <=2){
          if (pCount <= 1) { // in case of nested parentheses
            idStr += s.top();
          }
          //}
        }
        pCount--;
      }
      else{
        while(s.top() != '('){
          idStr += s.top();
          s.pop();
        }
        s.pop();
        pCount--;
      }
    }

 //   cout << idStr << endl;
    innocent.addToList(innocent.getHead(), idStr);
 //   innocent.addHead(idStr);

    
    if (addBar1 && !addBar2) {
      bar1.addToList(bar1.getHead(), idStr);
    } 
    if (!addBar1 && addBar2) { 
      bar2.addToList(bar2.getHead(), idStr);
    }
    idStr = "";
  } 

/*  cout << "Bar 1 IDs: ";
  bar1.print(bar1.getHead()); // prints out the ids in reverse input.
  //bar1.traverseLL(bar1.getHead());
  cout << endl;
  cout << "Bar 2 IDs: ";
  bar2.print(bar2.getHead());
  //bar2.traverseLL(bar2.getHead());
  cout << endl;
  bar1.sort(bar1.getHead());
  cout <<"Bar 1 Ids sorted: ";
  bar1.print(bar1.getHead());
  cout << endl;
  bar2.sort(bar2.getHead());
  cout <<"Bar 2 Ids sorted: ";
  bar2.print(bar2.getHead()); */
  //bar1.traverseLL(bar1.getHead());

//  innocent.deleteVal(innocent.getHead(), "1234");
//  cout << "Innocent before removal: " << endl; 
//  innocent.print(innocent.getHead());
  innocent.createGuilty(innocent.getHead(), guilty);
/*  if(guilty.getHead() != nullptr){
    cout << "Guilty: " << endl;
    guilty.print(out, guilty.getHead());
  }
  if(innocent.getHead() != nullptr){
    cout << "Innocent: " << endl; 
    innocent.print(out, innocent.getHead());
  }*/

  //i did the output file stuff we can test everything more deeply tmmrw --nicholas
  if(!innocent.isEmpty() && !guilty.isEmpty()){
    out << "Guilty: " << endl;
    guilty.outputFile(out, guilty.getHead());
    out << "Innocent: " << endl;
    innocent.outputFile(out, innocent.getHead());
  }
  else if(!innocent.isEmpty() && guilty.isEmpty()){
    out << "Innocent: " << endl;
    innocent.outputFile(out, innocent.getHead());
  }
  else if(innocent.isEmpty() && !guilty.isEmpty()){
    out << "Guilty: " << endl;
    guilty.outputFile(out, guilty.getHead());
  }

  
}

//ok so now we have the correct ids in the correct lists
//To Do List: - Implement addHead recursively    
//            - Sort lists
//            - Add duplicate IDs into guilty list and add other IDs into innocent list

// Possible to search up how to find duplicates in two lists to find guilty IDs i can ask my friend or the TA on thursday since he took DS last year

// Sort lists function was given by the TA but wasnt in recursive form, i tweaked it but highly unsure if it even works or not - Rodney

//sort list first then check for dupes
//yeah thatll be easier to check
