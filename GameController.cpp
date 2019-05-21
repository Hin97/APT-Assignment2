
#include "Game.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include <algorithm>

#define STATUS_OK			0
#define STATUS_INVALID		1
#define STATUS_CONTINE		2
#define STATUS_QUIT			3
#define STATUS_TERMINATE	4

Game::Game()
	: m_nRows(6)
	, m_nCols(6)
	, m_nCurrentPlayer(0)
{
	
}



Game::~Game()
{
}




void Game::Start()
{
	PrintWelcome();
	int select = Menu();
	while (select)
	{
		if (select == 1)
		{
			NewGame();

			RunGame();

			select = 0;
		}
		else if (select == 2)
		{
			if (LoadGame())
			{

				RunGame();

				select = 0;
			}
			else
			{
				select = Menu();
			}
		}
		else if (select == 3)
		{
			ShowStudentInfo();
			select = Menu();
		}
		else if (select == 4)
		{
			Quit();
			select = 0;
		}

		else if (select == 5)
		{
			NewGameAI();
			RunGame();
			select = 0;
		}

	}
}



void Game::RunGame()
{
	int status = STATUS_OK;
	while (status == STATUS_OK)
	{
		status = Round();
	}
	if (status == STATUS_TERMINATE) EndGame();
	Quit();
}



void Game::PrintWelcome()
{
	std::cout << "Welcome to Qwirkle!\n---------------------\n" << std::endl;
}


std::string Game::UserPrompt()
{
	std::cout << "> ";

	std::string str; 

	std::getline(std::cin, str);
	std::cout << std::endl;
	return str;
}


void Game::PrintInvalid()
{
	std::cout << "Invalid Input" << std::endl;
}


int Game::Menu()
{

	std::cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show student information\n4. Quit\n5. Play with AI\n" << std::endl;

	int select = 0;
	while (!select)
	{
		std::string num = UserPrompt();
		select = atoi(num.c_str());

		if (select < 1 || select>5)

		{
			PrintInvalid();
			select = 0;
		}
	}
	return select;
}


void Game::NewGame()
{

	for (int i = 0; i < m_nRows; i++)
	{
		std::vector<Tile> row;
		for (int j = 0; j < m_nCols; j++)
		{
			Tile tile; tile.colour = 0; tile.shape = 0;
			row.push_back(tile);
		}
		m_board.push_back(row);
	}

	std::cout << "Starting a New Game\n" << std::endl;
	for (int i = 0; i < 2; i++)
	{
		Player player; player.score = 0;
		bool legal = false;
		while (!legal)
		{
			legal = true;
			std::cout << "Enter a name for player " << i + 1 << " (uppercase characters only)" << std::endl;
			player.name = UserPrompt();
			if (player.name.empty()) legal = false;
			else
			{
				for (auto c : player.name)
				{
					if (c<'A' || c>'Z')
						legal = false;
				}
			}
			if (!legal) PrintInvalid();
		}
		m_players.push_back(player);
	}

	std::cout << "\nLet’s Play!\n" << std::endl;
	Shuffle();
	for (int i = 0; i < 2; i++)
	{
		m_players[i].ClearHand();
		m_players[i].Drawn(&m_bag, 6);
	}
}


void Game::NewGameAI()
{
	for (int i = 0; i < m_nRows; i++)
	{
		std::vector<Tile> row;
		for (int j = 0; j < m_nCols; j++)
		{
			Tile tile; tile.colour = 0; tile.shape = 0;
			row.push_back(tile);
		}
		m_board.push_back(row);
	}
	std::cout << "Starting a New Game\n" << std::endl;
	//create human
	{
		Player player; player.score = 0;
		bool legal = false;
		while (!legal)
		{
			legal = true;
			std::cout << "Enter your name(uppercase characters only)" << std::endl;
			player.name = UserPrompt();
			if (player.name.empty()) legal = false;
			else
			{
				for (auto c : player.name)
				{
					if (c<'A' || c>'Z')
						legal = false;
				}
			}
			if (!legal) PrintInvalid();
		}
		m_players.push_back(player);
	}
	//create computer
	{
		Player player; player.score = 0; player.name = "COMPUTER"; player.m_isAI = true;
		m_players.push_back(player);
	}
	std::cout << "\nLet’s Play!\n" << std::endl;
	Shuffle();
	for (int i = 0; i < 2; i++)
	{
		m_players[i].ClearHand();
		m_players[i].Drawn(&m_bag, 6);
	}
}



