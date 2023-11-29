#pragma once
#include "Factory.h"
#include "TransformedMaterial.h"

class TreeFactory : public TransformedMaterialFactory
{
public:
	std::shared_ptr<TransformedMaterial> produceTransformedMaterial(std::shared_ptr<RawMaterial> rm) override
	{
		std::shared_ptr<Wood> pw = std::shared_ptr<Wood>(new Wood(1.0, "Wood"));
		return pw;
	}
};

class IronFactory : public TransformedMaterialFactory
{
public:
	std::shared_ptr<TransformedMaterial> produceTransformedMaterial(std::shared_ptr<RawMaterial> rm) override
	{
		std::shared_ptr<Iron> pi = std::shared_ptr<Iron>(new Iron(1.1, "Iron"));
		return pi;
	}
};