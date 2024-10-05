#include "Node.h"

Node::Node()
{
    m_value = -1;
}

Node::Node(QPoint position, int value) :m_position(position), m_value(value)
{
}

Node::Node(const Node& other)
{
    m_position = other.m_position;
    m_value = other.m_value;
    neighbors = other.neighbors;
}

void Node::AddNeighbor(Node* node)
{
    neighbors.push_back(node);
}

void Node::SetValue(int value)
{
    m_value = value;
}

void Node::SetPosition(QPoint position)
{
    m_position = position;
}

std::list<Node*> Node::GetNeighbors()
{
    return neighbors;
}

int Node::GetValue()
{
    return m_value;
}

QPoint Node::GetPosition()
{
    return m_position;
}

bool Node::operator==(Node node)
{
    if ((m_value == node.m_value) && (m_position == node.m_position))
        return true;
    return false;
}