bool Game::LoadGame()
{
	std::cout << "Enter the filename from which load a game" << std::endl;
	std::string file = UserPrompt();

	file.erase(0, file.find_first_not_of(" "));
	file.erase(file.find_last_not_of(" ") + 1);

	std::ifstream is; is.open(file);

	if (!is)
	{
		std::cout << "Can not load the game!\n" << std::endl;
		return false;
	}
	else
	{

		std::string line;
		m_players.clear();
		for (int i = 0; i < 2; i++)
		{
			Player player; m_players.push_back(player);
		}
		for (int i = 0; i < 2; i++)
		{
			std::getline(is, m_players[i].name);
			std::getline(is, line); m_players[i].score = atoi(line.c_str());
			std::string strHand; std::getline(is, strHand);
			size_t left = 0;
			while (left < strHand.length())
			{
				std::string strTile = strHand.substr(left, 2);
				m_players[i].hand.AddTail(strTile[0], strTile[1] - '0');
				left += 3;
			}
		}
		std::getline(is, line); std::getline(is, line); 
		bool reading_board = true;
		int i = 0;
		while (reading_board)
		{
			std::getline(is, line);
			size_t index = line.find("|");
			if ((int)index == -1) reading_board = false;
			else
			{
				int j = 0;
				std::vector<Tile> row;
				while (index + 2 < line.length())
				{
					Tile tile; tile.colour = 0; tile.shape = 0;
					if (line[index + 1] != ' ')
					{
						tile.colour = line[index + 1];
						tile.shape = line[index + 2] - '0';
					}
					row.push_back(tile);
					j++; index += 3;
				}
				m_board.push_back(row);
			}
			i++;
		}
		if (m_board.size())
		{
			m_nRows = m_board.size();
			m_nCols = m_board[0].size();
		}
		size_t index = 0;
		while (index < line.length())
		{
			m_bag.AddTail(line[index], line[index + 1] - '0');
			index += 3;
		}
		std::getline(is, line);
		for (size_t i = 0; i < m_players.size(); i++)
		{
			if (m_players[i].name.compare(line) == 0)
				m_nCurrentPlayer = i;
		}

		std::cout << "Qwirkle game successfully loaded\n" << std::endl;
		return true;
	}
}


void Game::ShowStudentInfo()
{
	struct Student
	{
		std::string m_name, m_studentID, m_email;
		Student(std::string Name, std::string StudentID, std::string Email) { m_name = Name; m_studentID = StudentID; m_email = Email; }
		void Print() { std::cout << "Name:" << m_name << "\nStudent ID:" << m_studentID << "\nEmail:" << m_email << std::endl; }
	};

	std::vector<Student> students;
	students.push_back(Student("Oscar", "3562697", "s3562697@student.rmit.edu.au"));
	students.push_back(Student("Jack", "3661033", "s3661033@student.rmit.edu.au"));
	students.push_back(Student("Cryil", "3579811", "s3579811@student.rmit.edu.au"));
	students.push_back(Student("Jason", "3566690", "s3566690@student.rmit.edu.au"));

	std::cout << "----------------------------------" << std::endl;
	for (size_t i = 0; i < students.size(); i++)
	{
		students[i].Print();
		if (i + 1 < students.size()) std::cout << std::endl;
	}
	std::cout << "----------------------------------\n" << std::endl;
}


void Game::Quit()
{
	std::cout << "Goodbye" << std::endl;
}



