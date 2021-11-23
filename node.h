
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node
{
public:
	Node();
	Node(int n);
	string toString();
	Node *left;
	Node *right;
	int *freq;
	char ch;
};

Node::Node()
{
	ch = '\0';
	left = nullptr;
	right = nullptr;
	freq = new int(0);
}

Node::Node(int n)
{
	ch = '\0';
	left = nullptr;
	right = nullptr;
	freq = &n;
}

string Node::toString()
{
	stringstream ss;
	ss << *freq;
	return ss.str();
}

bool operator<(Node left, Node right)
{
	return left.freq < right.freq;
}

std::ostream &operator<<(std::ostream &stream, Node *node)
{
	if (node != nullptr)
	{
		stream << node->toString();
		return stream;
	}
	else
	{
		return stream;
	}
}

#endif