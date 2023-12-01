#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <regex>

#include "Product.h"

#include "Factory.h"
#include "TransformedMaterial.h"

static void printWatchOutMessage(unsigned int line, std::string productName)
{
	std::string message = __FILE__;
	std::string regex_expression = "repos\\\\(.*\\\\(\\w*\\.(h|cpp)))";
	const std::regex r = std::regex(regex_expression); // repos.*\\(\w*\.(h|cpp))
	std::smatch m;
	if (std::regex_search(message, m, r))
	{
		message = m[1].str();
	}
	message += " at line : ";
	message += std::to_string(line);
	message = message + ". Don't forget to ensure that we only use " + productName;
	std::cout << message << std::endl;
	
}

class IBuilder
{
protected:
	std::shared_ptr<Product> result;

public:
	virtual ~IBuilder() {};
	virtual void reset() = 0;
	virtual void Build(std::vector<std::shared_ptr<Product>> &vect) = 0;
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
		result = nullptr;
	}
	void Build(std::vector<std::shared_ptr<Product>> &vect) override
	{
		if(!vect.empty())
		{
			//std::shared_ptr<Tree> tree_ptr = std::dynamic_pointer_cast<Tree>(vect.back());			
			printWatchOutMessage(__LINE__, "Tree");
			
			vect.pop_back();
			result = std::shared_ptr<Wood>(new Wood(1.2, "Wood"));

		}
		else
		{
			std::cout << "No product to transform" << std::endl;
		}
		
	}


};

class MakeIron : public IBuilder
{
public:
	void reset() override
	{
	}
	void Build(std::vector<std::shared_ptr<Product>> &vect) override
	{
		if (!vect.empty())
		{
			printWatchOutMessage(__LINE__, "Iron ore");
			vect.pop_back();
			result = std::shared_ptr<Iron>(new Iron(1.5, "Iron"));
			
		}
		else
		{

		}

	}

};

