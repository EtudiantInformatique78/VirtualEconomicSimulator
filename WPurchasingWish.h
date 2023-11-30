#pragma once

class WCompany;

class WPurchasingWish
{
public:
	const shared_ptr<WCompany> company;
	const shared_ptr<WProductBaseInfo> product;
	const int quantity;

	WPurchasingWish(shared_ptr<WCompany> _company, shared_ptr<WProductBaseInfo> _product, int _quantity);
	~WPurchasingWish();
};