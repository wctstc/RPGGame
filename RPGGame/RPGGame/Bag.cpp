#include "Bag.h"

const int Bag::g_iMaxCapacity = 20;


Bag::Bag()
{
}


Bag::~Bag()
{
}

bool Bag::Init(const int iID, const int iCapacity)
{
    m_stContainerData.iID = iID;
    m_stContainerData.iCapacity = iCapacity;

    m_vUnits.clear();
    return true;
}

bool Bag::Save(int &iLength, char *csBuffer)const
{
    int iSize = sizeof(m_stContainerData);
    if (iLength < iSize)
        return false;

    memcpy(csBuffer, &m_stContainerData, iSize);


    int iUsedSize = iSize;
    for (vector<Unit>::const_iterator it = m_vUnits.begin(); it != m_vUnits.end(); ++it)
    {
        int iLeftSize = iLength - iUsedSize;
        if (!(*it).Save(iLeftSize, csBuffer + iUsedSize))
            return false;
        iUsedSize += iLeftSize;
    }
    iLength = iUsedSize;
    return true;
}

bool Bag::Load( int &iLength, const char *const csBuffer)
{
    int iSize = sizeof(m_stContainerData);
    if (iLength < iSize)
        return false;

    memcpy(&m_stContainerData, csBuffer, iSize);

    int iUsedSize = iSize;
    m_vUnits.clear();
    for (int i =0; i < m_stContainerData.iUsed && iUsedSize < iLength; ++i )
    {
        int iLeftSize = iLength - iUsedSize;
        Unit oUnit;
        if (!oUnit.Load(iLeftSize, csBuffer + iUsedSize))
            return false;

        m_vUnits.push_back(oUnit);
        iUsedSize += iLeftSize;
    }
    return true;
}

int Bag::GetUsedCapacity() const
{
    return m_stContainerData.iUsed;
}

bool Bag::Add(const int iItemID, const int iNumber)
{
    int iSize = m_vUnits.size();
    for (int i = 0; i < m_stContainerData.iUsed && i < iSize; ++i)
    {
        Unit &rUnit = m_vUnits.at(i);
        if (iItemID == rUnit.GetItemID())
        {
            rUnit.Add(iNumber);
            return true;
        }
    }
    if (m_stContainerData.iUsed < g_iMaxCapacity
        && m_vUnits.size() < g_iMaxCapacity)
    {
        Unit oUnit;
        oUnit.SetID(0);
        oUnit.SetItemID(iItemID);
        oUnit.SetItemNum(iNumber);
        oUnit.SetUnitCapacity(10000);

        m_vUnits.push_back(oUnit);
        ++m_stContainerData.iUsed;
        return true;
    }
    return false;
}

bool Bag::Reduce(const int iItemID, const int iNumber)
{
    for (vector<Unit>::iterator it = m_vUnits.begin();it != m_vUnits.end(); ++it)
    {
        if (iItemID == it->GetItemID())
        {
            if (!it->Reduce(iNumber))
                return false;
            if (it->GetItemNum() <= 0)
            {
                it = m_vUnits.erase(it);
                --m_stContainerData.iUsed;
            }
            return true;
        }
    }
    return false;

}

int Bag::GetItemID(const int iIndex) const

{
    int iSize = m_vUnits.size();
    if (iIndex < iSize && iIndex < m_stContainerData.iUsed)
        return m_vUnits.at(iIndex).GetItemID();
    return 0;
}

int Bag::GetItemNum(const int iIndex) const
{
    int iSize = m_vUnits.size();
    if (iIndex < iSize && iIndex < m_stContainerData.iUsed)
        return m_vUnits.at(iIndex).GetItemNum();
    return 0;
}

int Bag::GetItemNumByItemID(const int iItemID) const
{
    for (vector<Unit>::const_iterator it = m_vUnits.begin(); it != m_vUnits.end(); ++it)
    {
        if (it->GetItemID() == iItemID)
            return it->GetItemNum();
    }
    return 0;
}
