#pragma once

#include <iostream>
#include <cstdlib>

#include "point.h"

class Node
{
public:
	Node(Point* _point, Node* _parent = NULL, double _fCost = 0, double _distanceWithStart = 0);
	~Node();
	Node* getParent() const;
	Point* getPoint() const;
	double getFCost() const;
	double getDistanceWithStart() const;

private:
	// No smart pointer here to avoir circular dependencies. As we may have NULL here, we can't use weak_ptr neither 
	Node* parent;
	Point* point;
	double fCost;
	double distanceWithStart;
};