#include "Actor.h"



Actor::Actor()
{
}


Actor::~Actor()
{
}

bool Actor::Init(const Actor &oActor)
{
    m_stActorData = oActor.m_stActorData;
    return true;
}


bool Actor::Init(
    const int iID, 
    const int iHp,
    const int iMaxHp,
    const int iAttack,
    const int iDefance)
{
	m_stActorData.iID      = iID;
	m_stActorData.iHp      = iHp;
	m_stActorData.iMaxHp   = iMaxHp;
	m_stActorData.iAttack  = iAttack;
	m_stActorData.iDefance = iDefance;
	return true;
}

void Actor::Reset()
{
	m_stActorData.iHp = GetMaxHp();
}

void Actor::Defance(const int iDamage)
{
	int iRealDamage = iDamage - m_stActorData.iDefance;
	if (iRealDamage <= 0)
		iRealDamage = 1;
	m_stActorData.iHp -= iRealDamage;
}

int Actor::Attack()
{
	return m_stActorData.iAttack;
}

bool Actor::IsDie()
{
	return m_stActorData.iHp <= 0;
}
