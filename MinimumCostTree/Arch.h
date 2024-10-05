#pragma once
#include "Node.h"

class Arch
{
private:
	Node* m_firstNode;
	Node* m_secondNode;
	int m_cost;
	int m_color;
public:
	Arch();
	Arch(Node* firstNode, Node* secondNode, int cost);
	Arch(const Arch& other);
	void SetFirstNode(Node* firstNode);
	void SetSecondNode(Node* secondNode);
	void SetCost(int cost);
	void SetColor(int color);
	Node* GetFirstNode();
	Node* GetSecondNode();
	int GetCost();
	int GetColor();
};

