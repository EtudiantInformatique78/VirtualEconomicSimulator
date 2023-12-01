#include "WEconomy.h"


shared_ptr<WEconomy> WEconomy::InitializeEconomy()
{
	shared_ptr<WelfareState> welfareState = make_shared<WelfareState>();
	shared_ptr<WMarketPlace> marketPlace = make_shared<WMarketPlace>();

	shared_ptr<WEconomy> economy = make_shared<WEconomy>(welfareState, marketPlace);

	welfareState->SetEconomy(economy);
	marketPlace->SetEconomy(economy);

	return economy;
}

WEconomy::WEconomy(shared_ptr<WelfareState> _welfareState, shared_ptr<WMarketPlace> _marketPlace)
	: welfareState(_welfareState), marketPlace(_marketPlace)
{
	time_t currentTime;


	time(&currentTime);

	currentDate = make_shared<tm>();
	localtime_s(currentDate.get(), &currentTime);

	currentDate->tm_hour = 0;
	currentDate->tm_min = 0;
	currentDate->tm_sec = 0;
}

WEconomy::~WEconomy()
{

}

list<shared_ptr<WCompany>> WEconomy::GetCompanies()
{
	return companies;
}

void WEconomy::IncrementDay()
{
	currentDate->tm_mday++;
	mktime(currentDate.get());
	system("cls");
	cout << "New Day : " << currentDate->tm_mday << "/" << currentDate->tm_mon + 1 << "/" << currentDate->tm_year + 1900 << endl;

	bool isFirstOfTheMonth = (currentDate->tm_mday == 1);

	for (shared_ptr<WCompany> company : companies)
	{
		company->ExecuteDailyOperations(isFirstOfTheMonth, company, welfareState);
	}

	marketPlace->ExecuteDailyOperations();

	if(isFirstOfTheMonth)
		welfareState->DistributeMoney();
}


void WEconomy::AddValueToBuilder(shared_ptr<WProductBaseInfoBuilder> productBuilder, int id, string value)
{
	switch (id)
	{
		case 0:
			productBuilder->id = stoi(value);
			break;
		case 1:
			productBuilder->name = value;
			break;
		case 2:
			if (value == "true")
				productBuilder->productTreeState = ProductTreeState::EndProductTop;
			break;
		case 3:
			productBuilder->baseProductionCost = stof(value);
			break;
		case 4:
			productBuilder->baseMargin = stof(value);
			break;
		case 5:
			productBuilder->employeDayUnit = stoi(value);
			break;
		case 6:
			productBuilder->transportationCostPerkmPerUnit = stof(value);
			break;
		case 7:
			if(!value.empty())
				productBuilder->composition = value;
			break;
	}
}

void WEconomy::PopulateMapsOfProductsInfos(fstream& file, map<int, shared_ptr<WProductBaseInfoBuilder>>& productsBaseInfoBuilders, map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos)
{
	string line;
	bool isFirst = true;

	while (getline(file, line))
	{
		if (isFirst)
		{
			isFirst = false; // First line is a comment
			continue;
		}

		stringstream ss(line);
		vector<string> result;

		while (ss.good())
		{
			string substr;
			getline(ss, substr, ';');
			result.push_back(substr);
		}

		int size = result.size();

		shared_ptr<WProductBaseInfoBuilder> productBuilder = make_shared<WProductBaseInfoBuilder>();

		for (int i = 0; i < size; i++)
		{
			string value = result[i];

			AddValueToBuilder(productBuilder, i, value);
		}

		shared_ptr<WProductBaseInfo> productBaseInfo = make_shared<WProductBaseInfo>(productBuilder);

		productsBaseInfoBuilders[productBuilder->id] = productBuilder;
		productsBaseInfos[productBuilder->id] = productBaseInfo;
	}
}


void WEconomy::GetCompositionNumbers(string compositionStr, int& productInfoId, int& quantity)
{
	stringstream compositionSs(compositionStr);
	string tkn;

	getline(compositionSs, tkn, '-');
	productInfoId = stoi(tkn);
	std::getline(compositionSs, tkn, '-');
	quantity = stoi(tkn);
}

void WEconomy::AddCompositionToProducts(map<int, shared_ptr<WProductBaseInfoBuilder>>& productsBaseInfoBuilders, map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos)
{
	// Iterate with this method in case of Ids are discontinued
	for (auto element = productsBaseInfoBuilders.begin(); element != productsBaseInfoBuilders.end(); element++)
	{
		bool addedAComposition = false;
		int id = element->first;
		shared_ptr<WProductBaseInfoBuilder> productBaseInfoBuilder = element->second;
		shared_ptr<WProductBaseInfo> productBaseInfo = productsBaseInfos[id];

		stringstream compositionSs(productBaseInfoBuilder->composition);
		vector<string> compositions;

		while (compositionSs.good())
		{
			string substr;
			getline(compositionSs, substr, '/');
			compositions.push_back(substr);
		}


		for (string composition : compositions)
		{
			if (composition.size() == 0)
				continue;

			if (composition.find('-') == string::npos)
				continue;

			int outId, outQuantity;
			GetCompositionNumbers(composition, outId, outQuantity);

			if (!productsBaseInfos.count(outId))
				continue;

			shared_ptr<WProductBaseInfo> compositionProduct = productsBaseInfos[outId];

			productBaseInfo->AddCompositionProduct(outQuantity, compositionProduct);

			addedAComposition = true;
		}

		if (!addedAComposition)
			productBaseInfo->SetProductTreeStateAsBottom();
	}
}

void WEconomy::AddMapProductInfoInList(map<int, shared_ptr<WProductBaseInfo>>& productsBaseInfos)
{
	for (auto element = productsBaseInfos.begin(); element != productsBaseInfos.end(); element++)
	{
		shared_ptr<WProductBaseInfo> productInfo = element->second;
		productInfos.push_back(productInfo);
	}
}

void WEconomy::LoadProductTree()
{
	string fileName = GetExecutablePath() + "productTree.csv";

	fstream file(fileName, ios::in);

	if (!file.is_open())
	{
		cout << "Could not open the file : " << fileName << endl;
		return;
	}

	map<int, shared_ptr<WProductBaseInfoBuilder>> productsBaseInfoBuilders;
	map<int, shared_ptr<WProductBaseInfo>> productsBaseInfos;

	PopulateMapsOfProductsInfos(file, productsBaseInfoBuilders, productsBaseInfos);

	file.close();

	AddCompositionToProducts(productsBaseInfoBuilders, productsBaseInfos);
	AddMapProductInfoInList(productsBaseInfos);
}

string WEconomy::GetExecutablePath()
{
	vector<char> buf(1024, 0);
	vector<char>::size_type size = buf.size();

	GetModuleFileNameA(nullptr, &buf[0], 1024);
	string path = &buf[0];

	size_t pos = path.find_last_of('\\');

	return path.substr(0, pos) + '\\';
}

void WEconomy::CreateCompanies()
{
	int nbCompanyPerProduct = WConstants::NB_COMPANY_PER_PRODUCT;
	int nbCompany = 0;

	pair<int, int> position(0, 0);

	for (shared_ptr<WProductBaseInfo> productInfo : productInfos)
	{
		for (int i = 0; i < nbCompanyPerProduct; i++)
		{
			shared_ptr<WCompany> company = make_shared<WCompany>(nbCompany, productInfo);
			nbCompany++;
			companies.push_back(company);
		}
	}
}