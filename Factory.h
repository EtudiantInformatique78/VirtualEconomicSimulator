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
	virtual TransformedMaterial produceTransformedMaterial(RawMaterial rm) = 0;
};

class ConsumableFactory : public Factory
{
	virtual ConsommableGood produceTransformedMaterial(TransformedMaterial rm) = 0;
};