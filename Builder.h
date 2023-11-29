#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "Product.h"

#include "Factory.h"
#include "TransformedMaterial.h"

class IBuilder
{
public:
	virtual ~IBuilder() {};
	virtual void reset() = 0;
	virtual void Build(std::vector<Product> vect) = 0;
	virtual std::shared_ptr<Product> getResult() = 0;
};

class MakeWood : public IBuilder
{
private:
	std::shared_ptr<Product> result;

	void reset() override
	{
	}
	void Build(std::vector<Product> vect) override
	{
		if(!vect.empty())
		{
			
			if(dynamic_cast<Tree*>(  &vect.back()) != nullptr)
			{
				vect.pop_back();
				result = std::shared_ptr<Wood>(new Wood(1.2, "Wood"));
			}

		}
		else
		{
			
		}
		
	}

	std::shared_ptr<Product> getResult() override
	{
		return result;
	}

};

class MakeIron : public IBuilder
{
private:
	std::shared_ptr<Product> result;

	void reset() override
	{
	}
	void Build(std::vector<Product> vect) override
	{
		if (!vect.empty())
		{
			if (dynamic_cast<Iron*>(&vect.back()) != nullptr)
			{
				vect.pop_back();
				result = std::shared_ptr<Iron>(new Iron(1.5, "Iron"));
			}
		}
		else
		{

		}

	}

	std::shared_ptr<Product> getResult() override
	{
		return result;
	}

};

