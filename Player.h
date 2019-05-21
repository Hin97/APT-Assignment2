
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H
#include <string>
#include "LinkedList.h"

class Player
{
public:
	Player();
	~Player();
	//Player name
	std::string name;
	//Player score
	int score;
	//Linklist for tiles on hand
  LinkedList hand;
  //clear tiles from hand
  void ClearHand();
  //Place a tile, the result shows that its success or not.
  bool Discard(Colour colour, Shape shape);
};

#endif
