#pragma once

#include <random>
#include "WBaseInclusion.h"
#include "WProductBaseInfo.h"
#include "WPurchasingWish.h"
#include "WCompany.h"
#include "WProduct.h"
#include "WConstants.h"
#include "WEconomy.h"
#include "WPriceDetailsPerUnit.h"
#include <limits>

class WEconomy;
class WPurchasingWish;
/// <summary>
/// Act as the intermediary between the companies.
/// The market choose which company buy to which other one
/// </summary>
class WMarketPlace
{
private:
	shared_ptr<WEconomy> economy;

	map<shared_ptr<WProductBaseInfo>, list<shared_ptr<WProduct>>> marketStocks;
	map<shared_ptr<WProductBaseInfo>, list<shared_ptr<WPurchasingWish>>> purchasingWishesByProducts;


public:
	WMarketPlace();
	~WMarketPlace();

	void SetEconomy(shared_ptr<WEconomy> _economy);

	void Add(shared_ptr<WCompany> newCompany);
	void Remove(shared_ptr<WCompany> companyToremove);

	void ExecuteDailyOperations();
	void ExecuteCompanyDeals();

	void RetrieveEndProductsStocks();
	void RetrievePurchasingWishes();

	void AddToMarket(shared_ptr<WProductBaseInfo> productBaseInfo, list<shared_ptr<WProduct>> endproductStock);
	void AddPurchasingWishesCompany(shared_ptr<list<shared_ptr<WPurchasingWish>>> purchasingWishesCompany);

	//void CalculateNewProductsRates();
	int CountNbProducts(list<shared_ptr<WProduct>>& products);
	int CountWishesInMarket(shared_ptr<WProductBaseInfo> productBaseInfo);
	void ExecuteCompanyDealsByProduct(shared_ptr<WProductBaseInfo> productBaseInfo, list<shared_ptr<WPurchasingWish>> purchasingWishes);

	pair<shared_ptr<WProduct>, shared_ptr<WPriceDetailsPerUnit>> GetCheapestProduct(shared_ptr<WPurchasingWish> purchasingWish, list<shared_ptr<WProduct>>& marketStock);

};