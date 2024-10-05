#include "Node.h"

Node::Node()
{
	/*empty*/
}

Node::Node(int value, std::pair<float,float> coord) :m_value(value), m_coord(coord)
{
	/*empty*/
}

void Node::setValue(int value)
{
	m_value = value;
}

std::pair<float, float> Node::getCoord()
{
	return m_coord;
}

void Node::AddNeighbor(Node* node)
{
	neighbors.push_back(node);
}

int Node::getValue()
{
	return m_value;
}

std::list<Node*> Node::getNeighbors()
{
	return neighbors;
}

bool Node::operator==(const Node& other) const
{
	return m_value == other.m_value;
}