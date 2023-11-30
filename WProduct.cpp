#include "WBaseInclusion.h"
#include <iostream>
#include "WProduct.h"

WProduct::WProduct(float _price, int _quantity, shared_ptr<WCompany> _company) : price(_price), company(_company)
{
	quantity = _quantity;
}

WProduct::~WProduct()
{

}

float WProduct::GetPrice()
{
	return price;
}

int WProduct::GetQuantity()
{
	return quantity;
}

shared_ptr<WProduct> WProduct::Extract(int quantityToExtract)
{
	if (quantityToExtract >= quantity)
		return nullptr;

	quantity = -quantityToExtract;

	shared_ptr<WProduct> extractedProduct = make_shared<WProduct>(price, quantityToExtract, company);

	return extractedProduct;
}