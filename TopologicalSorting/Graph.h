#pragma once
#include "Arch.h"
#include <fstream>
#include <random>
#include <stack>

class Graph
{
private:
	std::vector<Node*> m_nodes;
	std::vector<Arch*> m_arches;
	std::vector<Arch> archesTS;
public:
	Graph();
	void AddNode(int value, std::pair<float, float> coord);
	void AddArch(Node* source, Node* destination);
	void CreateGraph();
	bool PTDF();
	void ShowTopologicalSorting(std::vector<int>t2);
	std::vector<Node*> getNodes();
	std::vector<Arch*> getArches();
	std::vector<Arch> getArchesTS();
	~Graph();
};
