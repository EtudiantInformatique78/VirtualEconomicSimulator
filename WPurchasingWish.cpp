#include "WBaseInclusion.h"
#include "WProductBaseInfo.h"
#include "WCompany.h"
#include "WPurchasingWish.h"



WPurchasingWish::WPurchasingWish(shared_ptr<WCompany> _company, shared_ptr<WProductBaseInfo> _product, int _quantity) : company(_company), product(_product), quantity(_quantity)
{

}

WPurchasingWish::~WPurchasingWish()
{

}