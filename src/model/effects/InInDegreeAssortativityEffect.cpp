/******************************************************************************
 * SIENA: Simulation Investigation for Empirical Network Analysis
 *
 * Web: http://www.stats.ox.ac.uk/~snijders/siena/
 *
 * File: InInDegreeAssortativityEffect.cpp
 *
 * Description: This file contains the implementation of the
 * InInDegreeAssortativityEffect class.
 *****************************************************************************/

#include <cmath>

#include "InInDegreeAssortativityEffect.h"
#include "utils/SqrtTable.h"
#include "network/Network.h"
#include "network/TieIterator.h"
#include "model/EffectInfo.h"
#include "model/variables/NetworkVariable.h"

using namespace std;

namespace siena
{

/**
 * Constructor.
 */
InInDegreeAssortativityEffect::InInDegreeAssortativityEffect(
	const EffectInfo * pEffectInfo) : NetworkEffect(pEffectInfo)
{
	this->lroot = pEffectInfo->internalEffectParameter() == 2;
	this->lsqrtTable = SqrtTable::instance();
}


/**
 * Calculates the contribution of a tie flip to the given actor.
 */
double InInDegreeAssortativityEffect::calculateContribution(int alter)
	const
{
	double change = 0;
	const Network * pNetwork = this->pNetwork();
	int egoDegree = pNetwork->inDegree(this->ego());
	int alterDegree = pNetwork->inDegree(alter);

	if (!this->outTieExists(alter))
	{
		alterDegree++;
	}

	if (this->lroot)
	{
		change =
			this->lsqrtTable->sqrt(egoDegree) *
				this->lsqrtTable->sqrt(alterDegree);
	}
	else
	{
		change = egoDegree * alterDegree;
	}

	return change;
}


/**
 * The contribution of the tie from the implicit ego to the given alter
 * to the statistic. It is assumed that preprocessEgo(ego) has been
 * called before.
 */
double InInDegreeAssortativityEffect::tieStatistic(int alter)
{
	double statistic;
	const Network * pNetwork = this->pNetwork();
	int egoDegree = pNetwork->inDegree(this->ego());
	int alterDegree = pNetwork->inDegree(alter);

	if (this->lroot)
	{
		statistic =
			this->lsqrtTable->sqrt(egoDegree) *
				this->lsqrtTable->sqrt(alterDegree);
	}
	else
	{
		statistic = egoDegree * alterDegree;
	}

	return statistic;
}

}
