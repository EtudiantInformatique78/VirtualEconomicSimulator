#include <iostream>
#include "WProduct.h"
#include "Company.h"

using namespace std;

WProduct::WProduct(float _price, int _quantity)
{
	price = _price;
	quantity = _quantity;
}

WProduct::~WProduct()
{

}

float WProduct::GetPrice()
{
	return price;
}