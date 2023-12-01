#include "WProductBaseInfoBuilder.h"


WProductBaseInfoBuilder::WProductBaseInfoBuilder()
{
	id = -1;
	name = "";
	basePrice = -1;
	baseMargin = -1;
	employeDayUnit = -1;
	baseProductionCost = -1;
	transportationCostPerkmPerUnit = -1;

	productTreeState = ProductTreeState::InMiddle;

	composition = "";
}



WProductBaseInfoBuilder::~WProductBaseInfoBuilder()
{

}