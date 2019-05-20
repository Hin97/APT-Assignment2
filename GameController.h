
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
	void Start();
private:
	//Run game
	void RunGame();
	//Print welcome message
	void PrintWelcome();
	//Print invalid message
	void PrintInvalid();
	//Print score info
	void PrintScores();
	//Print broad 
	void PrintBoard();
	//Save board info
	void SaveBoard(std::ofstream& os);
	//Prompt user input message 
	std::string UserPrompt();
	//print menu
	int Menu();
	//start a new game with input player name
	void NewGame();
	//load file from director
	bool LoadGame();
	//Calculate score
	int CalcScore(int row, int col, bool& qwirkle);
	//Check if the position can be place
	bool PlaceCheck(int row, int col);
	//Auto expand the board
	void ExpandBoard(int direction);
	//AI battle unfinished
	void NewGameAI();
	//show student info
	void ShowStudentInfo();
	//print goodbye after quit
	void Quit();
	//Let the game run for a round（All players perform an operation for one round），The return value indicates the function execution status （STATUS_OK，STATUS_INVALID，STATUS_CONTINE，STATUS_QUIT，STATUS_TERMINA）
	int Round();
	//Shuffle
	void Shuffle();
	//End game，print players score info
	void EndGame();
	//Parse the command entered by the player and return to the current game state
	int ParseCmd(std::string cmd, Player& player);
	//Parse the tile represented by the letter string into a Tile class, and the return value indicates whether the parsing is successful.
	bool ParseTile(std::string strTile, Tile& tile);
	//Parse the coordinates represented by the letter string into integer coordinates, and the return value indicates whether the parsing is successful.
	bool ParsePlace(std::string strPlace, int& row, int& col);
	//The player places a tile on the board, row and col indicate the placement coordinates, and the return value indicates the function execution status.
	int PlaceTile(Player& player, Tile& tile, int row, int col);
	//The player replaces a tile on the hand, puts it in the bag, and extracts a new tile from the top of the bag. The return value indicates the function execution status.
	int ReplaceTile(Player& player, Tile& tile);
	//The index value of the currently executing player
	size_t m_nCurrentPlayer;
private:
	//use to save player's vector
	std::vector<Player> m_players;
	//use to save board's vector of vector
	std::vector<std::vector<Tile>> m_board;
	//use to save bag's LinkedList
	LinkedList m_bag;
	//board size，row numbers and col numbers
	int m_nRows;
	int m_nCols;
};

#endif
