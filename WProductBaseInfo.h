#pragma once
#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"

class WProductBaseInfo
{
private:
	float floatingPricePerUnit;

public:
	const string name;
	const int id;

	const float basePrice;

	/// <summary>
	/// In % -> ex : .20
	/// </summary>
	const float baseMargin;

	const float baseProductionCost;
	const int employeDayUnit;

	const float transportationCostPerKmPerUnit;

	map<shared_ptr<WProductBaseInfo>, int> composition;

	WProductBaseInfo(shared_ptr<WProductBaseInfoBuilder> _builder);
	~WProductBaseInfo();

	void UpdateFloatingPrice(float rate);
	float GetFloatingPricePerUnit();

	void AddCompositionProduct(int quantity, shared_ptr<WProductBaseInfo> compositionProduct);
};