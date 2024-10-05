#include "Arch.h"

Arch::Arch() : m_source(nullptr), m_destination(nullptr)
{
	/*empty*/
}

Arch::Arch(Node* source, Node* destination) :m_source(source), m_destination(destination)
{
	/*empty*/
}

void Arch::setSourceNode(Node* source)
{
	m_source = source;
}

void Arch::setDestinationNode(Node* destination)
{
	m_destination = destination;
}

Node* Arch::getSourceNode()
{
	return m_source;
}

Node* Arch::getDestinationNode()
{
	return m_destination;
}