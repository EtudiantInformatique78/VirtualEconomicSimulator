#include "Company.h"
#include "EventExchange.h"
#include <memory>

/********************
*      Company      *
*********************/
Company::Company(std::string name)
{
	this->name = name;
	this->stockInit = std::vector<std::shared_ptr<Product>>();
	this->coin_purse = 100;
}

Company::~Company()
{
}

std::string Company::getName()
{
	return name;
}

double Company::getWallet()
{
	return coin_purse;
}

std::vector<std::shared_ptr<Product>> Company::getProducts()
{
	return stockInit;
}

void Company::setWallet(double coin_purse)
{
	this->coin_purse = coin_purse;
}

double Company::payMoney(double price)
{
	double diff = this->coin_purse - price;
	if (diff > 0)
	{
		return price;
	}
	else
	{
		return 0;
	}
}

void Company::push_back_stock(std::shared_ptr<Product> prod)
{
	this->stockInit.push_back(prod);
}

void Company::printProduct()
{
	std::vector<std::shared_ptr<Product>>::iterator it;
	for (it = this->stockInit.begin(); it != this->stockInit.end(); ++it)
	{
		std::cout << *(it->get()) << std::endl;
	}
}

std::shared_ptr<Product> Company::getProduct()
{
	if (stockInit.size() > 0)
	{
		std::shared_ptr<Product> ptr = stockInit.back();
		stockInit.pop_back();
		return ptr;
	}
	else
	{
		return nullptr;
	}
}

std::ostream& operator<<(std::ostream& out, Company& c)
{
	out << c.name;
	return out;
}







/***********************
*  RawMaterialCompany  *
************************/

RawMaterialCompany::RawMaterialCompany(std::string name) : Company(name) {}
RawMaterialCompany::~RawMaterialCompany(){}
void RawMaterialCompany::produceProduct()
{
	this->stockInit.push_back(this->factory->createProduct());
};






/*******************************
*  transformedMaterialCompany  *
********************************/
transformedMaterialCompany::transformedMaterialCompany(std::string name) : Company(name) {};
transformedMaterialCompany::~transformedMaterialCompany() {};








void BuyerCompany::buy()
{
	this->eb->buy();
}





/********************
*    TreeCompany    *
*********************/
TreeCompany::TreeCompany(std::string name) : RawMaterialCompany(name)
{
	this->factory = std::shared_ptr<TreeFactory>(new TreeFactory());
	//std::shared_ptr<TreeCompany> thisPointer(this, [](TreeCompany* ptr) {});
	//this->es = std::shared_ptr<EventSeller>(new EventSeller(thisPointer));

	auto sPointer = std::shared_ptr<TreeCompany>(this, [](auto) {});
	this->es = std::shared_ptr<EventSeller>(new EventSeller(sPointer));
}

TreeCompany::~TreeCompany(){}




/********************
*    WoodCompany    *
*********************/
WoodCompany::WoodCompany(std::string the_name) : transformedMaterialCompany(the_name)
{
	this->ptr_builder = std::shared_ptr<MakeWood>(new MakeWood());
	// I need to pass this into a smart pointer
	std::shared_ptr<WoodCompany> thisPointer(this, [](WoodCompany* ptr) {});
	this->eb = std::shared_ptr<EventBuyer>(new EventBuyer(thisPointer));
}

void WoodCompany::subscribeToACompany(SellerCompany& sc)
{
	this->eb->subscribe(sc.getEventSeller());
}
