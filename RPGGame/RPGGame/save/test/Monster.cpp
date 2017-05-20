
#include "Monster.h"

Monster::Monster()
:m_eType(Monster::MONSTER_TYPE_GENTLE)
,m_iDescription("")
,m_vDrop(vector<int>())

{
    m_iDropsRef = 0;

    memset(m_astDrops, 0, sizeof(Drop)*DROP_MAX);

}

Monster::~Monster()
{

}

bool Monster::Init()
{

    m_eType = Monster::MONSTER_TYPE_GENTLE;
    m_iDescription = "";
    m_vDrop = vector<int>();

    m_iDropsRef = 0;

    memset(m_astDrops, 0, sizeof(Drop)*DROP_MAX);

    return true;
}

bool Monster::Init(const Monster &oMonster)
{

    m_eType = oMonster.m_eType;
    m_iDescription = oMonster.m_iDescription;
    m_vDrop = oMonster.m_vDrop;

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



    bool #class_name#::SetDropID( const int iIndex, const int iID )
    {
        if(iIndex < 0 || iIndex >= m_i#array_property_name#Ref)
        return false;

        m_a#array_property_prefix##array_property_name#[iIndex].ID = iID;
        return true;
    }    bool #class_name#::SetDropNum( const int iIndex, const int iNum )
    {
        if(iIndex < 0 || iIndex >= m_i#array_property_name#Ref)
        return false;

        m_a#array_property_prefix##array_property_name#[iIndex].Num = iNum;
        return true;
    }

