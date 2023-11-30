#pragma once

class WProduct;

class WCompany
{
private:
	
	float capital;
	int nbEmploye;
	int nbAvailableEmploye;
	float salaryEmploye;

	int rAndDLevel;
	pair<int, int> position;
	map<shared_ptr<WCompany>, float> distanceFromCompany;

	float margin;

	map<shared_ptr<WProductBaseInfo>, list<shared_ptr<WProduct>>> rawStock;
	list<shared_ptr<WProduct>> endProductStock;

	shared_ptr<WProductBaseInfo> productBaseInfo;


public:
	WCompany(shared_ptr<WProductBaseInfo> _productBaseInfo, pair<int, int> _position);
	~WCompany();

	// Getters
	list<shared_ptr<WProduct>> GetEndProductStock();
	int GetNbOfPossibleProductToBuild();
	shared_ptr<WProductBaseInfo> GetProductBaseInfo();
	shared_ptr<list<shared_ptr<WPurchasingWish>>> GetPurchasingWishes(shared_ptr<WCompany> thisPtr);



	void ApplyWorkDay();
	void ReceiveMoney(float amount);
};