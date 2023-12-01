#include "WProductBaseInfo.h"

WProductBaseInfo::WProductBaseInfo(shared_ptr<WProductBaseInfoBuilder> _builder) 
	: id(_builder->id), name(_builder->name), baseMargin(_builder->baseMargin), 
	employeDayUnit(_builder->employeDayUnit), baseProductionCost(_builder->baseProductionCost), 
	transportationCostPerKmPerUnit(_builder->transportationCostPerkmPerUnit)
{
	floatingPricePerUnit = _builder->basePrice;
	productTreeState = _builder->productTreeState;
}


WProductBaseInfo::~WProductBaseInfo()
{

}

//void WProductBaseInfo::UpdateFloatingPrice(float rate)
//{
//	floatingPricePerUnit *= rate;
//}

//float WProductBaseInfo::GetFloatingPricePerUnit()
//{
//	return floatingPricePerUnit;
//}

void WProductBaseInfo::AddCompositionProduct(int quantity, shared_ptr<WProductBaseInfo> compositionProduct)
{
	composition[compositionProduct] = quantity;
}

void WProductBaseInfo::SetProductTreeStateAsBottom()
{
	productTreeState = ProductTreeState::FirstProductBottom;
}

ProductTreeState WProductBaseInfo::GetProductTreeState()
{
	return productTreeState;
}