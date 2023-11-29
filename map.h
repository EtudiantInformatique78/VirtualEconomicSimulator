#pragma once

#include <deque>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <map>

#include "point.h"
#include "node.h"

enum class COORDINATE_DIRECTION
{
	POSITIVE,
	NEGATIVE
};

class Map
{
public:
	Map(int _xSize, int _ySize);
	~Map();

	void displayMap() const;
	void createNewPoint(int x, int y, FIELD_TYPE fieldType);
	void searchForPath(int startingX, int startingY, int destinationX, int destinationY);

private:
	int xSize;
	int ySize;
	int smallestX;
	int greatestX;
	int smallestY;
	int greatestY;
	std::deque<std::deque<Point>> board;
	/*
	* Map storing FIELD_TYPE as key.
	* The value is composed of 2 elements: the first one is the character to display for this field type, the second is the speed modifier to apply on the pathfinding algorithm.
	*/
	std::map<FIELD_TYPE, std::pair<char, double>> fieldTypeInformations;

	void createNewColumn(COORDINATE_DIRECTION direction);
	void createNewLine(COORDINATE_DIRECTION direction);
	Point* getPoint(int x, int y);
	double getDistanceBetweenTwoPoint(int x1, int y1, int x2, int y2) const;
	void drawSolution(std::shared_ptr<Node> finalNode) const;
	bool isInPath(Node* finalNode, const Point& cell) const;
	Node* getFirstNode(Node* finalNode) const;
	std::shared_ptr<Node> getLowestFCostIndex(const std::unordered_map<std::string, std::shared_ptr<Node>>& list) const;
	bool isStartAndDestinationPointOnTheMap(int startingX, int startingY, int destinationX, int destinationY) const;
};
