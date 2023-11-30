#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "Product.h"

#include "Factory.h"
#include "TransformedMaterial.h"

class IBuilder
{
protected:
	std::shared_ptr<Product> result;

public:
	virtual ~IBuilder() {};
	virtual void reset() = 0;
	virtual void Build(std::vector<std::shared_ptr<Product>> vect) = 0;
	std::shared_ptr<Product> getResult()
	{
		return result;
	}
};

class MakeWood : public IBuilder
{
public:
	MakeWood() : IBuilder() {};
	~MakeWood() {};

	void reset() override
	{
	}
	void Build(std::vector<std::shared_ptr<Product>> vect) override
	{
		if(!vect.empty())
		{
			//std::shared_ptr<Tree> tree_ptr = std::dynamic_pointer_cast<Tree>(vect.back());
			std::cout << "Line : " << __LINE__ << "Don't forget to ensure that we only use Tree" << std::endl;
			vect.pop_back();
			result = std::shared_ptr<Wood>(new Wood(1.2, "Wood"));

		}
		else
		{
			
		}
		
	}


};

class MakeIron : public IBuilder
{
public:
	void reset() override
	{
	}
	void Build(std::vector<std::shared_ptr<Product>> vect) override
	{
		if (!vect.empty())
		{
			std::cout << "Line : " << __LINE__ << "Don't forget to ensure that we only use Iron ore" << std::endl;
			vect.pop_back();
			result = std::shared_ptr<Iron>(new Iron(1.5, "Iron"));
			
		}
		else
		{

		}

	}

};

