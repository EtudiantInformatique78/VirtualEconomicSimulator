#include "BaseInclusion.h"
#include "ProductBaseInfoBuilder.h"
#include "ProductBaseInfo.h"

ProductBaseInfo::ProductBaseInfo(int _id, ProductBaseInfoBuilder _builder) : id(_id), name(_builder.name), basePrice(_builder.basePrice), baseRate(_builder.baseRate), baseMargin(_builder.baseMargin), employeDayUnit(_builder.employeDayUnit), fabricationCost(_builder.fabricationCost), transportationCost(_builder.transportationCost)
{

}


ProductBaseInfo::~ProductBaseInfo()
{

}