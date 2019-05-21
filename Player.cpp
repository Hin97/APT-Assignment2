#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
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
