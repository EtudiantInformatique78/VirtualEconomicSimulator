#pragma once
#include <memory>
#include "Product.h"

class Factory
{
public:
	virtual std::shared_ptr<Product> createProduct() = 0;
};

class TransformedMaterialFactory : public Factory
{
	virtual std::shared_ptr<TransformedMaterial> produceTransformedMaterial(std::shared_ptr<RawMaterial> rm) = 0;
};

class ConsumableFactory : public Factory
{
	virtual std::shared_ptr<ConsommableGood> produceTransformedMaterial(std::shared_ptr<TransformedMaterial> rm) = 0;
};