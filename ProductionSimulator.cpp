// ProductionSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Seller.h"
#include "Company.h"
#include "EventExchange.h"


int main()
{
    std::cout << "Hello World!\n";

    std::shared_ptr<Company> c_ptr = std::shared_ptr<TreeCompany>(new TreeCompany("Montgomery's trees"));
    std::shared_ptr<Company> w_ptr = std::shared_ptr<WoodCompany>(new WoodCompany("Barret's trees"));

    c_ptr->produceProduct();

    std::shared_ptr<TreeCompany> dc_ptr = std::dynamic_pointer_cast<TreeCompany>(c_ptr);
    std::shared_ptr<WoodCompany> dw_ptr = std::dynamic_pointer_cast<WoodCompany>(w_ptr);

    dw_ptr->subscribeToACompany(*dc_ptr.get());
    dw_ptr->buy();
    dw_ptr->printProduct();
    std::cout << dw_ptr->getWallet() << std::endl;


    /*
    std::shared_ptr<EventSeller> es_ptr = std::shared_ptr<EventSeller>(new EventSeller());
    std::shared_ptr<EventBuyer> eb_ptr = std::shared_ptr<EventBuyer>(new EventBuyer());

    eb_ptr->subscribe(es_ptr);

    eb_ptr->buy();
    eb_ptr->buy();

    eb_ptr->printProduct();

    std::cout << "------------------------------------------" << std::endl;
    eb_ptr->buy();

    eb_ptr->printProduct();
    */
    

    /*
    
    std::string tree_company_name = std::string("Montgomery's trees");
    std::shared_ptr<Company> c_ptr = std::shared_ptr<TreeCompany>(new TreeCompany(tree_company_name));
    c_ptr->produceProduct();
    c_ptr->produceProduct();
    c_ptr->produceProduct();

    std::cout << *c_ptr.get() << std::endl;

    c_ptr->printProduct();

    std::shared_ptr<TreePublisher> tp_ptr = std::static_pointer_cast<TreePublisher>(
        std::dynamic_pointer_cast<TreeCompany>(c_ptr)
    );
    std::string wood_company_name = std::string("Barret's trees");
    std::shared_ptr<Company> w_ptr = std::shared_ptr<WoodCompany>(new WoodCompany(wood_company_name, tp_ptr ));

    tp_ptr->notifySubscriber();


    */

    

    /*
    c_ptr = std::shared_ptr<IronCompany>(new IronCompany("Montgomery's iron ores !"));
    c_ptr.get()->produceProduct();
    c_ptr.get()->produceProduct();

    std::cout << *c_ptr.get() << std::endl;
    c_ptr.get()->printProduct();
    */
    



    /*
    std::shared_ptr<Subscriber> ts1 = std::shared_ptr<TreeSubscriber>(new TreeSubscriber());
    std::shared_ptr<Subscriber> ts2 = std::shared_ptr<TreeSubscriber>(new TreeSubscriber());
    std::shared_ptr<Subscriber> ts3 = std::shared_ptr<TreeSubscriber>(new TreeSubscriber());
    std::shared_ptr<Subscriber> is1 = std::shared_ptr<IronSubscriber>(new IronSubscriber());

    std::shared_ptr<Publisher> tp_ptr = std::shared_ptr<TreePublisher>(new TreePublisher());
    std::shared_ptr<Publisher> ip_ptr = std::shared_ptr<IronPublisher>(new IronPublisher());


    tp_ptr->subscribe(ts1);
    tp_ptr->subscribe(ts2);
    tp_ptr->subscribe(ts3);
    ip_ptr->subscribe(is1);

    tp_ptr->notifySubscriber();

    ip_ptr->notifySubscriber();

    tp_ptr->unsubscribe(ts2);
    tp_ptr->notifySubscriber();
    */
    
    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
