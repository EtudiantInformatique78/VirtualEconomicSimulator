#pragma once


class WPriceDetailsPerUnit
{
public:
	const float transportationPrice;
	const float deltaCompanyPrice;


	WPriceDetailsPerUnit(float _transportationPrice, float _deltaCompanyPrice);
	~WPriceDetailsPerUnit();
};