#include "BaseInclusion.h"
#include <iostream>
#include "WProduct.h"

WProduct::WProduct(float _price, int _quantity, shared_ptr<Company> _company) : price(_price)
{
	quantity = _quantity;
	company = _company;
}

WProduct::~WProduct()
{

}

float WProduct::GetPrice()
{
	return price;
}