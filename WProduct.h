#pragma once
#include "WBaseInclusion.h"
#include <iostream>

class WCompany;

class WProduct
{
private:
	
	int quantity;

public:

	const float deltaCompanyPricePerUnit;
	const shared_ptr<WCompany> company;

	WProduct(float _deltaCompanyPricePerUnit, int _quantity, shared_ptr<WCompany> company);
	~WProduct();

	float GetPrice(int quantity);
	int GetQuantity();

	shared_ptr<WProduct> Extract(int quantity);

};


// DeltaCompanyPrice represent the price of the added value of the company
// so it need to be added with the WProductBaseInfo.floatingprice to represent the real value (and the transportation price after)