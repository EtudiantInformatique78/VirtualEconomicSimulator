#pragma once


class ProductBaseInfo
{
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
	const float transportationCost;

	vector<map<shared_ptr<ProductBaseInfo>, int>> composition;

	ProductBaseInfo(int _id, ProductBaseInfoBuilder _builder);
	~ProductBaseInfo();
};