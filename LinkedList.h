
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <fstream>
#include <vector>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

private:
   Node* head;
public:
	//向末尾增加一个节点
	void AddTail(Colour colour, Shape shape);
	void AddTail(Node* node);
	//弹出顶端的节点
	Node* Pop();
	//从中间抽取一个Node
	Node* Extract(Colour colour, Shape shape);
	//打印所有节点的内容
	void PrintContent();
	//保存所有节点的数据
	void SaveContent(std::ofstream &os);
	//清空所有数据
	void Clear();
	//返回节点数量
	int size();
	//返回保存tile向量
	void GetContent(std::vector<Tile>& tiles);
};

#endif // ASSIGN2_LINKEDLIST_H
