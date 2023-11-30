#include "WBaseInclusion.h"

#include "WProductBaseInfoBuilder.h"
#include "WProductBaseInfo.h"
#include "WPurchasingWish.h"
#include "WProduct.h"
#include "WCompany.h"
#include "WConstants.h"

WCompany::WCompany(shared_ptr<WProductBaseInfo> _productBaseInfo, pair<int,int> _position)
{
	capital = WConstants::COMPANY_START_CAPITAL;
	nbEmploye = WConstants::NB_EMPLOYE_START;
	salaryEmploye = WConstants::SALARY_EMPLOYE_START;
	rAndDLevel = 1;
	position = _position;

	productBaseInfo = _productBaseInfo;
}

WCompany::~WCompany()
{

}


void WCompany::ApplyWorkDay()
{

}

list<shared_ptr<WProduct>> WCompany::GetEndProductStock()
{
	return endProductStock;
}

shared_ptr<WProductBaseInfo> WCompany::GetProductBaseInfo()
{
	return productBaseInfo;
}

int WCompany::GetNbOfPossibleProductToBuild()
{
	if (nbAvailableEmploye == 0)
		return 0;

	int unitWork = productBaseInfo->employeDayUnit;
	int nbOfPossibleProductToBuild = unitWork / nbAvailableEmploye;

	return nbOfPossibleProductToBuild;
}


shared_ptr<list<shared_ptr<WPurchasingWish>>> WCompany::GetPurchasingWishes(shared_ptr<WCompany> thisPtr)
{
	int nbOfPossibleProductToBuild = GetNbOfPossibleProductToBuild();

	if (nbOfPossibleProductToBuild == 0)
		return nullptr;

	shared_ptr<list<shared_ptr<WPurchasingWish>>> listWishes = make_shared<list<shared_ptr<WPurchasingWish>>>();
	map<shared_ptr<WProductBaseInfo>, int> composition = productBaseInfo->composition;

	for (pair<shared_ptr<WProductBaseInfo>, int> comp : composition)
	{
		shared_ptr<WProductBaseInfo> productBaseInfo = comp.first;
		int quantity = comp.second;

		quantity *= nbOfPossibleProductToBuild;

		shared_ptr<WPurchasingWish> purchasingWish = make_shared<WPurchasingWish>(thisPtr, productBaseInfo, quantity);
		listWishes->push_back(purchasingWish);
	}

	return listWishes;
}

void WCompany::ReceiveMoney(float amount)
{
	capital += amount;
}