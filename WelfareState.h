#pragma once

#include "WBaseInclusion.h"
#include "WCompany.h"
#include "WEconomy.h"

class WelfareState
{
private:
	const shared_ptr<WEconomy> economy;
	
	float salaryPool;
	float transportationPool;

public:


	WelfareState(shared_ptr<WEconomy> _economy);
	~WelfareState();

	void PaySalaries(float value);
	void PayTransportation(float value);

	void DistributeMoney();


};


// WelfareState receive transporation fee to not create a dynamic where company want to sell to the farest one