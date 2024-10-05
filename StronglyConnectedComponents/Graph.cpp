#include "Graph.h"

Graph::Graph()
{
	/*empty*/
}

void Graph::AddNode(int value, std::pair<float, float> coord)
{
	Node* newNode = new Node(value, coord);
	m_nodes.push_back(newNode);
}

void Graph::AddArch(Node* source, Node* destination)
{
	Arch* newArch = new Arch(source, destination);
	m_arches.push_back(newArch);
	source->AddNeighbor(destination);
}

void ReadingMatrix(std::vector<std::vector<int>>& matrix, int& dimension)
{
	std::ifstream fin("Input.txt");
	fin >> dimension;
	std::vector<int> column;
	int element;
	for (int index = 0; index < dimension; index++)
	{
		for (int jndex = 0; jndex < dimension; jndex++)
		{
			fin >> element;
			column.push_back(element);
		}
		matrix.push_back(column);
		column.clear();
	}
	fin.close();
}

void GenerateCoords(float& coord1, float& coord2)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 6);
	coord1 = dis(gen);
	coord2 = dis(gen);
}

void Graph::CreateGraph()
{
	std::vector<std::vector<int>> matrix;
	int dimension;
	ReadingMatrix(matrix, dimension);
	for (int index = 0; index < dimension; index++)
	{
		float coord1, coord2;
		GenerateCoords(coord1, coord2);
		AddNode(index, std::make_pair(coord1, coord2));
	}
	for (int index = 0; index < dimension; index++)
	{
		for (int jndex = 0; jndex < dimension; jndex++)
		{
			if (matrix[index][jndex] == 1)
			{
				AddArch(m_nodes[index], m_nodes[jndex]);
			}
		}
	}
}

void Graph::PTDF()
{
	Node* entry = m_nodes[0]; // s
	std::vector<Node*>U; // unvisited nodes
	std::stack<Node*>V; // visited and unanalyzed nodes
	std::stack<Node*>W; // visited and analyzed nodes
	std::vector<int> p; // predecessors
	std::vector<int> t1;
	std::vector<int> t2;
	V.push(entry);
	for (Node*& node : m_nodes)
		if (node->getValue() != entry->getValue())
			U.push_back(node);
	for (int index = 0; index < m_nodes.size(); index++)
	{
		p.push_back(-1);
		t1.push_back(0);
		t2.push_back(0);
	}
	t1[entry->getValue()] = 1;
	int t = 1;
	while (!U.empty())
	{
		while (!V.empty())
		{
			Node* x = V.top();
			W.push(x);
			t1[x->getValue()] = ++t;
			int ok = 0;
			for (Node* y : x->getNeighbors())
			{
				auto it1 = std::find(U.begin(), U.end(), y);
				if (it1 != U.end())
				{
					ok = 1;
					V.push(*it1);
					U.erase(it1);
					t1[y->getValue()] = ++t;
					p[y->getValue()] = x->getValue();
					break;
				}
			}
			if (ok == 0)
			{
				V.pop();
				W.push(x);
				t2[x->getValue()] = ++t;
			}
		}
		if (!U.empty()) {
			Node* entry = U.front();
			U.erase(U.begin());
			V.push(entry);
			t1[entry->getValue()] = ++t;
		}
	}
	m_t2 = t2;
}

void Graph::CreateReversal()
{
	std::vector<std::vector<int>> matrix;
	int dimension;
	ReadingMatrix(matrix, dimension);
	for (int index = 0; index < dimension; index++)
	{
		float coord1, coord2;
		GenerateCoords(coord1, coord2);
		AddNode(index, std::make_pair(coord1, coord2));
	}
	for (int index = 0; index < dimension; index++)
	{
		for (int jndex = 0; jndex < dimension; jndex++)
		{
			if (matrix[index][jndex] == 1)
			{
				AddArch(m_nodes[jndex],m_nodes[index]);
			}
		}
	}
}

void Graph::PTDF2(std::vector<int> t2)
{
	Node* entry; // s
	std::vector<Node*>U; // unvisited nodes
	std::stack<Node*>V; // visited and unanalyzed nodes
	std::stack<Node*>W; // visited and analyzed nodes
	std::vector<int> p; // predecessors
	std::vector<int> t1;
	std::vector<int> t3;
	auto itMax = std::max_element(t2.begin(), t2.end());
	for (Node*& node : m_nodes)
	{
		if (node->getValue() != std::distance(t2.begin(), itMax))
			U.push_back(node);
		else
		{
			entry = node;
			V.push(entry);
			*itMax = -1;
		}
	}
	for (int index = 0; index < m_nodes.size(); index++)
	{
		p.push_back(-1);
		t1.push_back(0);
		t3.push_back(0);
	}
	t1[entry->getValue()] = 1;
	int t = 1;
	while (!U.empty()||!V.empty())
	{
		std::vector<Node*> component;
		while (!V.empty())
		{
			Node* x = V.top();
			W.push(x);
			t1[x->getValue()] = ++t;
			int ok = 0;
			for (Node* y : x->getNeighbors())
			{
				auto it1 = std::find(U.begin(), U.end(), y);
				if (it1 != U.end())
				{
					ok = 1;
					V.push(*it1);
					U.erase(it1);
					t1[y->getValue()] = ++t;
					p[y->getValue()] = x->getValue();
					t2[y->getValue()] = -1;
					break;
				}
			}
			if (ok == 0)
			{
				V.pop();
				W.push(x);
				component.push_back(x);
				t3[x->getValue()] = ++t;
			}
		}
		if (!U.empty()) 
		{
			auto itMax = std::max_element(t2.begin(), t2.end());
			for (Node*& node : m_nodes) 
			{
				if (node->getValue() == std::distance(t2.begin(), itMax)) 
				{
					entry = node;
					*itMax = -1;
					break;
				}
			}
			auto itNode = std::find_if(m_nodes.begin(), m_nodes.end(), [valueToFind = *itMax](Node* node) 
				{
				return node->getValue() == valueToFind;
				});
			U.erase(std::remove(U.begin(), U.end(), entry), U.end());
			V.push(entry);
			t1[entry->getValue()] = ++t;
		}
		conexComponents.push_back(component);
	}
}

std::vector<Node*> Graph::getNodes()
{
	return m_nodes;
}

std::vector<Arch*> Graph::getArches()
{
	return m_arches;
}

std::vector<int> Graph::getT2()
{
	return m_t2;
}

std::vector<std::vector<Node*>> Graph::getConexComponents()
{
	return conexComponents;
}

Graph::~Graph()
{

	for (Node*& node : m_nodes) 
	{
		delete node;
	}

	for (Arch*& arch : m_arches) 
	{
		delete arch;
	}
}