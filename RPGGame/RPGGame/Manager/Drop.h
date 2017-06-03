#ifndef __DROP_H__
#define __DROP_H__

#include "Struct.h"

class Drop
{
public:
    Drop();
    virtual ~Drop();
public:
    static const Drop &GetNoDrop();
public:
    bool Init(Drop& oDrop);
    bool Init(const int iID, const int iItemID, const int iItemNum);
public:
    SET_GET(int, i, ID,      m_stDropData.iID)
    SET_GET(int, i, ItemID,  m_stDropData.iItemID)
    SET_GET(int, i, ItemNum, m_stDropData.iItemNum)
private:
    struct DropData
    {
        int iID;
        int iItemID;
        int iItemNum;
    };
private:
    DropData m_stDropData;
};

#endif // __DROP_H__

