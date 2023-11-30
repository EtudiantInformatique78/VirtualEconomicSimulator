#include "WBaseInclusion.h"
#include "WProductBaseInfoBuilder.h"
#include "WProductBaseInfo.h"

WProductBaseInfo::WProductBaseInfo(int _id, WProductBaseInfoBuilder _builder) : id(_id), name(_builder.name), basePrice(_builder.basePrice), baseRate(_builder.baseRate), baseMargin(_builder.baseMargin), employeDayUnit(_builder.employeDayUnit), fabricationCost(_builder.fabricationCost), transportationCost(_builder.transportationCost)
{
	floatingPrice = _builder.basePrice;
}


WProductBaseInfo::~WProductBaseInfo()
{

}

void WProductBaseInfo::UpdateFloatingPrice(float rate)
{
	floatingPrice *= rate;
}

float WProductBaseInfo::GetFloatingPrice()
{
	return floatingPrice;
}