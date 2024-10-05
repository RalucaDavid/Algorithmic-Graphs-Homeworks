#include "Graph.h"

Graph::Graph()
{

}

void Graph::AddNode(Node* node)
{
	nodes.push_back(node);
}

void Graph::AddNode(QPoint position)
{
	bool verify = true;
	for (Node*& node : nodes)
	{
		if (((node->GetPosition().x() - 20 <= position.x()) && (position.x() <= node->GetPosition().x() + 30)) &&
			((node->GetPosition().y() - 20 <= position.y()) && (position.y() <= node->GetPosition().y() + 30)))
		{
			verify = false;
			break;
		}
	}
	if (verify == true)
	{
		Node* node = new Node(position,nodes.size());
		nodes.push_back(node);
	}
}

void Graph::AddArch(Arch* arch)
{
	arches.push_back(arch);
}

void Graph::AddArch(Node* node1, Node* node2, int cost)
{
	bool verify = true;
	for (Arch*& arch : arches)
	{
		if (((arch->GetFirstNode() == node1) && (arch->GetSecondNode() == node2)) ||
				((arch->GetSecondNode() == node1) && (arch->GetFirstNode() == node2)))
			{
				verify = false;
				break;
			}
	}
	if (verify == true)
	{
		Arch* newArch = new Arch(node1, node2, cost);
		arches.push_back(newArch);
		node1->AddNeighbor(node2);
		node2->AddNeighbor(node1);
	}
}

std::vector<Node*>& Graph::GetNodes()
{
	return nodes;
}

std::vector<Arch*>& Graph::GetAches()
{
	return arches;
}

int findSet(Node* node, const std::vector<std::vector<Node*>>& sets)
{
	for (size_t index = 0; index < sets.size(); index++)
	{
		if (std::find(sets[index].begin(), sets[index].end(), node) != sets[index].end())
			return index;
	}
	return -1;
}

//Total: n+mlogm+n*(m+n) = n+mlogm+n^2*(m+1) aprox. egal O(n^2)
void Graph::Generic()
{
	std::vector<std::vector<Node*>>M;
	std::vector<std::vector<Arch*>>A(nodes.size());
	std::vector<Arch*> finalArches;
	//O(n)
	for (Node*& node : nodes)
	{
		std::vector<Node*> Ni;
		Ni.push_back(node);
		M.push_back(Ni);
	}
	int jndex;
	//O(mlogm)
	std::sort(arches.begin(), arches.end(), [](Arch* a, Arch* b) {
		return a->GetCost() < b->GetCost();
		});
	//O(n)
	for (int k = 0; k < nodes.size() - 1; k++)
	{
		int index = 0;
		Arch* minArch = nullptr;
		Node* findNode = nullptr;
		//O(m)
		for (Arch* arch : arches)
		{
			if (((std::find(M[index].begin(), M[index].end(), arch->GetFirstNode()) == M[index].end() &&
				std::find(M[index].begin(), M[index].end(), arch->GetSecondNode()) != M[index].end()) &&
				std::find(finalArches.begin(), finalArches.end(), arch) == finalArches.end()))
			{
				minArch = arch;
				findNode = arch->GetFirstNode();
				break;
			}
			else if (((std::find(M[index].begin(), M[index].end(), arch->GetFirstNode()) != M[index].end() &&
				std::find(M[index].begin(), M[index].end(), arch->GetSecondNode()) == M[index].end())) &&
				std::find(finalArches.begin(), finalArches.end(), arch) == finalArches.end())
			{
				minArch = arch;
				findNode = arch->GetSecondNode();
				break;
			}
		}
		if (minArch != nullptr)
		{
			finalArches.push_back(minArch);
			minArch->SetColor(1);
			//O(n)
			jndex = findSet(findNode, M);
			M[index].insert(M[index].end(), M[jndex].begin(), M[jndex].end());
			M[jndex].clear();
			A[index].insert(A[index].end(), A[jndex].begin(), A[jndex].end());
			A[index].push_back(minArch);
			A[jndex].clear();
			M.erase(std::remove_if(M.begin(), M.end(), [](const std::vector<Node*>& set) {
				return set.empty();
				}), M.end());
		}
		if (k == nodes.size() - 1)
			finalArches.insert(finalArches.end(), A[index].begin(), A[index].end());
	}
}

//Total: n+mlogm+mlogn*(n*(m+n)
// n+mlogm+mlogn*n*(m+1) estimativ = O(n*m)+O(mlogm) care simplificat poate fi O(mlogm)
void Graph::Boruvka()
{
	std::vector<std::vector<Node*>>M;
	std::vector<Arch*> finalArches;
	//O(n)
	for (Node*& node:nodes)
	{
		std::vector<Node*> Ni;
		Ni.push_back(node);
		M.push_back(Ni);
	}
	int jndex;
	//O(mlogm)
	std::sort(arches.begin(), arches.end(), [](Arch* a, Arch* b) {
		return a->GetCost() < b->GetCost();
		});
	//O(m*logn)
	while (finalArches.size() < nodes.size() - 1)
	{
		std::vector<std::vector<Node*>> M_new;
		//O(n)
		for (auto& Ni : M)
		{
			Arch* minArch = nullptr;
			Node* findNode = nullptr;
			//O(m)
			for (Arch* arch : arches)
			{
				if (((std::find(Ni.begin(), Ni.end(), arch->GetFirstNode()) == Ni.end() &&
					std::find(Ni.begin(), Ni.end(), arch->GetSecondNode()) != Ni.end()) &&
					std::find(finalArches.begin(), finalArches.end(), arch) == finalArches.end()))
				{
					minArch = arch;
					findNode = arch->GetFirstNode();
					break;
				}
				else if (((std::find(Ni.begin(), Ni.end(), arch->GetFirstNode()) != Ni.end() &&
					std::find(Ni.begin(), Ni.end(), arch->GetSecondNode()) == Ni.end())) &&
					std::find(finalArches.begin(), finalArches.end(), arch) == finalArches.end())
				{
					minArch = arch;
					findNode = arch->GetSecondNode();
					break;
				}
			}
			if (minArch != nullptr)
			{
				finalArches.push_back(minArch);
				minArch->SetColor(2);
				//O(n)
				jndex = findSet(findNode, M);
				Ni.insert(Ni.end(), M[jndex].begin(), M[jndex].end());
				M[jndex].clear();
				M.erase(std::remove_if(M.begin(), M.end(), [](const std::vector<Node*>& set) {
					return set.empty();
					}), M.end());
			}
			M_new.push_back(Ni);
		}
		M = M_new;
	}
}

Graph::~Graph()
{
	for (Node*& node : nodes) 
	{
		delete node;
	}
	for (Arch*& arch : arches) 
	{
		delete arch;
	}
}
