#include "Graph.h"

Graph::Graph()
{
	/*empty*/
}

void Graph::AddNode(int value,std::pair<float,float> coord)
{
	Node* newNode = new Node(value,coord);
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

void GenerateCoords(float& coord1, float&coord2)
{
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_real_distribution<> dis(0,6);
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
		GenerateCoords(coord1,coord2);
		AddNode(index,std::make_pair(coord1,coord2));
	}
	for (int index = 0; index < dimension; index++)
	{
		for (int jndex = 0; jndex < dimension; jndex++)
		{
			if (matrix[index][jndex]== 1)
			{
				AddArch(m_nodes[index], m_nodes[jndex]);
			}
		}
	}
}

bool Graph::PTDF()
{
	Node* entry = m_nodes[0]; // s
	std::vector<Node*>U; // unvisited nodes
	std::stack<Node*>V; // visited and unanalyzed nodes
	std::stack<Node*>W; // visited and analyzed nodes
	std::vector<int> p; // predecessors
	std::vector<int> t1;
	std::vector<int> t2;
	std::vector<int> color;
	V.push(entry);
	for (Node*& node : m_nodes)
		if (node->getValue() != entry->getValue())
			U.push_back(node);
	for (int index = 0; index < m_nodes.size(); index++)
	{
		p.push_back(-1);
		t1.push_back(0);
		t2.push_back(0);
		color.push_back(0);
	}
	t1[entry->getValue()] = 1;
	int t = 1;
	while (!U.empty() || !V.empty()) 
	{
		while (!V.empty()) 
		{
			Node* x = V.top();
			color[x->getValue()] = 1;
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
					archesTS.push_back(Arch(x, y));
					break;
				}
			}
			if (ok == 0)
			{
				color[x->getValue()] = 2;
				V.pop();
				W.push(x);
				t2[x->getValue()] = ++t;
			}
			for (Node* y : x->getNeighbors())
			{
				if (color[y->getValue()] == 1)
					return false;
			}
		}
		if (!U.empty()) {
			Node* entry = U.front();
			U.erase(U.begin());
			V.push(entry);
			t1[entry->getValue()] = ++t;
		}
	}
	ShowTopologicalSorting(t2);
	return true;
}

void Graph::ShowTopologicalSorting(std::vector<int>t2)
{
	std::ofstream fout("Output.txt");
	fout << "Topological Sorting Order:\n";
	std::vector<std::pair<int, int>> indexValuePair;
	for (int index = 0; index < t2.size(); ++index) 
	{
		indexValuePair.push_back(std::make_pair(index, t2[index]));
	}
	std::sort(indexValuePair.begin(), indexValuePair.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
		});
	for (const auto& pair : indexValuePair) 
	{
		fout << pair.first << ' ';
	}
	fout.close();
}

std::vector<Node*> Graph::getNodes()
{
	return m_nodes;
}

std::vector<Arch*> Graph::getArches()
{
	return m_arches;
}

std::vector<Arch> Graph::getArchesTS()
{
	return archesTS;
}

Graph::~Graph()
{
	for (Node*& node : m_nodes) {
		delete node;
	}

	for (Arch*& arch : m_arches) {
		delete arch;
	}
}