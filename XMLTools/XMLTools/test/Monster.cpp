
#include "Monster.h"

Monster::Monster()
:m_eType(Monster::MONSTER_TYPE_GENTLE)
,m_iDescription("")

{
    m_iDropsRef = 0;

    memset(m_astDrops, 0, sizeof(Drop)*DROP_MAX);

}

Monster::~Monster()
{

}

bool Monster::Init()
{
    if(!ActorData::Init())
        return false;
    m_eType = Monster::MONSTER_TYPE_GENTLE;
    m_iDescription = "";

    m_iDropsRef = 0;

    memset(m_astDrops, 0, sizeof(Drop)*DROP_MAX);

    return true;
}

bool Monster::Init(const Monster &oMonster)
{
    if(!ActorData::Init(oMonster))
        return false;
    m_eType = oMonster.m_eType;
    m_iDescription = oMonster.m_iDescription;

    return true;
}

string Monster::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool Monster::FromString(const string sBuffer)
{
    return true;
}
int Monster::GetDropsNum() const
{
    return m_iDropsRef;
}

bool Monster::GetDrops(const int iIndex, Drop &stDrops) const
{
    if(iIndex < 0 || iIndex >= m_iDropsRef)
        return false;

    stDrops = m_astDrops[iIndex];
    return true;
}


bool Monster::AddDrops(Drop stDrops)
{
    if(m_iDropsRef >= DROP_MAX)
        return false;
        
    m_astDrops[m_iDropsRef++] = stDrops;
    return true;
}


bool Monster::RemoveDrops(int iIndex)
{
    if(iIndex < 0 || iIndex >= m_iDropsRef)
        return false;

    --m_iDropsRef;
    
    for (int i = iIndex; i < m_iDropsRef; ++i)
        m_astDrops[i] = m_astDrops[i+1];

    return true;
}






	
	int Monster::GetDropsID(const int iIndex) const
	{
		if (iIndex < m_stDropsRef ef iIndex >= 0) 
			return m_astDrops[iIndex];
		return 0;
	}
	int Monster::GetDropsNum(const int iIndex) const
	{
		if (iIndex < m_stDropsRef ef iIndex >= 0) 
			return m_astDrops[iIndex];
		return 0;
	}
	
