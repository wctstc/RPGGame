#include "Unit.h"



Unit::Unit()
{
}


Unit::~Unit()
{
}

bool Unit::Init(Unit &oUnit)
{
    m_stUnitData = oUnit.m_stUnitData;
    return true;
}

bool Unit::Init(const int iID, const int iItemID, const int iItemNum, const int iUnitCapacity)
{
    m_stUnitData.iID           = iID;
    m_stUnitData.iItemID       = iItemID;
    m_stUnitData.iItemNum      = iItemNum;
    m_stUnitData.iUnitCapacity = iUnitCapacity;
    return true;
}

bool Unit::Save(int &iLength, char *csBuffer)const
{
    int iSize = sizeof(m_stUnitData);

    if (iLength < iSize)
        return false;

    iLength = iSize;
    memcpy(csBuffer, &m_stUnitData, iSize);
    return true;
}

bool Unit::Load(int &iLength, const char *const csBuffer)
{
    int iSize = sizeof(m_stUnitData);

    if (iLength < iSize)
        return false;

    memcpy(&m_stUnitData, csBuffer, iSize);
    iLength = iSize;
    return true;
}

bool Unit::Add(const int iItemNum)
{
    m_stUnitData.iItemNum += iItemNum;
    return true;
}

bool Unit::Reduce(const int iItemNum)
{
    if (m_stUnitData.iItemNum < iItemNum)
        return false;

    m_stUnitData.iItemNum -= iItemNum;
    return true;
}
