#include "ll.h"
# include <iostream>
#include <string>
using  namespace std;

linkedList::linkedList() {
  //head=tail=nullptr;
  head = nullptr;
  size = 0;
}

linkedList::~linkedList() {
  node *cur = head;
  while (!isEmpty()) {
    head = head->next;
    delete cur;
    cur = head;
  }
}


void linkedList::outputFile(ofstream &_output, node *head) {
  node *cur = head;
  if (cur != nullptr) {
    
    //   output << "Guilty: " << cur->id << endl;
    // 
    //if innocent
    //   output << "Innocent: " << cur->id << endl;
    // 
    _output << cur->id << endl;
    outputFile(_output, cur->next);
  }
}


void linkedList::sort(node *head){
  if(head->next == nullptr || head == nullptr) return;

  node *curr = head;
  node *next = curr->next;
  int idCurr = stoi(curr->id);
  int idNext = stoi(next->id);

  if(idCurr > idNext){
    string temp = curr->id;
    curr->id = next->id;
    next->id = temp;
  }

  sort(curr->next);
/*  node *curr = head;
  while(curr->next != nullptr){
    if(stoi(curr->id) > stoi(curr->next->id)){
      string temp = curr->id;
      curr->id = curr->next->id;
      curr->next->id = temp;
    }
    curr = curr->next;
  } */
}

void linkedList::print(node *head) {
  node *cur = head;
  if (head == nullptr) {
    return;
  }
  else {
    cout << cur->id << endl;
    return print(cur->next);
  }
}

void linkedList::addHead(string _id) {
  node* temp= new node;
  temp->id=_id;
  temp->next=nullptr;
  if(head==nullptr)
    head=temp;
  else{
    head->prev=temp;
    temp->next=head;
    head=temp;
  }
  size++;
}

//add to tail recursively and traversing recursively - nicholas

//I could not get it to work tho
/*node* linkedList::addToEnd(node* head, string _id){
  if(head == nullptr){
    node *elt = new node;
    elt->id = _id;
    elt->next = nullptr;
    return elt;
  }
  else{
    head->next = addToEnd(head->next, _id);
  }
  return head;
} */

void linkedList::addToEnd(node* headn, string _id){ //i got it working - mike
  // ONLY ITERATES THIS LOOP EVERTIME IT ITERATES - Jacob
  node *curr = headn;
  if(curr == nullptr){
    node *temp = new node;
    temp->id = _id;
    temp->next = nullptr;
    head = temp;
    size++;
    return;
  }

  
  if(curr->next == nullptr){
    node *temp = new node;
    temp->id = _id;
    temp->next = nullptr;
    curr->next = temp;
    size++; //do we ever even use size
    return;
  }

  addToEnd(curr->next, _id);

} 
//so what this function does is take in our head and the id as parameters. for the first iteration, head is nullptr so it sets the temp data with our id. The problem comes when we do the recursive call with curr->next which is head->next and when inputed back into the function, the head parameter is set to head->next, so thats our new head getting rid of the last one in the process. I hope this makes sense. - Jacob

void linkedList::traverseLL(node* head){
  node* curr = head;
  if(curr->next == nullptr){
    return;
  }
  traverseLL(head->next);
}


/*node* linkedList::deleteVal(node* head, string _id) { 
  node *cur = head;
  if (head == nullptr) {
    return;
  }
  if (stoll(head->id) == stoll(_id)) {
    head = head->next;
    return;
  }
  deleteVal(head->next, _id);
  return head;
}*/

void linkedList::addToList(node *cur, string _id) {
  if (isEmpty() || stoll(head->id) > stoll(_id)) {
    if (isEmpty()) {
      node *temp = new node;
      temp->id = _id; temp->prev = nullptr; temp->next = nullptr;
      head = tail = temp;
    }
    else {
      node *temp = new node;
      temp->id = _id; temp->prev = nullptr; temp->next = head;
      head->prev = temp;
      head = temp;
    }
  }
  else if (cur == nullptr) {
    node *temp = new node;
    temp->id = _id; temp->prev = tail; temp->next = nullptr;
    tail->next = temp;
    tail = temp;
  }
  else if (stoll(cur->id) > stoll(_id)) {
    node *temp = new node;
    temp->id = _id; temp->prev = cur->prev; temp->next = cur;
    cur->prev->next = temp;
    cur->prev = temp;
  }
  else {
    addToList(cur->next, _id);
  }
}

