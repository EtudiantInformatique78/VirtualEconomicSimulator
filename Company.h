#pragma once


class Company
{
private:
	
	int nbEmploye;
	int nbAvailableEmploye;
	float salaryEmploye;

	int rAndDLevel;
	pair<int, int> position;
	map<Company, float> distanceFromCompany;

	float margin;

	vector<WProduct> rawStocks;
	vector<WProduct> finishedStocks;

	shared_ptr<ProductBaseInfo> productBaseInfo;


public:
	Company(shared_ptr<ProductBaseInfo> _productBaseInfo, pair<int, int> _position);
	~Company();

	void ApplyWorkDay();

};