#pragma once
#include "Seller.h"
#include "Product.h"
#include "Factory.h"
#include "Builder.h"

class Company
{
protected:
	std::string name;
	std::vector<std::shared_ptr<Product>> stockInit;
	double coin_purse;

public:
	Company(std::string name)
	{
		this->name = name;
		this->stockInit = std::vector<std::shared_ptr<Product>>();
	}
	virtual ~Company() {}

	// Getters
	std::string getName()
	{
		return name;
	}

	double getWallet()
	{
		return coin_purse;
	}

	std::vector<std::shared_ptr<Product>> getProducts()
	{
		return stockInit;
	}

	// Setters
	void setWallet(double coin_purse)
	{
		this->coin_purse = coin_purse;
	}

	// Method
	double payMoney(double price)
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

	void push_back_stock(std::shared_ptr<Product> prod)
	{
		this->stockInit.push_back(prod);
	}

	virtual void produceProduct() = 0;
	
	void printProduct()
	{
		std::vector<std::shared_ptr<Product>>::iterator it;
		for (it = this->stockInit.begin(); it != this->stockInit.end(); ++it)
		{
			std::cout << *(it->get()) << std::endl;
		}
	};
	friend std::ostream& operator<<(std::ostream& out, Company& c)
	{
		out << c.name;
		return out;
	}

	std::shared_ptr<Product> getProduct()
	{
		if(stockInit.size()>0)
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

};

class RawMaterialCompany : public Company
{
protected:
	std::shared_ptr<Factory> factory;

public:
	RawMaterialCompany(std::string name) : Company(name) {};
	~RawMaterialCompany() {};
	void produceProduct() override
	{
		this->stockInit.push_back(this->factory->createProduct());
	};
};

class transformedMaterialCompany : public Company
{
protected:
	std::shared_ptr<IBuilder> ptr_builder;
public:
	transformedMaterialCompany(std::string name) : Company(name){}
	~transformedMaterialCompany(){}
	
};

class TreeCompany : public RawMaterialCompany, public TreePublisher
{
public:
	TreeCompany(std::string name) : RawMaterialCompany(name)
	{
		this->factory = std::shared_ptr<TreeFactory>(new TreeFactory());
	};
	~TreeCompany() {};
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


class WoodCompany : public transformedMaterialCompany, public TreeSubscriber
{
public:
	WoodCompany(std::string the_name, std::shared_ptr<TreePublisher> tp) : transformedMaterialCompany(the_name)
	{
		this->ptr_builder = std::shared_ptr<MakeWood>(new MakeWood());
		// I need to pass this into a smart pointer
		std::shared_ptr<WoodCompany> thisPointer(this, [](WoodCompany* ptr) {});
		tp->subscribe(std::dynamic_pointer_cast<TreeSubscriber>(thisPointer));
	}

	void produceProduct()
	{
		/*
		I try to figure out
		*/
	}
};