int Game::Round()
{
	while (m_nCurrentPlayer < m_players.size())
	{
		Player &p = m_players[m_nCurrentPlayer];
		if (p.hand.size() == 0) return STATUS_TERMINATE;

		std::cout << p.name << ", it’s your turn" << std::endl;
		PrintScores();
		PrintBoard();
		std::cout << "Your hand is" << std::endl;
		p.hand.PrintContent();
		std::cout << std::endl;

		if (p.m_isAI)
		{
			std::vector<Tile> tiles; p.hand.GetContent(tiles);
			Tile tileChoose = tiles[0];
			int scoreMax = 0, row = 0, col = 0;
			for (int t = 0; t < tiles.size(); t++)
			{
				for (int i = 0; i < m_nRows; i++)
				{
					for (int j = 0; j < m_nCols; j++)
					{
						if (m_board[i][j].shape == 0)
						{
							m_board[i][j].colour = tiles[t].colour;
							m_board[i][j].shape = tiles[t].shape;
							if (PlaceCheck(i, j))
							{
								bool isqwirkle;
								int score = CalcScore(i, j, isqwirkle);
								if (scoreMax < score)
								{
									scoreMax = score;
									tileChoose = tiles[t];
									row = i;
									col = j;
								}
							}
							m_board[i][j].colour = 0;
							m_board[i][j].shape = 0;
						}
					}
				}
			}
			if (scoreMax == 0)
			{
				std::cout << "COMPUTER replace " << tiles[0].colour << tiles[0].shape << std::endl;
				ReplaceTile(p, tiles[0]);
			}
			else
			{
				char r = 'A' + row;
				std::cout << "COMPUTER place " << tileChoose.colour << tileChoose.shape << " at " << r << col << std::endl << std::endl;
				PlaceTile(p, tileChoose, row, col);
			}
		}
		else
		{
			int status = STATUS_INVALID;
			while (status != STATUS_OK)
			{
				std::string cmd = UserPrompt();
				status = ParseCmd(cmd, p);
				if (status == STATUS_QUIT || status == STATUS_TERMINATE) return status;
				if (status == STATUS_INVALID) PrintInvalid();
			}
		}
		m_nCurrentPlayer++;
	}
	m_nCurrentPlayer = 0;
	return STATUS_OK;
}


void Game::PrintScores()
{
	for (size_t i = 0; i < m_players.size(); i++)
	{
		std::cout << "Score for " << m_players[i].name << ": " << m_players[i].score << std::endl;
	}
}


