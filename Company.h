#pragma once
#include "Seller.h"
#include "Product.h"
#include "Factory.h"
#include "Builder.h"
#include <memory>

class EventSeller;
class EventBuyer;

/********************
*      Company      *
*********************/

class Company
{
protected:
	std::string name;
	std::vector<std::shared_ptr<Product>> stockInit;
	double coin_purse;

public:
	// Constructor and Destructor
	Company(std::string name);
	virtual ~Company();

	// Getters
	std::string getName();
	double getWallet();	
	std::vector<std::shared_ptr<Product>> getProducts();
	
	// Setters
	void setWallet(double coin_purse);
	
	// Method
	virtual void produceProduct() = 0;

	double payMoney(double price);
	void push_back_stock(std::shared_ptr<Product> prod);
	void printProduct();
	std::shared_ptr<Product> getProduct();
	

	friend std::ostream& operator<<(std::ostream& out, Company& c);
};




/***********************
*  RawMaterialCompany  *
************************/
class RawMaterialCompany : public Company
{
protected:
	std::shared_ptr<Factory> factory;

public:
	RawMaterialCompany(std::string name);
	~RawMaterialCompany();
	void produceProduct() override;
};




/*******************************
*  transformedMaterialCompany  *
********************************/
class transformedMaterialCompany : public Company
{
protected:
	std::shared_ptr<IBuilder> ptr_builder;
public:
	transformedMaterialCompany(std::string name);
	~transformedMaterialCompany();
};




class SellerCompany
{
protected:
	std::shared_ptr<EventSeller> es;
public:
	std::shared_ptr<EventSeller> getEventSeller()
	{
		return es;
	}
};


class BuyerCompany
{
protected:
	std::shared_ptr<EventBuyer> eb;
public:
	std::shared_ptr<EventBuyer> getEventBuyer()
	{
		return eb;
	}

	void buy();

};




/********************
*    TreeCompany    *
*********************/
class TreeCompany : public RawMaterialCompany, public SellerCompany
{
public:
	TreeCompany(std::string name);
	~TreeCompany();

};

class IronCompany : public RawMaterialCompany, public IronPublisher
{
public:
	IronCompany(std::string name) : RawMaterialCompany(name)
	{
		this->factory = std::shared_ptr<IronFactory>(new IronFactory());
	};
	~IronCompany() {};

};





/********************
*    WoodCompany    *
*********************/
class WoodCompany : public transformedMaterialCompany, public BuyerCompany
{
//private:
//	std::shared_ptr<EventBuyer> eb;
public:
	WoodCompany(std::string the_name);

	void subscribeToACompany(SellerCompany& sc);

	void produceProduct()
	{
		/*
		I try to figure out
		*/
	}
};
