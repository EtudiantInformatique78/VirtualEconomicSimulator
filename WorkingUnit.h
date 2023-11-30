#pragma once


class WorkingUnit
{
private:
	int nbWorkingEmploye;


public:
	WorkingUnit(int nbEmploye, list<WProduct> rawStocks);
	~WorkingUnit();
};