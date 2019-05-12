
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <fstream>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

private:
   Node* head;
};

public:
  //Add a node to the back of the linklist
	void AddTail(Colour colour, Shape shape);
	void AddTail(Node* node);
  //Show the head node of linklist
	Node* Pop();
  //Print out the tile information of node
	void PrintContent();
  //Clean out the linklist
	void Clear();
  //Print out the side of linklist
	int size();
};

#endif // ASSIGN2_LINKEDLIST_H
