// ProductionSimulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Seller.h"


int main()
{
    std::cout << "Hello World!\n";

    
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
