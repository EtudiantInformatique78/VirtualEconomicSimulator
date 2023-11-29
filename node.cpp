#include "node.h"

Node::Node(Point* _point, Node* _parent, double _fCost, double _distanceWithStart)
{
	point = _point;
	parent = _parent;
	fCost = _fCost;
	distanceWithStart = _distanceWithStart;
}

Node::~Node()
{
}

Node* Node::getParent() const
{
	return parent;
}

Point* Node::getPoint() const
{
	return point;
}

double Node::getFCost() const
{
	return fCost;
}

double Node::getDistanceWithStart() const
{
	return distanceWithStart;
}
