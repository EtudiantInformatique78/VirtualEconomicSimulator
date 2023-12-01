#pragma once
#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"

class WProductBaseInfo
{
private:
	ProductTreeState productTreeState;

public:
	const string name;
	const int id;

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

	void SetProductTreeStateAsBottom();


	void AddCompositionProduct(int quantity, shared_ptr<WProductBaseInfo> compositionProduct);

	ProductTreeState GetProductTreeState();
};