#include "WMarketPlace.h"

WMarketPlace::WMarketPlace()
{

}

WMarketPlace::~WMarketPlace()
{

}

void WMarketPlace::SetEconomy(shared_ptr<WEconomy> _economy)
{
	economy = _economy;
}

void WMarketPlace::Add(shared_ptr<WCompany> newCompany)
{
	auto companies = economy->GetCompanies();
	companies.push_back(newCompany);
}


void WMarketPlace::Remove(shared_ptr<WCompany> companyToremove)
{
	auto companies = economy->GetCompanies();
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
	auto companies = economy->GetCompanies();
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
	auto companies = economy->GetCompanies();
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

pair<shared_ptr<WProduct>, shared_ptr<WPriceDetailsPerUnit>> WMarketPlace::GetCheapestProduct(shared_ptr<WPurchasingWish> purchasingWish, list<shared_ptr<WProduct>>& marketStock)
{
	shared_ptr<WProductBaseInfo> productBaseInfo = purchasingWish->product;
	shared_ptr<WCompany> companyThatPurchase = purchasingWish->company;

	shared_ptr<WPriceDetailsPerUnit> priceDetails = make_shared<WPriceDetailsPerUnit>(.0f, .0f, .0f);

	shared_ptr<WProduct> cheapestProduct = nullptr;
	float cheapestPrice = 99999999999999999999999999999999999999.9999999999f;

	for (shared_ptr<WProduct> product : marketStock)
	{
		float transporationPricePerUnit = companyThatPurchase->GetDistanceFrom(product->company) * productBaseInfo->transportationCostPerKmPerUnit;

		float finalPrice = productBaseInfo->GetFloatingPricePerUnit() + transporationPricePerUnit + product->deltaCompanyPricePerUnit;

		if (finalPrice > cheapestPrice)
			continue;

		cheapestPrice = finalPrice;
		cheapestProduct = product;

		priceDetails = make_shared<WPriceDetailsPerUnit>(productBaseInfo->GetFloatingPricePerUnit(), transporationPricePerUnit, product->deltaCompanyPricePerUnit);
	}

	return pair<shared_ptr<WProduct>, shared_ptr<WPriceDetailsPerUnit>>(cheapestProduct, priceDetails);
}


void WMarketPlace::SelectCompanyDealsByProduct(shared_ptr<WProductBaseInfo> productBaseInfo, list<shared_ptr<WPurchasingWish>> purchasingWishes)
{
	float basePrice = productBaseInfo->GetFloatingPricePerUnit();
	float transportationCostPerKm = productBaseInfo->transportationCostPerKmPerUnit;

	list<shared_ptr<WProduct>> marketStock = marketStocks[productBaseInfo];
	
	random_device rd;
	mt19937 gen(rd());

	// Security while
	int failedAttempt = 3;

	while (purchasingWishes.size() > 0 && marketStock.size() == 0 && failedAttempt > 0)
	{
		uniform_int_distribution<>distrib(0, purchasingWishes.size() - 1);

		shared_ptr<WPurchasingWish> selectedPurchasingWish = *next(purchasingWishes.begin(), distrib(gen));

		pair<shared_ptr<WProduct>, shared_ptr<WPriceDetailsPerUnit>> cheapestProduct = GetCheapestProduct(selectedPurchasingWish, marketStock);

		shared_ptr<WProduct> productToPurchase = cheapestProduct.first;
		shared_ptr<WPriceDetailsPerUnit> priceDetails = cheapestProduct.second;

		if (productToPurchase == nullptr)
		{
			failedAttempt--;
			continue;
		}

		shared_ptr<WCompany> buyingCompany = selectedPurchasingWish->company;
		shared_ptr<WCompany> sellingCompany = productToPurchase->company;


		int nbAvailableProductInStock = productToPurchase->GetQuantity();
		int nbWishPurchaseProduct = selectedPurchasingWish->quantity;

		int nbProductPurchased = (nbWishPurchaseProduct > nbAvailableProductInStock) ? nbAvailableProductInStock : nbWishPurchaseProduct;

		float paidPriceBetweenCompanies = nbProductPurchased * (priceDetails->floatingPrice + priceDetails->deltaCompanyPrice);
		float transportationPrice = nbProductPurchased * priceDetails->transportationPrice;

		float totalPrice = paidPriceBetweenCompanies + transportationPrice;

		if (!buyingCompany->CanPay(totalPrice) || !buyingCompany->AttemptDeductionPayment(totalPrice))
		{
			failedAttempt--;
			continue;
		}

		economy->welfareState->PayTransportation(transportationPrice);
		
		bool succeedBuying = false;;
		shared_ptr<WProduct> possibleExtractedProduct = sellingCompany->AttemptBuyProduct(succeedBuying, productToPurchase, paidPriceBetweenCompanies, nbProductPurchased);

		if (!succeedBuying)
		{
			failedAttempt--;
			continue;
		}

		// TODO : here transaction registering

		if (possibleExtractedProduct != nullptr)
			buyingCompany->AddToRawStock(productBaseInfo, possibleExtractedProduct);
		else
			buyingCompany->AddToRawStock(productBaseInfo, productToPurchase);


		if (nbWishPurchaseProduct > nbAvailableProductInStock) // Means that keep WishPurchase
		{
			marketStock.remove(productToPurchase);
			marketStocks[productBaseInfo] = marketStock;
		}
		else if (nbWishPurchaseProduct == nbAvailableProductInStock) // remove both
		{
			purchasingWishes.remove(selectedPurchasingWish);
			marketStock.remove(productToPurchase);
			marketStocks[productBaseInfo] = marketStock;
		}
		else // nbWishPurchaseProduct < nbAvailableProductInStock   Means that keep product in stock
		{
			purchasingWishes.remove(selectedPurchasingWish);
		}
	}
}


void WMarketPlace::SelectCompanyDeals()
{
	// for each product
	for (pair<shared_ptr<WProductBaseInfo>, list<shared_ptr<WPurchasingWish>>> purchasingWishesByProduct : purchasingWishesByProducts)
	{
		shared_ptr<WProductBaseInfo> productBaseInfo = purchasingWishesByProduct.first;

		if (!marketStocks.count(productBaseInfo))
			continue;

		list<shared_ptr<WPurchasingWish>> purchasingWishes = purchasingWishesByProduct.second;
		SelectCompanyDealsByProduct(productBaseInfo, purchasingWishes);
	}
}