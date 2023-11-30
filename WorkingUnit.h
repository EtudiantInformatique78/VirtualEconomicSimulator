#pragma once


class WorkingUnit
{
private:
	int nbWorkingEmploye;


public:
	WorkingUnit(int nbEmploye, vector<WProduct> rawStocks);
	~WorkingUnit();
};