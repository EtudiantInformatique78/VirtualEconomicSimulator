#pragma once

#include "WBaseInclusion.h"
#include "WCompany.h"
#include "WelfareState.h"
#include "WMarketPlace.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>


class WelfareState;
class WMarketPlace;

/// <summary>
/// "Main" of the economic system
/// </summary>
class WEconomy
{
private:
	list<shared_ptr<WCompany>> companies;
	list<shared_ptr<WProductBaseInfo>> productInfos;
	shared_ptr<tm> currentDate;

public:

	const shared_ptr<WelfareState> welfareState;
	const shared_ptr<WMarketPlace> marketPlace;

	static shared_ptr<WEconomy> InitializeEconomy();

	WEconomy(shared_ptr<WelfareState> _welfareState, shared_ptr<WMarketPlace> _marketPlace);
	~WEconomy();

	list<shared_ptr<WCompany>> GetCompanies();

	void IncrementDay();

	string GetExecutablePath();

	// LoadProductTree
	void LoadProductTree();
	void PopulateMapsOfProductsInfos(fstream& file, map<int, shared_ptr<WProductBaseInfoBuilder>>& productsBaseInfoBuilders, map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos);
	void AddCompositionToProducts(map<int, shared_ptr<WProductBaseInfoBuilder>>& productsBaseInfoBuilders, map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos);

	void AddValueToBuilder(shared_ptr<WProductBaseInfoBuilder> productBuilder, int id, string value);
	void GetCompositionNumbers(string compositionStr, int& productInfoId, int& quantity);

	void AddMapProductInfoInList(map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos);


	void CreateCompanies();
};