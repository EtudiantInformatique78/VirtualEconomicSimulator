#include "EventExchange.h"

// EventSeller
void EventSeller::sellProduct(std::shared_ptr<EventBuyer> eb)
{
	// ask buyer for money
	std::shared_ptr<Product> ptr_product = this->ptrCompany.getProduct();
	if(ptr_product != nullptr)
	{
		double starting_price = ptr_product->getStartingPrice();
		std::cout << "I am selling : " << ptr_product->getName() << std::endl;
		double money = eb->pay(starting_price);

		// If it has money, push element to vect
		if (money == starting_price)
		{
			double coin_purse = this->ptrCompany.getWallet();
			coin_purse += money;
			this->ptrCompany.setWallet(coin_purse);


			eb->push_back(ptr_product);
		}
		// else do nothing
		else
		{
			std::cout << "You don't have enough money bro" << std::endl;
		}
	}
	else
	{
		std::cout << "I don't have product to sell" << std::endl;
	}
}


// Event Buyer

void EventBuyer::subscribe(std::shared_ptr<EventSeller> s)
{
	vect.push_back(s);
}

void EventBuyer::unsubscribe(std::shared_ptr<EventSeller> s)
{
	//std::string err = std::string("void EventBuyer::unsubscribe(std::shared_ptr<EventSeller> s) is not implemented");
	//throw err;
	std::vector<std::shared_ptr<EventSeller>>::iterator position = std::find(vect.begin(), vect.end(), s);
	if (position != vect.end())
	{
		vect.erase(position);
	}

}

void EventBuyer::printProduct()
{
	std::vector<std::shared_ptr<Product>>::iterator it;
	std::vector<std::shared_ptr<Product>> vectProd = this->ptrCompany.getProducts();
	for (it = vectProd.begin(); it != vectProd.end(); ++it)
	{
		std::cout << *((*it).get()) << std::endl;
	}
}


std::vector<std::shared_ptr<Product>> EventBuyer::getProduct()
{
	return this->ptrCompany.getProducts();
}



void EventBuyer::push_back(std::shared_ptr<Product> p_ptr)
{	
	this->ptrCompany.push_back_stock(p_ptr);
}

void EventBuyer::buy()
{
	std::shared_ptr<EventBuyer> thisPointer(this, [](EventBuyer* ptr) {});

	std::vector<std::shared_ptr<EventSeller>>::iterator it;
	for (it = vect.begin(); it != vect.end(); ++it)
	{
		it->get()->sellProduct(thisPointer);
	}
}
