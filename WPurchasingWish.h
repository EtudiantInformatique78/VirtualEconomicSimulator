#pragma once
#include "WBaseInclusion.h"
#include "WProductBaseInfo.h"
#include "WCompany.h"

class WCompany;

class WPurchasingWish
{
public:
	const shared_ptr<WCompany> company;
	const shared_ptr<WProductBaseInfo> product;
	
	int quantity;

	WPurchasingWish(shared_ptr<WCompany> _company, shared_ptr<WProductBaseInfo> _product, int _quantity);
	~WPurchasingWish();

	void RemoveQuantity(int value);
};