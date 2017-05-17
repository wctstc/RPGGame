
#include "Monster.h"

Monster::Monster()
:m_eType(Monster::MONSTER_TYPE_GENTLE)
,m_iDescription("")
,m_vDrop(vector<int>())

{
    m_iDropRef = 0;
    m_iDrop2Ref = 0;

    memset(m_aiDrop, 0, sizeof(int)*DROP_MAX);
    memset(m_aiDrop2, 0, sizeof(int)*DROP_MAX);

}

Monster::~Monster()
{

}

bool Monster::Init()
{
    if(!Actor::Init())
        return false;
    m_eType = Monster::MONSTER_TYPE_GENTLE;
    m_iDescription = "";
    m_vDrop = vector<int>();

    m_iDropRef = 0;
    m_iDrop2Ref = 0;

    memset(m_aiDrop, 0, sizeof(int)*DROP_MAX);
    memset(m_aiDrop2, 0, sizeof(int)*DROP_MAX);

    return true;
}

bool Monster::Init(const Monster &oMonster)
{
    if(!Actor::Init(oMonster))
        return false;
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
int Monster::GetDropNum() const
{
    return m_iDropRef;
}
int Monster::GetDrop2Num() const
{
    return m_iDrop2Ref;
}

bool Monster::GetDrop(const int iIndex, int &iDrop) const
{
    if(iIndex < 0 || iIndex >= m_iDropRef)
        return false;

    iDrop = m_aiDrop[iIndex];
    return true;
}
bool Monster::GetDrop2(const int iIndex, int &iDrop2) const
{
    if(iIndex < 0 || iIndex >= m_iDrop2Ref)
        return false;

    iDrop2 = m_aiDrop2[iIndex];
    return true;
}


bool Monster::AddDrop(int iDrop)
{
    if(m_iDropRef >= DROP_MAX)
        return false;
        
    m_aiDrop[m_iDropRef++] = iDrop;
    return true;
}

bool Monster::AddDrop2(int iDrop2)
{
    if(m_iDrop2Ref >= DROP_MAX)
        return false;
        
    m_aiDrop2[m_iDrop2Ref++] = iDrop2;
    return true;
}


bool Monster::RemoveDrop(int iIndex)
{
    if(iIndex < 0 || iIndex >= m_iDropRef)
        return false;

    --m_iDropRef;
    
    for (int i = iIndex; i < m_iDropRef; ++i)
        m_aiDrop[i] = m_aiDrop[i+1];

    return true;
}

bool Monster::RemoveDrop2(int iIndex)
{
    if(iIndex < 0 || iIndex >= m_iDrop2Ref)
        return false;

    --m_iDrop2Ref;
    
    for (int i = iIndex; i < m_iDrop2Ref; ++i)
        m_aiDrop2[i] = m_aiDrop2[i+1];

    return true;
}


