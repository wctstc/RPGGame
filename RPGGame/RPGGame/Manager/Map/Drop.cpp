#include "Drop.h"

Drop::Drop()
{
    m_stDropData.iID = 0;
    m_stDropData.iItemID = 0;
    m_stDropData.iItemNum = 0;
}


Drop::~Drop()
{
}

const Drop & Drop::GetNoDrop()
{
    static Drop oDrop;
    return oDrop;
}

bool Drop::Init(Drop& oDrop)
{
    m_stDropData = oDrop.m_stDropData;
    return true;
}

bool Drop::Init(const int iID, const int iItemID, const int iItemNum)
{
    m_stDropData.iID      = iID;
    m_stDropData.iItemID  = iItemID;
    m_stDropData.iItemNum = iItemNum;
    return true;
}
