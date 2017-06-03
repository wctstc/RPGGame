#include "Actor.h"



Actor::Actor()
{
    m_stActorData.iID = -1;
    m_stActorData.sName = "无行动者";
    m_stActorData.iHp = 0;
    m_stActorData.iMaxHp = 0;
    m_stActorData.iAttack = 0;
    m_stActorData.iDefance = 0;
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
    const string sName,
    const int iHp,
    const int iMaxHp,
    const int iAttack,
    const int iDefance)
{
	m_stActorData.iID      = iID;
    m_stActorData.sName    = sName;
    m_stActorData.iPreHp   = iHp;
	m_stActorData.iHp      = iHp;
	m_stActorData.iMaxHp   = iMaxHp;
	m_stActorData.iAttack  = iAttack;
	m_stActorData.iDefance = iDefance;
	return true;
}

void Actor::Reset()
{
    m_stActorData.iPreHp = m_stActorData.iHp;
	m_stActorData.iHp = GetMaxHp();
}

void Actor::Defance(const int iDamage)
{
	int iRealDamage = iDamage - m_stActorData.iDefance;

	if (iRealDamage <= 0)
        iRealDamage = 1;

    m_stActorData.iPreHp = m_stActorData.iHp;

	m_stActorData.iHp -= iRealDamage;
}

int Actor::Attack()const
{
	return m_stActorData.iAttack;
}

bool Actor::IsDie()const
{
	return m_stActorData.iHp <= 0;
}
