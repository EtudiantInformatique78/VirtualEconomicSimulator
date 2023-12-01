#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"
#include "WProductBaseInfo.h"
#include "WProduct.h"
#include "WCompany.h"
#include "WMarketPlace.h"
#include <conio.h>

#include <iostream>



int main()
{
    shared_ptr<WEconomy> economy = WEconomy::InitializeEconomy();
    economy->LoadProductTree();
    economy->CreateCompanies();


    bool wantQuit = false;

    while (!wantQuit)
    {
        char ch = _getch();

        if (ch == 'q')
            wantQuit = true;

        economy->IncrementDay();
    }


   
}