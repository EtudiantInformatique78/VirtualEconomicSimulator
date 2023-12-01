#include "WCompany.h"


WCompany::WCompany(int _id, shared_ptr<WProductBaseInfo> _productBaseInfo) 
	: id(_id), productBaseInfo(_productBaseInfo)
{
	capital = WConstants::COMPANY_START_CAPITAL;
	nbMaxEmploye = WConstants::NB_EMPLOYE_START;
	nbEmploye = WConstants::NB_EMPLOYE_START;
	salaryEmploye = WConstants::SALARY_EMPLOYE_START;
	researchLevel = 1;

	productivityEmploye = 1;

	productInProduction = nullptr;

	isFrozen = true;

	margin = _productBaseInfo->baseMargin;
	productionCost = _productBaseInfo->baseProductionCost;
}

WCompany::~WCompany()
{

}

#pragma region Getters

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
  	int unitWorkProduct = productBaseInfo->employeDayUnit;
	int nbOfPossibleProductToBuild = (nbEmploye * productivityEmploye) / unitWorkProduct;

	if (nbOfPossibleProductToBuild == 0 && nbEmploye > 0) // Force employes to work more than one day
		return 1;

	return nbOfPossibleProductToBuild;
}

shared_ptr<list<shared_ptr<WPurchasingWish>>> WCompany::GetPurchasingWishes(shared_ptr<WCompany> thisPtr)
{
	if (productBaseInfo->GetProductTreeState() == ProductTreeState::FirstProductBottom)
	{
		// No wishes because don't buy on the marketplace but extract directly from earth
		return nullptr;
	}

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

int WCompany::GetQuantityRawProductInStock(shared_ptr<WProductBaseInfo> productBaseInfo)
{
	if (!rawStock.count(productBaseInfo))
		return 0;

	shared_ptr<list<shared_ptr<WProduct>>> rawStockProduct = rawStock[productBaseInfo];

	int quantity = 0;

	for (shared_ptr<WProduct> product : *rawStockProduct)
	{
		quantity += product->GetQuantity();
	}

	return quantity;
}

bool WCompany::RemoveFromRawStock(shared_ptr<WProductBaseInfo> productBaseInfo, int quantityToRemove, float& outTotalPrice)
{
	if (!rawStock.count(productBaseInfo))
		return false;

	shared_ptr<list<shared_ptr<WProduct>>> rawStockProduct = rawStock[productBaseInfo];
	list<shared_ptr<WProduct>> productToRemoveFromStock;

	bool stockIsEmpty = false;

	// Remove product until enough quantity has been removed
	for (shared_ptr<WProduct> product : *rawStockProduct)
	{
		int quantityInProduct = product->GetQuantity();

		if (quantityToRemove < quantityInProduct)
		{
			shared_ptr<WProduct> extractedProduct = product->Extract(quantityToRemove);
			quantityToRemove = 0;

			outTotalPrice += product->deltaCompanyPricePerUnit * quantityToRemove;

			// TODO : register extraction from raw stock
			break;
		}
		
		if (quantityToRemove == quantityInProduct)
		{
			productToRemoveFromStock.push_back(product);

			outTotalPrice += product->deltaCompanyPricePerUnit * quantityToRemove;
			quantityToRemove = 0;
			break;
		}

		// quantityToRemove > quantityInProduct
		outTotalPrice += product->deltaCompanyPricePerUnit * quantityInProduct;
		quantityToRemove -= quantityInProduct;
		productToRemoveFromStock.push_back(product);
	}

	if (quantityToRemove != 0) // Couldn't remove enough product
		return false;

	// Remove the removedProducts from the rawStock
	for (shared_ptr<WProduct> productToRemove : productToRemoveFromStock)
	{
		rawStockProduct->remove(productToRemove);
	}

	return true;
}

#pragma endregion


#pragma region DailyOperations
void WCompany::ExecuteDailyOperations(bool isFirstOfTheMonth, shared_ptr<WCompany> thisCompany, shared_ptr<WelfareState> welfareState)
{
	if (isFirstOfTheMonth && !isFrozen)
	{
		PaySalaries(welfareState);
		TryRecrutEmploye();
	}

	ExecuteEmployeWork(thisCompany);

	TrySellDirectlyToWelfareState(welfareState);	

	TryUpgradeResearchLevel(welfareState);
}

void WCompany::PaySalaries(shared_ptr<WelfareState> welfareState)
{
	float salariesCost = nbEmploye * salaryEmploye;

	capital -= salariesCost;

	if (capital < 0.0f)
	{
		float realPayment = capital * -1.0f;
		capital = 0.0f;
		welfareState->PaySalaries(realPayment);

		int nbOfUnpaidSalary = (salariesCost - realPayment) / salaryEmploye;
		random_device rd;
		mt19937 gen(rd());
		bernoulli_distribution dist(0.5);
		

		for (int i = 0; i < nbOfUnpaidSalary; i++)
		{
			if (dist(gen)) // 1/2 chance that the employe leave
				nbEmploye--;
		}

		return;
	}

	welfareState->PaySalaries(salariesCost);
}

void WCompany::TryRecrutEmploye()
{
	if (nbEmploye == nbMaxEmploye)
		return;

	// Can hire only if the total payroll is less than 10% of the capital

	float totalSalaries = nbEmploye * salaryEmploye;
	bool wantToHire = (totalSalaries / capital) < .1f;

	while (wantToHire)
	{
		if (nbEmploye + 1 > nbMaxEmploye)
		{
			wantToHire = false;
			continue;
		}

		// Hire employe
		nbEmploye++;

		totalSalaries = nbEmploye * salaryEmploye;
		wantToHire = (totalSalaries / capital) < .1f;
	}
}

void WCompany::ExecuteEmployeWork(shared_ptr<WCompany> thisCompany)
{
	float productEmployeDayUnit = productBaseInfo->employeDayUnit;
	float remainingEmployeWorkForceOfTheday = nbEmploye * productivityEmploye; 

	if (productInProduction == nullptr)
		TryStartNewProduction(thisCompany);

	if (productInProduction == nullptr) // Couldn't work
		return;

	float remainingWorkForceToFinishProduct = productInProduction->second;

	remainingWorkForceToFinishProduct -= remainingEmployeWorkForceOfTheday;

	int totalQuantity = 0;

	while (remainingWorkForceToFinishProduct <= 0)
	{
		// Product Finished
		shared_ptr<WProduct> finishedProduct = productInProduction->first;

		totalQuantity += finishedProduct->GetQuantity();

		endProductStock.push_back(finishedProduct);
		productInProduction = nullptr;

		if (!TryStartNewProduction(thisCompany))
		{
			if (totalQuantity > 0)
				cout << "		Company n " << thisCompany->id << " has just produced " << totalQuantity << "x " << thisCompany->GetProductBaseInfo()->name << endl;
			return;
		}


		// Surplus of the remainingWorkForceToFinishProduct represent the remaining amount of the remainingEmployeWorkForceOfTheday
		remainingEmployeWorkForceOfTheday = remainingWorkForceToFinishProduct * -1.0f;

		remainingWorkForceToFinishProduct = productInProduction->second;
		remainingWorkForceToFinishProduct -= remainingEmployeWorkForceOfTheday;
	}

	if(totalQuantity > 0)
		cout << "		Company n " << thisCompany->id << " has just produced " << totalQuantity << "x " << thisCompany->GetProductBaseInfo()->name << endl;

	productInProduction->second = remainingWorkForceToFinishProduct;
	return;
}


bool WCompany::TryStartNewProduction(shared_ptr<WCompany> thisCompany)
{
	float productEmployeDayUnit = productBaseInfo->employeDayUnit;
	float employeWorkForceOfTheday = nbEmploye * productivityEmploye;

	float quantityF = productEmployeDayUnit / employeWorkForceOfTheday;
	int wishQuantity = (quantityF < 1.0f) ? 1 : quantityF;

	int quantity;
	bool isFirstBottomproduct = (productBaseInfo->GetProductTreeState() == ProductTreeState::FirstProductBottom);

	float totalPriceRawProduct = 0.0f;

	if (isFirstBottomproduct)
		quantity = wishQuantity; // RawStock are useless because bottom company don't buy products, they extract from earth
	else
		quantity = RetrieveRawProductsToBeginProduction(wishQuantity, totalPriceRawProduct);

	if (quantity == 0)
		return false;

	if (isFrozen)
	{
		isFrozen = false;
		cout << "        Company n " << id << " just started its first production !" << endl;
	}

	float daySpentOnProduct = productEmployeDayUnit / productivityEmploye;
	float salaryCostPerDay = salaryEmploye / 31.0f; // 31 is number of day in a month
	float salaryCostPerProduct = daySpentOnProduct * salaryCostPerDay;

	float deltaCompanyPricePerUnit;

	if (isFirstBottomproduct)
		deltaCompanyPricePerUnit = (salaryCostPerProduct * quantity * productionCost) * (1 + margin) / quantity; // production cost is multiplied to increase the price per unit compared to other company that buy raw products
	else
		deltaCompanyPricePerUnit = (salaryCostPerProduct * quantity + totalPriceRawProduct + productionCost) * (1 + margin) / quantity;

	shared_ptr<WProduct> product = make_shared<WProduct>(deltaCompanyPricePerUnit, quantity, thisCompany);
	productInProduction = make_shared<pair<shared_ptr<WProduct>, float>>(product, productBaseInfo->employeDayUnit * quantity);
	
	return true;
}

int WCompany::RetrieveRawProductsToBeginProduction(int wishQuantity, float& outTotalPrice)
{
	int minimumAvailableRessourceProduct = INT_MAX;

	map<shared_ptr<WProductBaseInfo>, int> compositionProductToProduce = productBaseInfo->composition;


	// Get the maximum amount of product that can be produced
	for (pair<shared_ptr<WProductBaseInfo>, int> material : compositionProductToProduce)
	{
		shared_ptr<WProductBaseInfo> productMaterial = material.first;
		int requiredQuantityForOne = material.second;

		int nbAvailableProductMaterial = GetQuantityRawProductInStock(productMaterial);

		int maxAvailableQuantityForProductMaterial = nbAvailableProductMaterial / requiredQuantityForOne;

		if (maxAvailableQuantityForProductMaterial < minimumAvailableRessourceProduct)
			minimumAvailableRessourceProduct = maxAvailableQuantityForProductMaterial;
	}

	int quantityToRetrieve = (minimumAvailableRessourceProduct > wishQuantity) ? wishQuantity : minimumAvailableRessourceProduct;
	
	if (quantityToRetrieve == 0)
		return 0;

	outTotalPrice = 0.0f;

	// Remove the raw products from stock
	for (pair<shared_ptr<WProductBaseInfo>, int> material : compositionProductToProduce)
	{
		shared_ptr<WProductBaseInfo> productMaterial = material.first;
		int requiredQuantityForOne = material.second;

		RemoveFromRawStock(productMaterial, requiredQuantityForOne * quantityToRetrieve, outTotalPrice);
	}

	return quantityToRetrieve;
}


void WCompany::TryUpgradeResearchLevel(shared_ptr<WelfareState> welfareState)
{
	float upgradeCost = WConstants::BASE_UPGRADE_COST_RESEARCH * WConstants::UPGRADE_RATIO_COST_RESEARCH * researchLevel;

	float ratio = upgradeCost / capital;

	if (ratio > WConstants::MINIMUM_PERCENT_TO_UPGRADE_RESEARCH)
		return;

	// Upgrade Research
	capital -= upgradeCost;
	welfareState->PayResearch(upgradeCost);

	researchLevel++;

	cout << "        Company n " << id << " upgraded to the Research Level " << researchLevel << endl;

	nbMaxEmploye += WConstants::EMPLOYE_AMOUNT_UPGRADE_RESEARCH;
	productivityEmploye += WConstants::EMPLOYE_PRODUCTIVITY_UPGRADE_RESEARCH;

	margin *= WConstants::MARGIN_RATIO_RESEARCH;

	float halfBaseMargin = productBaseInfo->baseMargin * .5f;

	if (margin < halfBaseMargin)
		margin = halfBaseMargin;

	productionCost *= WConstants::FABRICATION_COST_RATIO_RESEARCH;

	float halfProductionCost = productBaseInfo->baseProductionCost * .5f;

	if (productionCost < halfProductionCost)
		productionCost = halfProductionCost;

}


#pragma endregion


#pragma region TransactionMarket

void WCompany::ReceiveMoney(float amount)
{
	capital += amount;
}

float WCompany::GetDistanceFrom(shared_ptr<WCompany> company)
{
	if (distanceFromCompany.count(company))
		return distanceFromCompany[company];

	// TODO : Calculate the distance and save it in distanceFromCompany

	return 5.0f;
}

bool WCompany::CanPay(float amount)
{
	return amount <= capital;
}

bool WCompany::AttemptDeductionPayment(float amount)
{
	if (amount > capital)
		return false;

	capital -= amount;

	return true;
}


shared_ptr<WProduct> WCompany::AttemptBuyProduct(bool& succeedBuying, shared_ptr<WProduct> product, float totalPrice, int quantity)
{
	bool inStock = false;
	succeedBuying = false;

	for (shared_ptr<WProduct> productInList : endProductStock)
	{
		if (productInList != product)
			continue;

		inStock = true;
		break;
	}

	if (!inStock)
		return nullptr;

	succeedBuying = true;

	capital += totalPrice;

	if (product->GetQuantity() >= quantity)
	{
		endProductStock.remove(product);
		return nullptr;
	}

	// quantity < stock
	shared_ptr<WProduct> extractedProduct = product->Extract(quantity);

	return extractedProduct;
}
#pragma endregion


void WCompany::AddToRawStock(shared_ptr<WProductBaseInfo> productBaseInfo, shared_ptr<WProduct> productToAdd)
{
	if (!rawStock.count(productBaseInfo))
	{
		shared_ptr<list<shared_ptr<WProduct>>> products = make_shared<list<shared_ptr<WProduct>>>();
		products->push_back(productToAdd);
		rawStock[productBaseInfo] = products;
		return;
	}

	rawStock[productBaseInfo]->push_back(productToAdd);
}

void WCompany::TrySellDirectlyToWelfareState(shared_ptr<WelfareState> welfareState)
{
	if (productBaseInfo->GetProductTreeState() != ProductTreeState::EndProductTop)
		return;

	int totalQuantity = 0;
	int totalTotalPrice = 0;
	string productName = "";

	for (shared_ptr<WProduct> productToSell : endProductStock)
	{
		int quantity = productToSell->GetQuantity();
		totalQuantity += quantity;

		float totalPrice = productToSell->GetPrice(quantity);
		totalTotalPrice += totalPrice;

		capital += welfareState->SellEndProduct(totalPrice);
	}

	if (totalQuantity == 0)
		return;

	cout << "        WelfareState has just bought  " << totalQuantity << "x " << productBaseInfo->name << "for " << totalTotalPrice << "€." << endl;

	endProductStock.clear();
}