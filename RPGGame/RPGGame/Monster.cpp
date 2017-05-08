#include "Monster.h"



Monster::Monster()
{
}


Monster::~Monster()
{
}

const Monster & Monster::GetNoMonster()
{
    static Monster oMonster;
    return oMonster;
}

bool Monster::Init(Monster& oMonster)
{
    if (!Actor::Init(oMonster))
        return false;

    m_stMonsterData = oMonster.m_stMonsterData;
    return true;
}

bool Monster::Init(
    const int iID,
    const string sName,
    const int iHp,
    const int iMaxHp,
    const int iAttack,
    const int iDefance, 
    const Monster::MonsterType eType,
    const string sDescription,
    const vector<int> &vDrop)
{
    if (!Actor::Init(iID, sName, iHp, iMaxHp, iAttack, iDefance))
        return false;

    m_stMonsterData.eType        = eType;
    m_stMonsterData.sDescription = sDescription;
    m_stMonsterData.vDrop        = vDrop;
    return true;
}
