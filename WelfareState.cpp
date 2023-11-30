
#include "WelfareState.h"

WelfareState::WelfareState(shared_ptr<WEconomy> _economy) : economy(economy)
{
	salaryPool = 0;
	transportationPool = 0;
}

WelfareState::~WelfareState()
{

}


void WelfareState::PaySalaries(float value)
{
	salaryPool += value;
}

void WelfareState::PayTransportation(float value)
{
	transportationPool += value;
}

void WelfareState::DistributeMoney()
{
	list<shared_ptr<WCompany>> companies = economy->GetCompanies();
	int nbCompanies = companies.size();

	float giveOut = (salaryPool / nbCompanies) + (transportationPool / nbCompanies);
	
	for (shared_ptr<WCompany> company : companies)
	{
		company->ReceiveMoney(giveOut);
	}

	salaryPool = 0;
	transportationPool = 0;
}
