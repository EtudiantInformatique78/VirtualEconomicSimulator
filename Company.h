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
	std::vector<std::shared_ptr<Product>> productMade;
public:
	transformedMaterialCompany(std::string name);
	~transformedMaterialCompany();

	std::vector<std::shared_ptr<Product>> getProductMade();

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






/*****************************
*        BuyerCompany        *
******************************/
class BuyerCompany
{
protected:
	std::shared_ptr<EventBuyer> eb;
public:
	// Getter
	std::shared_ptr<EventBuyer> getEventBuyer();
	
	// Method
	void subscribeToACompany(SellerCompany& sc);
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








/********************
*  IronCoreCompany  *
*********************/
class IronCoreCompany : public RawMaterialCompany, public SellerCompany
{
public:
	IronCoreCompany(std::string name);
	~IronCoreCompany();
};







/********************
*    WoodCompany    *
*********************/
class WoodCompany : public transformedMaterialCompany, public BuyerCompany
{
public:
	WoodCompany(std::string the_name);

	// Method
	void produceProduct() override;
	
};








/********************
*    IronCompany    *
*********************/
class IronCompany : public transformedMaterialCompany, public BuyerCompany
{
public:
	IronCompany(std::string the_name);

	// Method
	void produceProduct() override;

};