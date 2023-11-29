#include "BaseInclusion.h"
#include "Company.h"
#include "ProductBaseInfo.h"
#include "Constants.h"
#include "WProduct.h"


using namespace std;

Company::Company(shared_ptr<ProductBaseInfo> _productBaseInfo, pair<int,int> _position)
{
	nbEmploye = Constants::NB_EMPLOYE_START;
	salaryEmploye = Constants::SALARY_EMPLOYE_START;
	rAndDLevel = 1;
	position = _position;

	productBaseInfo = _productBaseInfo;
}

Company::~Company()
{

}


void Company::ApplyWorkDay()
{

}