#pragma once
#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"

class WProductBaseInfo
{
private:
	float floatingPrice;

public:
	const string name;
	const int id;

	const float basePrice;
	const float baseRate;
	const float baseMargin;

	const int employeDayUnit;
	const float fabricationCost;

	/// <summary>
	/// Per kms
	/// </summary>
	const float transportationCostPerKm;

	map<shared_ptr<WProductBaseInfo>, int> composition;

	WProductBaseInfo(int _id, WProductBaseInfoBuilder _builder);
	~WProductBaseInfo();

	void UpdateFloatingPrice(float rate);
	float GetFloatingPrice();
};