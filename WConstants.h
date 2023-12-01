#pragma once


class WConstants
{
public:

	static const int NB_EMPLOYE_START;
	static const float SALARY_EMPLOYE_START;
	static const float PRICE_FLUCTUATION_SCALING;
	static const float COMPANY_START_CAPITAL;

	static const float BASE_UPGRADE_COST_RESEARCH;
	static const float UPGRADE_RATIO_COST_RESEARCH;

	/// <summary>
	/// The Company need that the upgrade represent maximum X % of the capital to invest
	/// </summary>
	static const float MINIMUM_PERCENT_TO_UPGRADE_RESEARCH;

	static const float EMPLOYE_AMOUNT_UPGRADE_RESEARCH;
	static const float EMPLOYE_PRODUCTIVITY_UPGRADE_RESEARCH;

	static const float MARGIN_RATIO_RESEARCH;
	static const float FABRICATION_COST_RATIO_RESEARCH;


	static const int NB_COMPANY_PER_PRODUCT;
};