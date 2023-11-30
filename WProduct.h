#pragma once


class Company;

class WProduct
{
private:
	
	int quantity;
	shared_ptr<Company> company;

public:

	const float price;

	WProduct(float _price, int _quantity, shared_ptr<Company> company);
	~WProduct();

	float GetPrice();

};