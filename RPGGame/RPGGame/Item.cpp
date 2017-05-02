#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

bool Item::Init(const Item &oItem)
{
    m_oItemData = oItem.m_oItemData;
    return true;
}


bool Item::Init(const int iID, const ItemType eType, const string &sName, const string &sDestription)
{
    m_oItemData.iID          = iID;
    m_oItemData.eType        = eType;
    m_oItemData.sName        = sName;
    m_oItemData.sDescription = sDestription;
    return true;
}
