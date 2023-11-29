#pragma once
#include <vector>
#include <memory>

#include "Product.h"
#include "TransformedMaterial.h"

class IConsumableBuilder
{
protected:
	std::shared_ptr<Product> result;

public:


	virtual ~IConsumableBuilder() {};
	virtual void reset() = 0;
	virtual void BuildStepA(std::vector<Product> vect) = 0;
	virtual void BuildStepB(std::vector<Product> vect) = 0;
	virtual void BuildStepC(std::vector<Product> vect) = 0;
	virtual std::shared_ptr<Product> getResult() = 0;
};

class buildBed : public IConsumableBuilder
{
public:
	void reset() override {};
	void BuildStepA(std::vector<Product> vect) override 
	{
		if (!vect.empty())
		{

			if (dynamic_cast<Wood*>(&vect.back()) != nullptr)
			{
				vect.pop_back();
				result = std::shared_ptr<Wood>(new Wood(1.2, "Wood"));
			}

		}
		else
		{

		}
	};
	void BuildStepB(std::vector<Product> vect) override 
	{
	
	};
	void BuildStepC(std::vector<Product> vect) override 
	{
	
	};
	std::shared_ptr<Product> getResult() override 
	{
		return result;
	};
};

class buildCar : public IConsumableBuilder
{
public:
	void reset() override {};
	void BuildStepA(std::vector<Product> vect) override
	{
		if (!vect.empty())
		{

			if (dynamic_cast<Iron*>(&vect.back()) != nullptr)
			{
				vect.pop_back();
				result = std::shared_ptr<Iron>(new Iron(1.5, "Wood"));
			}

		}
		else
		{

		}
	};
	void BuildStepB(std::vector<Product> vect) override
	{

	};
	void BuildStepC(std::vector<Product> vect) override
	{

	};
	std::shared_ptr<Product> getResult() override
	{
		return result;
	};
};