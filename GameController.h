
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
	//启动游戏
	void Start();
private:
	//运行游戏
	void RunGame();
	//打印欢迎信息
	void PrintWelcome();
	//打印用户输入无效的提示信息
	void PrintInvalid();
	//打印分数信息
	void PrintScores();
	//打印棋盘数据
	void PrintBoard();
	//保存棋盘数据
	void SaveBoard(std::ofstream &os);
	//提示用户输入数据
	std::string UserPrompt();
	//显示游戏菜单并获取用户选择，返回值为用户的选择项
	int Menu();
	//开始新的游戏
	void NewGame();
	//加载保存的游戏，返回值表示是否加载成功
	bool LoadGame();
	//显示作者信息
	void ShowStudentInfo();
	//打印退出游戏goodbye
	void Quit();
	//让游戏运行一个回合(所有玩家执行一次操作为一个回合)，返回值表示函数执行状态（STATUS_OK正常，STATUS_INVALID用户输入无效，STATUS_CONTINE继续，STATUS_QUIT退出，STATUS_TERMINATE终止）
	int Round();
	//洗牌
	void Shuffle();
	//游戏结束，打印双方得分信息
	void EndGame();
	//解析玩家输入的命令，并返回当前游戏状态
	int ParseCmd(std::string cmd, Player &player);
	//将字符串表示的tile解析为Tile类，返回值表示解析是否成功
	bool ParseTile(std::string strTile, Tile& tile);
	//将字符串表示的坐标解析为整数坐标值，返回值表示解析是否成功
	bool ParsePlace(std::string strPlace, int& row, int& col);
	//玩家放置一个tile到棋盘上，row和col代表放置的坐标，返回值表示函数执行状态
	int PlaceTile(Player& player, Tile& tile, int row, int col);
	//玩家替换手上的一块tile，放入bag中，并从bag顶端抽取一块新的tile，返回值表示函数执行状态
	int ReplaceTile(Player& player, Tile& tile);
	//当前正在执行操作的玩家的索引值
	size_t m_nCurrentPlayer;
private:
	//用于保存玩家的vector
	std::vector<Player> m_players;
	//用于保存棋盘的vector of vector
	std::vector<std::vector<Tile>> m_board;
	//用于保存bag的LinkedList
	LinkedList m_bag;
	//棋盘的尺寸，行数和列数
	int m_nRows;
	int m_nCols;
};

#endif