
#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include <string>
#include "Player.h"
#include <vector>


class Game
{

public:
	Game();
	~Game();
	//start game
	void Start();//Jason
private:
	//Run game
	void RunGame();//Jack
	//Print welcome message
	void PrintWelcome();//Jason
	//Print invalid message
	void PrintInvalid();//Jason
	//Print score info
	void PrintScores();//Oscar
	//Print broad 
	void PrintBoard();//Jack
	//Save board info
	void SaveBoard(std::ofstream& os);//Jack
	//Prompt user input message 
	std::string UserPrompt();//Jason
	//print menu
	int Menu();//Jason
	//start a new game with input player name
	void NewGame();//Oscar
	//load file from director
	bool LoadGame();//Jack
	//Calculate score
	int CalcScore(int row, int col, bool& qwirkle);//Jason
	//Check if the position can be place
	bool PlaceCheck(int row, int col);//Jason
	//Auto expand the board
	void ExpandBoard(int direction);//Jack
	//AI battle unfinished
	void NewGameAI();//Oscar
	//show student info
	void ShowStudentInfo();//Jack
	//print goodbye after quit
	void Quit();//Jason
	//Let the game run for a round（All players perform an operation for one round），The return value indicates the function execution status （STATUS_OK，STATUS_INVALID，STATUS_CONTINE，STATUS_QUIT，STATUS_TERMINA）
	int Round();//Cryil
	//Shuffle
	void Shuffle();//cryil
	//End game，print players score info
	void EndGame();//Cryil
	//Parse the command entered by the player and return to the current game state
	int ParseCmd(std::string cmd, Player& player);//Jack
	//Parse the tile represented by the letter string into a Tile class, and the return value indicates whether the parsing is successful.
	bool ParseTile(std::string strTile, Tile& tile);//Cryil
	//Parse the coordinates represented by the letter string into integer coordinates, and the return value indicates whether the parsing is successful.
	bool ParsePlace(std::string strPlace, int& row, int& col);//Cryil
	//The player places a tile on the board, row and col indicate the placement coordinates, and the return value indicates the function execution status.
	int PlaceTile(Player& player, Tile& tile, int row, int col);//Oscar
	//The player replaces a tile on the hand, puts it in the bag, and extracts a new tile from the top of the bag. The return value indicates the function execution status.
	int ReplaceTile(Player& player, Tile& tile);//Oscar
	//The index value of the currently executing player
	size_t m_nCurrentPlayer;//Oscar
private:
	//use to save player's vector
	std::vector<Player> m_players;//Oscar
	//use to save board's vector of vector
	std::vector<std::vector<Tile>> m_board;//Jack
	//use to save bag's LinkedList
	LinkedList m_bag;//Cryil
	//board size，row numbers and col numbers
	int m_nRows;
	int m_nCols;

};

#endif
