#pragma once

#include "WBaseInclusion.h"
#include "WCompany.h"


/// <summary>
/// "Main" of the economic system
/// </summary>
class WEconomy
{
private:
	list<shared_ptr<WCompany>> companies;

public:

	WEconomy();
	~WEconomy();

	list<shared_ptr<WCompany>> GetCompanies();


};