#pragma once


class WCompany;

class WProduct
{
private:
	
	int quantity;

public:

	const float price;
	const shared_ptr<WCompany> company;

	WProduct(float _price, int _quantity, shared_ptr<WCompany> company);
	~WProduct();

	float GetPrice();
	int GetQuantity();

	shared_ptr<WProduct> Extract(int quantity);

};