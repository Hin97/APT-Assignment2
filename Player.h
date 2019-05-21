
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
};

#endif
