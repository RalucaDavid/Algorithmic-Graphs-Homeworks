#include "Arch.h"

Arch::Arch()
{
}

Arch::Arch(Node* firstNode, Node* secondNode, int cost) :m_firstNode(firstNode), m_secondNode(secondNode), m_cost(cost)
{
	m_color = 0;
}

Arch::Arch(const Arch& other)
{
	m_firstNode = other.m_firstNode;
	m_secondNode = other.m_secondNode;
	m_cost = other.m_cost;
	m_color = other.m_color;
}

void Arch::SetFirstNode(Node* firstNode)
{
	m_firstNode = firstNode;
}

void Arch::SetSecondNode(Node* secondNode)
{
	m_secondNode = secondNode;
}

void Arch::SetCost(int cost)
{
	m_cost = cost;
}

void Arch::SetColor(int color)
{
	m_color = color;
}

Node* Arch::GetFirstNode()
{
	return m_firstNode;
}

Node* Arch::GetSecondNode()
{
	return m_secondNode;
}

int Arch::GetCost()
{
	return m_cost;
}

int Arch::GetColor()
{
	return m_color;
}
