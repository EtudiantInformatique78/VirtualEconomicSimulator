#pragma once
#include "WBaseInclusion.h"
#include "ProductTreeState.h"

class WProductBaseInfoBuilder
{
public:
	int id;
	string name;

	float basePrice;
	float baseMargin;

	float baseProductionCost;
	int employeDayUnit;


	float transportationCostPerkmPerUnit;

	string composition;

	ProductTreeState productTreeState;

	WProductBaseInfoBuilder();
	~WProductBaseInfoBuilder();
};