#include "WBaseInclusion.h"
#include "WProductBaseInfo.h"
#include "WPurchasingWish.h"
#include "WCompany.h"
#include "WMarketPlace.h"
#include "WProduct.h"
#include "WConstants.h"

WMarketPlace::WMarketPlace()
{

}

WMarketPlace::~WMarketPlace()
{

}

void WMarketPlace::Add(shared_ptr<WCompany> newCompany)
{
	companies.push_back(newCompany);
}


void WMarketPlace::Remove(shared_ptr<WCompany> companyToremove)
{
	companies.remove(companyToremove);
}



void WMarketPlace::AddToMarket(shared_ptr<WProductBaseInfo> productBaseInfo, list<shared_ptr<WProduct>> endproductStock)
{
	list<shared_ptr<WProduct>> productList;

	if (marketStocks.count(productBaseInfo)) // Already contain the productKey
		productList = marketStocks[productBaseInfo];

	for (shared_ptr<WProduct> product : endproductStock)
	{
		productList.push_back(product);
	}

	marketStocks[productBaseInfo] = productList;
}

void WMarketPlace::RetrieveEndProductsStocks()
{
	marketStocks.clear();

	// Add all end products of each company to the market
	for (shared_ptr<WCompany> const company : companies)
	{
		shared_ptr<WProductBaseInfo> productBaseInfo = company->GetProductBaseInfo();
		list<shared_ptr<WProduct>> endproductStock = company->GetEndProductStock();

		AddToMarket(productBaseInfo, endproductStock);
	}
}


void WMarketPlace::AddPurchasingWishesCompany(shared_ptr<list<shared_ptr<WPurchasingWish>>> purchasingWishesCompany)
{
	for (shared_ptr<WPurchasingWish> const purchasingWish : *purchasingWishesCompany)
	{
		list<shared_ptr<WPurchasingWish>> purchasingWishes = {};
		shared_ptr<WProductBaseInfo> productbaseInfo = purchasingWish->product;

		if (purchasingWishesByProducts.count(productbaseInfo))
			purchasingWishes = purchasingWishesByProducts[productbaseInfo];

		purchasingWishes.push_back(purchasingWish);
		purchasingWishesByProducts[productbaseInfo] = purchasingWishes;
	}
}

void WMarketPlace::RetrievePurchasingWishes()
{
	purchasingWishesByProducts.clear();

	for (shared_ptr<WCompany> const company : companies)
	{
		shared_ptr<list<shared_ptr<WPurchasingWish>>> purchasingWishesCompany = company->GetPurchasingWishes(company);

		if (purchasingWishesCompany == nullptr)
			continue;

		AddPurchasingWishesCompany(purchasingWishesCompany);
	}
}


int WMarketPlace::CountNbProducts(list<shared_ptr<WProduct>>& products)
{
	int nbProducts = 0;

	for (shared_ptr<WProduct> product : products)
	{
		nbProducts += product->GetQuantity();
	}

	return nbProducts;
}

int WMarketPlace::CountWishesInMarket(shared_ptr<WProductBaseInfo> productBaseInfo)
{
	if (!purchasingWishesByProducts.count(productBaseInfo))
		return 0;

	list<shared_ptr<WPurchasingWish>> productWishes = purchasingWishesByProducts[productBaseInfo];

	int nbQuantity = 0;

	for (shared_ptr<WPurchasingWish> purchasingWish : productWishes)
	{
		nbQuantity += purchasingWish->quantity;
	}

	return nbQuantity;
}

void UpdateFloatingPrice(shared_ptr<WProductBaseInfo> productBaseInfo, int nbProducts, int nbWishes)
{
	float rateToApply = 0;

	if (nbProducts > nbWishes) // market reduce the price
	{

		if (nbWishes == 0)
			rateToApply = 0.9f;
		else
			rateToApply = 1 - (((nbProducts - nbWishes)) / nbWishes * WConstants::PRICE_FLUCTUATION_SCALING);
	}
	else // Market increase the price
	{
		if (nbProducts == 0)
			rateToApply = 1.1f;
		else
			rateToApply = 1 + (((nbWishes - nbProducts)) / nbProducts * WConstants::PRICE_FLUCTUATION_SCALING);
	}

	productBaseInfo->UpdateFloatingPrice(rateToApply);
}


void WMarketPlace::CalculateNewProductsRates()
{
	map<shared_ptr<WProductBaseInfo>, bool> calculatedProducts;

	for (pair<shared_ptr<WProductBaseInfo>, list<shared_ptr<WProduct>>> productStock : marketStocks)
	{
		shared_ptr<WProductBaseInfo> productBaseInfo = productStock.first;
		list<shared_ptr<WProduct>> products = productStock.second;

		calculatedProducts[productBaseInfo] = true;

		int nbProducts = CountNbProducts(products);
		int nbWishes = CountWishesInMarket(productBaseInfo);

		UpdateFloatingPrice(productBaseInfo, nbProducts, nbWishes);
	}

	// Handle the wishes that don't have any stock
	for (pair<shared_ptr<WProductBaseInfo>, list<shared_ptr<WPurchasingWish>>> purchasingWishesByProduct : purchasingWishesByProducts)
	{
		shared_ptr<WProductBaseInfo> productBaseInfo = purchasingWishesByProduct.first;

		if (calculatedProducts.count(productBaseInfo))
			continue;

		calculatedProducts[productBaseInfo] = true;

		list<shared_ptr<WPurchasingWish>> purchasingWish = purchasingWishesByProduct.second;

		int nbProducts = 0;
		int nbWishes = CountWishesInMarket(productBaseInfo);

		UpdateFloatingPrice(productBaseInfo, nbProducts, nbWishes);
	}
}

void WMarketPlace::SelectCompanyDeals()
{

}