
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
	//������Ϸ
	void Start();
private:
	//������Ϸ
	void RunGame();
	//��ӡ��ӭ��Ϣ
	void PrintWelcome();
	//��ӡ�û�������Ч����ʾ��Ϣ
	void PrintInvalid();
	//��ӡ������Ϣ
	void PrintScores();
	//��ӡ��������
	void PrintBoard();
	//������������
	void SaveBoard(std::ofstream &os);
	//��ʾ�û���������
	std::string UserPrompt();
	//��ʾ��Ϸ�˵�����ȡ�û�ѡ�񣬷���ֵΪ�û���ѡ����
	int Menu();
	//��ʼ�µ���Ϸ
	void NewGame();
	//���ر������Ϸ������ֵ��ʾ�Ƿ���سɹ�
	bool LoadGame();
	//��ʾ������Ϣ
	void ShowStudentInfo();
	//��ӡ�˳���Ϸgoodbye
	void Quit();
	//����Ϸ����һ���غ�(�������ִ��һ�β���Ϊһ���غ�)������ֵ��ʾ����ִ��״̬��STATUS_OK������STATUS_INVALID�û�������Ч��STATUS_CONTINE������STATUS_QUIT�˳���STATUS_TERMINATE��ֹ��
	int Round();
	//ϴ��
	void Shuffle();
	//��Ϸ��������ӡ˫���÷���Ϣ
	void EndGame();
	//��������������������ص�ǰ��Ϸ״̬
	int ParseCmd(std::string cmd, Player &player);
	//���ַ�����ʾ��tile����ΪTile�࣬����ֵ��ʾ�����Ƿ�ɹ�
	bool ParseTile(std::string strTile, Tile& tile);
	//���ַ�����ʾ���������Ϊ��������ֵ������ֵ��ʾ�����Ƿ�ɹ�
	bool ParsePlace(std::string strPlace, int& row, int& col);
	//��ҷ���һ��tile�������ϣ�row��col������õ����꣬����ֵ��ʾ����ִ��״̬
	int PlaceTile(Player& player, Tile& tile, int row, int col);
	//����滻���ϵ�һ��tile������bag�У�����bag���˳�ȡһ���µ�tile������ֵ��ʾ����ִ��״̬
	int ReplaceTile(Player& player, Tile& tile);
	//��ǰ����ִ�в�������ҵ�����ֵ
	size_t m_nCurrentPlayer;
private:
	//���ڱ�����ҵ�vector
	std::vector<Player> m_players;
	//���ڱ������̵�vector of vector
	std::vector<std::vector<Tile>> m_board;
	//���ڱ���bag��LinkedList
	LinkedList m_bag;
	//���̵ĳߴ磬����������
	int m_nRows;
	int m_nCols;
};

#endif