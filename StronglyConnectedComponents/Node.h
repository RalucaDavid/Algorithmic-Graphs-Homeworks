#pragma once
#include <vector>
#include <list>

class Node
{
private:
	int m_value;
	std::pair<float, float> m_coord;
	std::list<Node*> neighbors;
public:
	Node();
	Node(int value, std::pair<float, float> coord);
	void setValue(int value);
	std::pair<float, float> getCoord();
	void AddNeighbor(Node* node);
	int getValue();
	std::list<Node*> getNeighbors();
	bool operator==(const Node& other) const;
};

