
#include "WelfareState.h"

WelfareState::WelfareState()
{
	salaryPool = 0;
	transportationPool = 0;
	researchPool = 0;
}

WelfareState::~WelfareState()
{

}

void WelfareState::SetEconomy(shared_ptr<WEconomy> _economy)
{
	economy = _economy;
}


void WelfareState::PaySalaries(float value)
{
	salaryPool += value;
}

void WelfareState::PayTransportation(float value)
{
	transportationPool += value;
}

void WelfareState::PayResearch(float value)
{
	researchPool += value;
}

void WelfareState::DistributeMoney()
{
	list<shared_ptr<WCompany>> companies = economy->GetCompanies();
	int nbCompanies = companies.size();

	float giveOut = (salaryPool / nbCompanies) + (transportationPool / nbCompanies) + (researchPool / nbCompanies);
	
	for (shared_ptr<WCompany> company : companies)
	{
		company->ReceiveMoney(giveOut);
	}

	salaryPool = 0;
	transportationPool = 0;
	researchPool = 0;
}

float WelfareState::SellEndProduct(float totalPrice)
{
	// useless return system function but in case implement other system here (keep it for now !)
	// monetary creation here, like the real economy, to expend the activities
	return totalPrice;
}