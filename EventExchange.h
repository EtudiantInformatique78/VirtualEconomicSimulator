#pragma once
#include <vector>
#include <iostream>
#include "Product.h"
#include "TransformedMaterial.h"
#include "Company.h"

class EventCompany
{
protected:
	std::shared_ptr<Company> ptrCompany;

public:
	EventCompany(std::shared_ptr<Company> ptr_company)
	{
		this->ptrCompany = ptrCompany;
	}
	virtual ~EventCompany() {};
};

class EventBuyer;

class EventSeller : public EventCompany
{
	
public:
	EventSeller(std::shared_ptr<Company> ptr_company) : EventCompany(ptrCompany) {};
	~EventSeller() {};
	void sellProduct(std::shared_ptr<EventBuyer> eb);
};

class EventBuyer : public EventCompany
{
private:
	std::vector<std::shared_ptr<EventSeller>> vect;
	//std::vector<std::shared_ptr<Product>> vectProd;

public:
	// Constructor
	EventBuyer(std::shared_ptr<Company> ptr_company) : EventCompany(ptrCompany)
	{
		vect = std::vector<std::shared_ptr<EventSeller>>();
	}
	// Destructor
	~EventBuyer() {};

	// Getter


	// Setter


	// Method
		// Subscribe and Unsubsribe
		void subscribe(std::shared_ptr<EventSeller> s);
		void unsubscribe(std::shared_ptr<EventSeller> s);

	// print the products
	void printProduct();
	
	// some tiny "API" with company	
	std::vector<std::shared_ptr<Product>> getProduct();
	void push_back(std::shared_ptr<Product> p_ptr);


	void buy();
	double pay(double money)
	{
		return this->ptrCompany->payMoney(money);
	}

};

/*
#include <vector>
#include <iostream>

class Subscriber
{
public:
	virtual void update() = 0;
};

class Publisher
{
protected:
	std::vector<std::shared_ptr<Subscriber>> vect;
	//std::vector<Subscriber> vectSubscriber;

public:
	virtual void subscribe(std::shared_ptr<Subscriber> s) = 0;
	virtual void unsubscribe(std::shared_ptr<Subscriber> s) = 0;
	virtual void notifySubscriber() = 0;
};


*/