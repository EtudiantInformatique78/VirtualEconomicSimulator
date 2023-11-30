#pragma once
#include "Product.h"

class Tree : public RawMaterial
{
public:
	Tree(double starting_price, std::string name) : RawMaterial(starting_price, name) {};
	~Tree() {};

	double getStartingPrice() override
	{
		return starting_price;
	}

	std::string getName() override
	{
		return name;
	}
};

class IronOre : public RawMaterial
{
public:
	IronOre(double starting_price, std::string name) : RawMaterial(starting_price, name) {};
	~IronOre() {};

	double getStartingPrice() override
	{
		return starting_price;
	}

	std::string getName() override
	{
		return name;
	}
};