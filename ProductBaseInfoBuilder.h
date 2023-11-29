#pragma once


class ProductBaseInfoBuilder
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

	ProductBaseInfoBuilder();
	~ProductBaseInfoBuilder();
};