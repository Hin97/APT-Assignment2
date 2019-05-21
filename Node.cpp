
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   // TODO
	this->tile = tile;
	this->next = next;
}

Node::Node(Node& other)
{
   // TODO
	tile = other.tile;
	next = other.next;
}
