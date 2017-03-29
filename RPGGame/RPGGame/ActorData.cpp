#include "ActorData.h"



ActorData::ActorData()
{
}


ActorData::~ActorData()
{
}

bool ActorData::Init(int iID, int iHp, int iMaxHp, int iAttack, int iDefance)
{
	m_iID = iID;
	m_iHp = iHp;
	m_iMaxHp = iMaxHp;
	m_iAttack = iAttack;
	m_iDefance = iDefance;
	return true;
}

bool ActorData::Init(const ActorData &oActorData)
{
	m_iID = oActorData.m_iID;
	m_iHp = oActorData.GetHp();
	m_iMaxHp = oActorData.GetMaxHp();
	m_iAttack = oActorData.GetAttack();
	m_iDefance = oActorData.GetDefance();
	return true;
}

