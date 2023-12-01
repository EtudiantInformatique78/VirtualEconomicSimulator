#pragma once

#include "WBaseInclusion.h"
#include "WCompany.h"
#include "WEconomy.h"

class WEconomy;

class WelfareState
{
private:
	shared_ptr<WEconomy> economy;
	
	float salaryPool;
	float transportationPool;
	float researchPool;

public:


	WelfareState();
	~WelfareState();

	void SetEconomy(shared_ptr<WEconomy> _economy);

	void PaySalaries(float value);
	void PayTransportation(float value);
	void PayResearch(float value);

	void DistributeMoney();
	float SellEndProduct(float totalPrice);

};


// WelfareState receive transporation fee to not create a dynamic where company want to sell to the farest one