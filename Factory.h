#pragma once
#include <memory>
#include "Product.h"
#include "RawMaterials.h"

class Factory
{
public:
	virtual std::shared_ptr<Product> createProduct() = 0;
};


class RawMaterialFactory : public Factory
{
public:
	virtual std::shared_ptr<Product> createProduct() = 0;
};

class IronFactory : public RawMaterialFactory
{
public:
	std::shared_ptr<Product> createProduct() override
	{
		std::shared_ptr<IronOre> pIo = std::shared_ptr<IronOre>(new IronOre(1.5, "Iron Ore"));
		return pIo;
	}
};

class TreeFactory : public RawMaterialFactory
{
public:
	std::shared_ptr<Product> createProduct() override
	{
		std::shared_ptr<Tree> pt = std::shared_ptr<Tree>(new Tree(1.1, "Tree"));
		return pt;
	}
};

/*
class TransformedMaterialFactory : public Factory
{
	virtual std::shared_ptr<TransformedMaterial> produceTransformedMaterial(std::shared_ptr<RawMaterial> rm) = 0;
};

class ConsumableFactory : public Factory
{
	virtual std::shared_ptr<ConsumableGood> produceTransformedMaterial(std::shared_ptr<TransformedMaterial> rm) = 0;
};

*/
