#include "Player.h"



Player::Player()
	: m_isAI(false)
{
}


Player::~Player()
{
}


void Player::Drawn(LinkedList* pBag, int count)
{
	for (int i = 0; i < count; i++)
	{
		Node* node = pBag->Pop();
		hand.AddTail(node);
	}
}


void Player::ClearHand()
{
	hand.Clear();
}


bool Player::Discard(Colour colour,Shape shape)
{
	Node *node = hand.Extract(colour, shape);
	if (node == nullptr) return false;
	else
	{
		delete node->tile;
		delete node;
		return true;
	}
}
