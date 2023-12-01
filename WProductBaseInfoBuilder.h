#pragma once
#include "WBaseInclusion.h"

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

	WProductBaseInfoBuilder();
	~WProductBaseInfoBuilder();
};