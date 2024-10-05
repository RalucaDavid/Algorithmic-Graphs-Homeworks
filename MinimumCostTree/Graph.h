#pragma once

#include <vector>
#include <fstream>
#include "Arch.h"
#include <stack>

class Graph
{
private:
	std::vector<Node*> nodes;
	std::vector<Arch*> arches;
public:
	Graph();
	void AddNode(Node* node);
	void AddNode(QPoint position);
	void AddArch(Arch* arch);
	void AddArch(Node* node1, Node* node2, int cost);
	std::vector<Node*>& GetNodes();
	std::vector<Arch*>& GetAches();
	void Generic();
	void Boruvka();
	~Graph();
};

