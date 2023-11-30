#include "BaseInclusion.h"

#include "ProductBaseInfoBuilder.h"
#include "ProductBaseInfo.h"
#include "WProduct.h"
#include "Company.h"
#include "Constants.h"

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