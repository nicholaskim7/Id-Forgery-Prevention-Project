#include <fstream>
#include <string>
using namespace std;

struct node {
  node *next;
  node *prev;
  string id;
};

class linkedList {
private:
  node *head;
  node *tail;
  int size;
public:
  linkedList();
  ~linkedList();
  void addHead(string);
  node *getHead() {return head;}
  node *getTail() {return tail;}
  int getSize() {return size;}
  bool isEmpty() {
    if (head == nullptr) {
      return true;
    }
    else {
      return false;
    }
  }
  void outputFile(ofstream &, node*);
  void sort(node *);
  void print(node *);

  void addToEnd(node*, string _id);
  void traverseLL(node* head);


  node* addToTail(node*, string _id);
  node* deleteVal(node*, string);

  void addToList(node*, string);
  void createGuilty(node*, linkedList&);
//  void remove(node*);
};