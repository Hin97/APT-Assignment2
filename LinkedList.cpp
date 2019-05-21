
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() 
{
   head = nullptr;
   // TODO
}

LinkedList::~LinkedList() 
{
	Clear();
}


void LinkedList::Clear()
{
	Node* cur = head;
	while (cur)
	{
		Node* temp = cur->next;
		delete cur->tile;
		delete cur;
		cur = temp;
	}
	head = nullptr;
}


void LinkedList::AddTail(Colour colour, Shape shape)
{
	Tile* tile = new Tile();
	tile->colour = colour;
	tile->shape = shape;
	Node* node = new Node(tile, nullptr);
	AddTail(node);
}


void LinkedList::AddTail(Node * node)
{
	if (node == nullptr) return;
	if (head == nullptr) head = node;
	else
	{
		Node* temp = head;
		while (temp->next) temp = temp->next;
		temp->next = node;
	}
}


void LinkedList::PrintContent()
{
	Node* temp = head;
	while (temp)
	{
		std::cout << temp->tile->colour << temp->tile->shape;
		if (temp->next) std::cout << ',';
		temp = temp->next;
	} 
	std::cout << std::endl;
}


void LinkedList::SaveContent(std::ofstream & os)
{
	Node* temp = head;
	while (temp)
	{
		os << temp->tile->colour << temp->tile->shape;
		if (temp->next) os << ',';
		temp = temp->next;
	}
	os << std::endl;
}


Node* LinkedList::Pop()
{
	Node* temp = head;
	if (head) head = head->next;
	if (temp) temp->next = nullptr;
	return temp;
}


Node * LinkedList::Extract(Colour colour, Shape shape)
{
	if (head == nullptr) return nullptr;
	if (head->tile->colour == colour && head->tile->shape == shape)
		return Pop();
	Node* temp = head;
	while (temp->next)
	{
		Node* next = temp->next;
		if (next->tile->colour == colour&&next->tile->shape == shape)
		{
			temp->next = next->next;
			next->next = nullptr;
			return next;
		}
		temp = temp->next;
	}
	return nullptr;
}


int LinkedList::size()
{
	int count = 0;
	Node* temp = head;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}


void LinkedList::GetContent(std::vector<Tile>& tiles)
{
	Node* temp = head;
	while (temp)
	{
		Tile tile; 
		tile.colour = temp->tile->colour;
		tile.shape = temp->tile->shape;
		temp = temp->next; 
		tiles.push_back(tile);
	}
}
