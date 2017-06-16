#include "Container.h"
#include "Log.h"

Container::Container()
:m_pstContainerData(NULL)
{
}

Container::~Container()
{
}

bool Container::Init(ContainerData *pstContainerData)
{
    if (pstContainerData == NULL)
        return false;

    m_pstContainerData = pstContainerData;
    return true;
}

int Container::GetCapacity() const
{
    return MAX_CONTAINER_CAPACITY;
}

int Container::GetUsedCapacity() const
{
    return m_pstContainerData->GetCellNum();
}

int Container::Add(const int iItemID, const int iNumber)
{
    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return -1;
    }

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return -1;
    }

    if (TryAdd(iItemID, iNumber) != iNumber)
        return false;
    
    AddForce(iItemID, iNumber);
    return true;
}

void Container::AddForce(const int iItemID, const int iNumber)
{
    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return;
    }

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return;
    }

    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return;
    }


    int iLeft = iNumber;

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return;
    }

    //加入未满格子
    for (int i = 0; i < m_pstContainerData->GetCellNum(); ++i)
    {
        CellData *pstCell = m_pstContainerData->UseCell(i);
        if (pstCell == NULL)
        {
            GLogError("get cell fail. i:%d, cell num:%d", i, m_pstContainerData->GetCellNum());
            return;
        }


        if (pstCell->GetID() == iItemID)//可叠加格子
        {
            int iCapacity = pstCell->GetUnitCapacity() - pstCell->GetItemNum();
            if (iLeft > iCapacity)
            {
                pstCell->SetItemNum(pstCell->GetUnitCapacity());
                iLeft -= iCapacity;
            }
            else
            {
                pstCell->UseItemNum() += iCapacity;
                iLeft = 0;
                break;
            }
        }
    }

    //加入空格子
    for (int i = m_pstContainerData->GetCellNum(); i < MAX_CONTAINER_CAPACITY; ++i)
    {
        CellData stCell;

        stCell.SetID(i);
        stCell.SetItemID(iItemID);
        
        if (iLeft > stCell.GetUnitCapacity())
        {
            stCell.SetItemNum(stCell.GetUnitCapacity());
            iLeft -= stCell.GetUnitCapacity();
        }
        else
        {
            stCell.SetItemNum(iLeft);
            iLeft = 0;
        }
            
        if (!m_pstContainerData->AddCell(stCell))
        {
            GLogError("add cell fail.");
            return;
        }

        if (iLeft <= 0)
        {
            iLeft = 0;
            break;
        }
    }

    if (iLeft != 0)
    {
        GLogError("add force but capacity is not enough."
            "item id:%d item num:%d. left:%d",
            iItemID, iNumber, iLeft);
    }
}

int Container::TryAdd(const int iItemID, const int iNumber) const
{
    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return -1;
    }

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return -1;
    }

    int iCapacity = GetItemCapacityByItemID(iItemID);

    if (iCapacity > iNumber)
        return iNumber;
    
    return iNumber;
}


int Container::Remove(const int iItemID, const int iNumber)
{
    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return -1;
    }

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return -1;
    }

    if (TryRemove(iItemID, iNumber) == iNumber)
        return false;
    

    RemoveForce(iItemID, iNumber);
    return true;
}


int Container::TryRemove(const int iItemID, const int iNumber)
{
    if (m_pstContainerData == NULL)
    {
        GLogError("m_pstContainerData is NULL");
        return -1;
    }

    if (iItemID <= 0 || iNumber <= 0)
    {
        GLogError("item error.item id:%d, num:%d", iItemID, iNumber);
        return -1;
    }

    int iCount = GetItemNumByItemID(iItemID);

    if (iCount > iNumber)
        return iNumber;

    return iCount;
}

void Container::RemoveForce(const int iItemID, const int iNumber)
{
//     int iLeft = iNumber;
//     VecContainerUnitIt it;
// 
//     //先扣除未满的格子
//     it = m_vContainerUnits.begin();
//     for (; it != m_vContainerUnits.end(); ++it)
//     {
//         if (it->iItemID == iItemID && it->iItemNum != it->iUnitCapacity)
//         {
//             if (it->iItemNum > iLeft)
//             {
//                 it->iItemNum -= iLeft;
//                 return;
//             }
//             else
//             {
//                 iLeft -= it->iItemNum;
//                 it->iItemNum = 0;
//                 it->iItemID  = 0;
//             }
//         }
//     }
// 
//     //扣除满的格子
//     it = m_vContainerUnits.begin();
//     for (; it != m_vContainerUnits.end(); ++it)
//     {
//         if (it->iItemID == iItemID && it->iItemNum == it->iUnitCapacity)
//         {
//             if (it->iItemNum > iLeft)
//             {
//                 it->iItemNum -= iLeft;
//                 return;
//             }
//             else
//             {
//                 iLeft -= it->iItemNum;
//                 it->iItemNum = 0;
//                 it->iItemID = 0;
//             }
//         }
//     }
}


int Container::GetItemNumByItemID(const int iItemID) const
{
    int iNumber = 0;
    for (int i =0; i < m_pstContainerData->GetCellNum(); ++i)
    {
        CellData stData;
        if (!m_pstContainerData->GetCell(i, stData))
        {
            GLogError("get cell fail. %d", i);
            return 0;
        }

        if( stData.GetItemID() == iItemID )
            iNumber += stData.GetItemNum();
    }
    return iNumber;
}

int Container::GetItemCapacityByItemID(const int iItemID) const
{
    int iCapacity = 0;
    for (int i = 0; i < m_pstContainerData->GetCellNum(); ++i)
    {
        CellData stData;
        if (!m_pstContainerData->GetCell(i, stData))
        {
            GLogError("get cell fail. %d", i);
            return 0;
        }

        if (stData.GetItemID() == iItemID)
            iCapacity += (stData.GetUnitCapacity() - stData.GetItemNum());
    }

    CellData stCellData;
    stCellData.SetItemID(iItemID);

    for (int i = m_pstContainerData->GetCellNum(); i < MAX_CONTAINER_CAPACITY; ++i)
        iCapacity += stCellData.GetUnitCapacity();
    
    return iCapacity;
}