// do you need help w anything
//idk whats wrong w it
//is it just not adding 1234 to guilty? yea ok lemme see
// youre probably missing a condition for when curr == head
// damn im stumped
//i think its skipping over the last two some how
// do you wanna try adding another id in the input to see if something happens
//nvm idk whats going on
//yeah thats strange, its not skipping over and your function looks right
//yea its skipping 1234, it didnt evaluate them as equal
//there should be no issue with white space right? 
// yeah i dont see what could be causing it to skip 1234
//is it because that is the last input so there is no cur-> next?
// no its just skipping over 1234 entirely, it goes from 1010 to 2021
// what i think could possibly be the problem is that after it removes 1010, its not reading in 1234, idk how to explain it
//i think i see the problem nvm
//what i was thinking is that 1234 becomes the new head/curr and the function call moves it to the next 1234
// wait i think i see the issue, in line 216, when we set curr = cur->next->next, it then goes to cur->next again because of the recursion thing. i think only cur->next is needed
// wats wrong
//if u think so we can try it but my logic was curr = cur->next->next skips the dupe
// yeah i get your logic and its right, but it skips the dupe to 1234, and then skips to the next 1234 again because of the recursion line
//yea thats why i added the currMoved flag
// jeez ik we have to do recursion but this is actually making it harder in the process
// aight maybe my idea was wrong
// i think we just need more if else statements for whenever curr == head
void linkedList::createGuilty(node *curr, linkedList &guilty){
  if(curr == nullptr || curr->next == nullptr) return;

  bool currMoved = false;
  string guiltyid;
  node *previous;
  if(curr->id == curr->next->id){
    guiltyid = curr->id;
    guilty.addToList(guilty.getHead(), guiltyid);
  //  cout << guiltyid << " is guilty" << endl;
    guiltyid.clear();
    if(curr==head){
      if(curr == head && curr->next == tail){  
        head = tail = nullptr; 
        return;
      }
      else if (curr->next != nullptr) {
        curr = curr->next->next;
        head = curr;
        head->prev = nullptr;
      }
    }
    else if(curr->next == tail){
      previous = curr->prev;
      previous->next = nullptr;
      tail = previous;
      return;
    }
    else{
      previous = curr->prev;
      previous->next = nullptr;
      curr = curr->next->next;
      previous->next = curr;
      curr->prev = previous;
    }
    currMoved = true;
  }
  if(curr == nullptr || curr->next == nullptr) return;

  if(!currMoved)
    createGuilty(curr->next, guilty);
  else
    createGuilty(curr, guilty);
}
/*
void linkedList::remove(node *curr){
  if(!curr) return;

  
  node* previous;
  if(curr->id == curr->next->id && curr->next != nullptr){
    if(curr==head){
      curr = curr->next->next;
      head = curr;
    }
    else if(curr->next == tail){
      previous = curr->prev;
      previous->next = nullptr;
      tail = previous;
      return;
    }
    else{
      previous = curr->prev;
      previous->next = nullptr;
      curr = curr->next->next;
      previous->next = curr;
      curr->prev = previous;
    }
  }
  else if(curr->next == nullptr) return;
  
  remove(curr->next);
}

void linkedList::remove(node *cur) {
  if (cur == nullptr) { 
    return;
  }
  if (cur->id == cur->next->id) {
    if (cur == head && cur == tail) {
      head=tail=nullptr;  
    }
    else if (cur->next == nullptr) {
      return;
    }
    else if (cur == head) {
      head = head->next->next;
      head->prev = nullptr;
    }
    else if (cur == tail) {     
      tail = tail->prev->prev;
      tail->next = nullptr;
    }
    else {
      cur->next->prev = cur->prev;
      cur->prev->next = cur->next->next;
    }
    
  }
  else if (cur->next == nullptr) {
    return;
  }
  else {
    remove(cur->next);
  }
}*/

