#pragma once
#include "WBaseInclusion.h"
#include "WProduct.h"

class WorkingUnit
{
private:
	int nbWorkingEmploye;


public:
	WorkingUnit(int nbEmploye, list<WProduct> rawStocks);
	~WorkingUnit();
};