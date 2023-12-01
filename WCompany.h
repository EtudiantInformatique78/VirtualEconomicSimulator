#pragma once
#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"
#include "WProductBaseInfo.h"
#include "WPurchasingWish.h"
#include "WProduct.h"
#include "WConstants.h"
#include "WelfareState.h"
#include <limits>
#include <random>

class WProduct;
class WelfareState;
class WPurchasingWish;

class WCompany
{
private:
	
	float capital;
	int nbMaxEmploye;
	int nbEmploye;
	float salaryEmploye;

	int researchLevel;
	
	map<shared_ptr<WCompany>, float> distanceFromCompany;

	float margin;
	float productionCost;
	float productivityEmploye;

	map<shared_ptr<WProductBaseInfo>, shared_ptr<list<shared_ptr<WProduct>>>> rawStock;
	list<shared_ptr<WProduct>> endProductStock;

	shared_ptr<pair<shared_ptr<WProduct>, float>> productInProduction;

public:

	const int id;
	const pair<int, int> position;
	const shared_ptr<WProductBaseInfo> productBaseInfo;

	WCompany(int _id, shared_ptr<WProductBaseInfo> _productBaseInfo, pair<int, int> _position);
	~WCompany();

	// Getters
	list<shared_ptr<WProduct>> GetEndProductStock();
	int GetNbOfPossibleProductToBuild();
	shared_ptr<WProductBaseInfo> GetProductBaseInfo();
	shared_ptr<list<shared_ptr<WPurchasingWish>>> GetPurchasingWishes(shared_ptr<WCompany> thisPtr);
	int GetQuantityRawProductInStock(shared_ptr<WProductBaseInfo> productBaseInfo);

	// Daily Operations
	void ExecuteDailyOperations(bool isFirstOfTheMonth, shared_ptr<WCompany> thisCompany, shared_ptr<WelfareState> welfareState);
	void PaySalaries(shared_ptr<WelfareState> welfareState);
	void TryRecrutEmploye();
	void ExecuteEmployeWork(shared_ptr<WCompany> thisCompany);
	bool TryStartNewProduction(shared_ptr<WCompany> thisCompany);
	int RetrieveRawProductsToBeginProduction(int wishQuantity);
	void TryUpgradeResearchLevel(shared_ptr<WelfareState> welfareState);


	// Stock
	bool RemoveFromRawStock(shared_ptr<WProductBaseInfo> productBaseInfo, int quantity);

	// Transactions Market
	void ReceiveMoney(float amount);

	float GetDistanceFrom(shared_ptr<WCompany> company);
	
	bool CanPay(float amount);
	bool AttemptDeductionPayment(float amount);

	shared_ptr<WProduct> AttemptBuyProduct(bool& succeedBuying, shared_ptr<WProduct> product, float totalPrice, int quantity);

	void AddToRawStock(shared_ptr<WProductBaseInfo> productBaseInfo, shared_ptr<WProduct> productToAdd);

};