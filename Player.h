
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H
#include <string>
#include "LinkedList.h"

class Player
{
public:
	Player();
	~Player();
	//玩家姓名
	std::string name;
	//玩家得分
	int score;
	//保存玩家手中的tile
	LinkedList hand;
	//玩家从bag抽取tile，一次性抽取count个数的tile
	void Drawn(LinkedList* pBag, int count);
	//清空玩家手里的tile
	void ClearHand(); 
	//玩家将手里的tile打出，返回值表示是否成功
	bool Discard(Colour colour, Shape shape);
	bool m_isAI;
};

#endif