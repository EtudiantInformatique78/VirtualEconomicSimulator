#pragma once


class WPriceDetailsPerUnit
{
public:
	const float floatingPrice;
	const float transportationPrice;
	const float deltaCompanyPrice;


	WPriceDetailsPerUnit(float _floatingPrice, float _transportationPrice, float _deltaCompanyPrice);
	~WPriceDetailsPerUnit();
};