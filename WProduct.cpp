#include "WProduct.h"

WProduct::WProduct(float _deltaCompanyPricePerUnit, int _quantity, shared_ptr<WCompany> _company) : company(_company)
{
	quantity = _quantity;
	deltaCompanyPricePerUnit = _deltaCompanyPricePerUnit;
}

WProduct::~WProduct()
{

}

float WProduct::GetPrice(int quantity)
{
	return deltaCompanyPricePerUnit * quantity;
}

int WProduct::GetQuantity()
{
	return quantity;
}

shared_ptr<WProduct> WProduct::Extract(int quantityToExtract)
{
	if (quantityToExtract >= quantity)
		return nullptr;

	quantity = -quantityToExtract;

	shared_ptr<WProduct> extractedProduct = make_shared<WProduct>(deltaCompanyPricePerUnit, quantityToExtract, company);

	return extractedProduct;
}

void WProduct::SetNewDeltaCompanyPricePerUnitFromPurchase(float totalAmountPaid)
{
	deltaCompanyPricePerUnit = totalAmountPaid / quantity;
}