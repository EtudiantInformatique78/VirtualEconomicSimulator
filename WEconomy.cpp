#include "WEconomy.h"


WEconomy::WEconomy()
{

}

WEconomy::~WEconomy()
{

}

list<shared_ptr<WCompany>> WEconomy::GetCompanies()
{
	return companies;
}