void Game::PrintBoard()
{
	std::cout << "   ";
	for (size_t i = 0; i < m_nCols; i++)
	{
		if (i < 10)
			std::cout << i << "  ";
		else
			std::cout << i << " ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < m_nCols + 1; i++)
	{
		std::cout << "---";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < m_board.size(); i++)
	{
		char c = 'A' + short(i);
		std::cout << c << " |";
		for (auto t : m_board[i])
		{
			if (t.colour)
			{
				std::cout << t.colour << t.shape << "|";
			}
			else
			{
				std::cout << "  |";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void Game::SaveBoard(std::ofstream &os)
{
	os << "   ";
	for (size_t i = 0; i < m_board.size(); i++)
	{
		os << i << "  ";
	}
	os << std::endl;
	for (size_t i = 0; i < m_board.size() + 1; i++)
	{
		os << "---";
	}
	os << std::endl;
	for (size_t i = 0; i < m_board.size(); i++)
	{
		char c = 'A' + short(i);
		os << c << " |";
		for (auto t : m_board[i])
		{
			if (t.colour)
			{
				os << t.colour << t.shape << "|";
			}
			else
			{
				os << "  |";
			}
		}
		os << std::endl;
	}
}


void Game::Shuffle()
{
	char colour[6] = { 'R' ,'O' ,'Y' ,'G' ,'B' ,'P' };
	std::vector<Tile> pool;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			Tile tile; 
			tile.colour = colour[i];
			tile.shape = j + 1;
			pool.push_back(tile);
			pool.push_back(tile);
		}
	}
	m_bag.Clear();
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> id(0, 71);
	std::random_device device;
	e.seed(device());
	while (!pool.empty())
	{
		int index = id(e) % pool.size();
		Tile t = pool[index];
		m_bag.AddTail(t.colour, t.shape);
		pool.erase(pool.begin() + index);
	}
}


void Game::EndGame()
{
	std::string winner;
	int max = 0;
	std::cout << "Game over" << std::endl;
	for (size_t i = 0; i < m_players.size(); i++)
	{
		if (max < m_players[i].score)
		{
			winner = m_players[i].name;
			max = m_players[i].score;
		}
		std::cout << "Score for " << m_players[i].name << ": " << m_players[i].score << std::endl;
	}
	std::cout << "Player " << winner << " won!\n" << std::endl;
}


int Game::ParseCmd(std::string cmd, Player &player)
{
	if (cmd.compare("^D") == 0 || cmd.compare("\x4") == 0) return STATUS_QUIT;
	int index = cmd.find(' ');
	if (cmd.find("place ") == 0)
	{
		int c = cmd.find("at");
		if (c == -1) return STATUS_INVALID;
		std::string strTile = cmd.substr(index + 1, c - index - 2);
		std::string strPlace = cmd.substr(c + 3, cmd.length() - c - 3);
		Tile tile; if (!ParseTile(strTile, tile)) return STATUS_INVALID;
		int row, col; if (!ParsePlace(strPlace, row, col)) return STATUS_INVALID;
		return PlaceTile(player, tile, row, col);
	}
	else if (cmd.find("replace ") == 0)
	{
		std::string strTile = cmd.substr(index + 1, cmd.length() - index);
		Tile tile; if (!ParseTile(strTile, tile)) return STATUS_INVALID;
		return ReplaceTile(player, tile);
	}
	else if (cmd.find("save ") == 0)
	{
		std::string fileName = cmd.substr(index + 1, cmd.length() - index);
		fileName.erase(0, fileName.find_first_not_of(" "));
		fileName.erase(fileName.find_last_not_of(" ") + 1);
		std::ofstream os; os.open(fileName);
		if (!os) return STATUS_INVALID;
		for (size_t i = 0; i < m_players.size(); i++)
		{
			os << m_players[i].name << std::endl;
			os << m_players[i].score << std::endl;
			m_players[i].hand.SaveContent(os);
		}
		SaveBoard(os);
		m_bag.SaveContent(os);
		os << player.name << std::endl;
		os.close();
		std::cout << "Game successfully saved\n" << std::endl;
		return STATUS_CONTINE;
	}
	return STATUS_INVALID;
}


bool Game::ParseTile(std::string strTile, Tile& tile)
{
	if (strTile.size() != 2) return false;
	Colour c = strTile[0];
	if (c != 'R'&&c != 'O'&&c != 'Y'&&c != 'G'&&c != 'B'&&c != 'P') return false;
	int shape = strTile[1] - '0';
	if (shape < 1 || shape>6) return false;
	tile.colour = c;
	tile.shape = shape;
	return true;
}


bool Game::ParsePlace(std::string strPlace, int& row, int& col)
{
	row = strPlace[0] - 'A';
	if (row < 0 || row > m_nRows) return false;
	for (size_t i = 1; i < strPlace.length(); i++)
	{
		if (strPlace[i]<'0' || strPlace[i]>'9') return false;
	}
	col = atoi(strPlace.substr(1, strPlace.length() - 1).c_str());
	if (col < 0 || col>m_nCols) return false;
	return true;
}


int Game::ReplaceTile(Player & player, Tile & tile)
{
	if (m_bag.size() == 0) return STATUS_INVALID;
	else
	{
		Node * node = player.hand.Extract(tile.colour, tile.shape);
		if(node==nullptr)  return STATUS_INVALID;
		m_bag.AddTail(node);
		player.Drawn(&m_bag, 1);
		return STATUS_OK;
	}
}


int Game::PlaceTile(Player& player, Tile& tile, int row, int col)
{
	if (player.hand.size() == 0) return STATUS_TERMINATE;
	if (m_board[row][col].colour != 0) return STATUS_INVALID;
	m_board[row][col].colour = tile.colour;
	m_board[row][col].shape = tile.shape;
	if (!PlaceCheck(row, col))
	{
		m_board[row][col].colour = 0;
		m_board[row][col].shape = 0;
		return STATUS_INVALID;
	}
	if (!player.Discard(tile.colour, tile.shape)) return STATUS_INVALID;
	else
	{
		bool qwirkle;
		player.score += CalcScore(row, col, qwirkle);
		if (qwirkle) std::cout << "QWIRKLE!!!\n" << std::endl;
		player.Drawn(&m_bag, 1);
		if (row == 0) ExpandBoard(0);
		if (row == m_nRows - 1) ExpandBoard(1);
		if (col == 0) ExpandBoard(2);
		if (col == m_nCols - 1) ExpandBoard(3);
		return STATUS_OK;
	}
}


bool Game::PlaceCheck(int row, int col)
{
	Shape shape = m_board[row][col].shape;
	Colour colour = m_board[row][col].colour;
	//vertical test
	int type = -1;
	if (row - 1 >= 0 && m_board[row - 1][col].shape)
	{
		type = 0;
		if (colour == m_board[row - 1][col].colour) type = 1;
	}
	else if (row + 1 < m_nRows && m_board[row + 1][col].shape)
	{
		type = 0;
		if (colour == m_board[row + 1][col].colour) type = 1;
	}
	if (type != -1)
	{
		int i = row - 1, count = 1;
		while (i >= 0 && m_board[i][col].shape)
		{
			if ((m_board[i][col].colour == colour || m_board[i][col].shape != shape) && type == 0) return false;
			if ((m_board[i][col].colour != colour || m_board[i][col].shape == shape) && type == 1) return false;
			count++;
			i--;
		}
		i = row + 1;
		while (i < m_nRows && m_board[i][col].shape)
		{
			if ((m_board[i][col].colour == colour || m_board[i][col].shape != shape) && type == 0) return false;
			if ((m_board[i][col].colour != colour || m_board[i][col].shape == shape) && type == 1) return false;
			count++;
			i++;
		}
		if (count > 6) return false;
	}
	//horizontal test
	type = -1;
	if (col - 1 >= 0 && m_board[row][col - 1].shape)
	{
		type = 0;
		if (colour == m_board[row][col - 1].colour) type = 1;
	}
	else if (col + 1 < m_nCols && m_board[row][col + 1].shape)
	{
		type = 0;
		if (colour == m_board[row][col + 1].colour) type = 1;
	}
	if (type != -1)
	{
		int i = col - 1, count = 1;
		while (i >= 0 && m_board[row][i].shape)
		{
			if ((m_board[row][i].colour == colour || m_board[row][i].shape != shape) && type == 0) return false;
			if ((m_board[row][i].colour != colour || m_board[row][i].shape == shape) && type == 1) return false;
			count++;
			i--;
		}
		i = col + 1;
		while (i < m_nCols && m_board[row][i].shape)
		{
			if ((m_board[row][i].colour == colour || m_board[row][i].shape != shape) && type == 0) return false;
			if ((m_board[row][i].colour != colour || m_board[row][i].shape == shape) && type == 1) return false;
			count++;
			i++;
		}
		if (count > 6) return false;
	}
	return true;
}


int Game::CalcScore(int row, int col,bool& qwirkle)
{
	qwirkle = false;
	int score = 0, count = 1, i = row - 1;
	while (i >= 0 && m_board[i][col].shape)
	{
		count++;
		i--;
	}
	i = row + 1;
	while (i < m_nRows && m_board[i][col].shape)
	{
		count++;
		i++;
	}
	if (count > 1)score += count;
	if (count == 6) { score += 6; qwirkle = true; }

	i = col - 1; count = 1;
	while (i >= 0 && m_board[row][i].shape)
	{
		count++;
		i--;
	}
	i = col + 1;
	while (i < m_nCols && m_board[row][i].shape)
	{
		count++;
		i++;
	}
	if (count > 1)score += count;
	if (count == 6) { score += 6; qwirkle = true; }
	return score;
}


void Game::ExpandBoard(int direction)
{
	std::vector<std::vector<Tile>> copy;
	if (direction == 0 && m_nRows<26)
	{
		std::vector<Tile> row;
		for (int j = 0; j < m_nCols; j++)
		{
			Tile tile; tile.colour = 0; tile.shape = 0;
			row.push_back(tile);
		}
		copy.push_back(row);
		for (int i = 0; i < m_nRows; i++)
		{
			copy.push_back(m_board[i]);
		}
		m_nRows++;
		m_board.swap(copy);
	}
	else if (direction == 1 && m_nRows<26)
	{
		for (int i = 0; i < m_nRows; i++)
		{
			copy.push_back(m_board[i]);
		}
		std::vector<Tile> row;
		for (int j = 0; j < m_nCols; j++)
		{
			Tile tile; tile.colour = 0; tile.shape = 0;
			row.push_back(tile);
		}
		copy.push_back(row);
		m_nRows++;
		m_board.swap(copy);
	}
	else if (direction == 2 && m_nCols<26)
	{
		for (int i = 0; i < m_nRows; i++)
		{
			std::vector<Tile> row;
			Tile tile; tile.colour = 0; tile.shape = 0;
			row.push_back(tile);
			for (int j = 0; j < m_nCols; j++)
			{
				row.push_back(m_board[i][j]);
			}
			copy.push_back(row);
		}
		m_nCols++;
		m_board.swap(copy);
	}
	else if (direction == 3 && m_nCols<26)
	{
		for (int i = 0; i < m_nRows; i++)
		{
			Tile tile; tile.colour = 0; tile.shape = 0;
			m_board[i].push_back(tile);
		}
		m_nCols++;
	}
}

