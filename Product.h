#pragma once
#include <string>

class Product
{
protected:
	double starting_price;
	std::string name;

public:
	Product(double starting_price, std::string name) : starting_price(starting_price), name(name) {};
	virtual ~Product() {};

	virtual double getStartingPrice() = 0;
	virtual std::string getName() = 0;
};

class RawMaterial : public Product
{
public:
	RawMaterial(double starting_price, std::string name) : Product(starting_price, name) {};
	virtual ~RawMaterial() {};
};

class TransformedMaterial : public Product
{
public:
	TransformedMaterial(double starting_price, std::string name) : Product(starting_price, name) {};
	virtual ~TransformedMaterial() {};
};

class ConsumableGood : public Product
{
public:
	ConsumableGood(double starting_price, std::string name) : Product(starting_price, name) {};
	virtual ~ConsumableGood() {};
};