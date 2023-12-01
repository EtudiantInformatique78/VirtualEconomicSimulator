#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"
#include "WProductBaseInfo.h"
#include "WProduct.h"
#include "WCompany.h"
#include "WMarketPlace.h"


#include <iostream>



int main()
{
    shared_ptr<WEconomy> economy = WEconomy::InitializeEconomy();
    economy->LoadProductTree();
    economy->CreateCompanies();

    std::cout << "cc" << std::endl;
}