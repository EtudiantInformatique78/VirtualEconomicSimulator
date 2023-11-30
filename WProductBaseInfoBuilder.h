#pragma once
#include "WBaseInclusion.h"

class WProductBaseInfoBuilder
{
public:
	string name;

	float basePrice;
	float baseRate;
	float baseMargin;

	int employeDayUnit;
	float fabricationCost;

	/// <summary>
	/// Per kms
	/// </summary>
	float transportationCost;

	WProductBaseInfoBuilder();
	~WProductBaseInfoBuilder();
};