#pragma once
#include "Arch.h"
#include <fstream>
#include <random>
#include <stack>
#include <algorithm>

class Graph
{
private:
	std::vector<Node*> m_nodes;
	std::vector<Arch*> m_arches;
	std::vector<int>m_t2;
	std::vector<std::vector<Node*>> conexComponents;
public:
	Graph();
	void AddNode(int value, std::pair<float, float> coord);
	void AddArch(Node* source, Node* destination);
	void CreateGraph();
	void PTDF();
	void CreateReversal();
	void PTDF2(std::vector<int> t2);
	
	std::vector<Node*> getNodes();
	std::vector<Arch*> getArches();
	std::vector<int> getT2();
	std::vector<std::vector<Node*>> getConexComponents();
	~Graph();
};
