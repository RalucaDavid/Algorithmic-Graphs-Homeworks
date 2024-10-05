#pragma once
#include "Node.h"

class Arch
{
private:
	Node* m_source;
	Node* m_destination;
public:
	Arch();
	Arch(Node* source, Node* destination);
	void setSourceNode(Node* source);
	void setDestinationNode(Node* destination);
	Node* getSourceNode();
	Node* getDestinationNode();
};
