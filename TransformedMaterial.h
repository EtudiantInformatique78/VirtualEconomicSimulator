#pragma once
#include "Product.h"

class Iron : public TransformedMaterial
{
public:
	Iron(double starting_price, std::string name) : TransformedMaterial(starting_price, name) {};
	~Iron();

	double getStartingPrice() override
	{
		return starting_price;
	}

	std::string getName() override
	{
		return name;
	}
};

class Wood : public TransformedMaterial
{
public:
	Wood(double starting_price, std::string name) : TransformedMaterial(starting_price, name) {};
	~Wood();

	double getStartingPrice() override
	{
		return starting_price;
	}

	std::string getName() override
	{
		return name;
	}
};