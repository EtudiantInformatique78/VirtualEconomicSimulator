#pragma once


class WProduct
{
private:
	float price;
	int quantity;
	shared_ptr<Company> company;

public:

	WProduct(float price, int quantity);
	~WProduct();

	float GetPrice();

};