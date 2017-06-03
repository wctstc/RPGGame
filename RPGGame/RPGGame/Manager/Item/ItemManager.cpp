#include "ItemManager.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

bool ItemManager::Init()
{
	if (!g_ItemConfigLoader.Init())
		return false;
	return true;
}

const ItemType ItemManager::GetTypeByID(const int iID) const
{
    const ItemConfig *pItem = g_ItemConfigLoader.GetItemConfigByID(iID);

    return pItem?pItem->eType:ITEM_TYPE_NO;
}

const string ItemManager::GetNameByID(const int iID) const
{
    const ItemConfig *pItem = g_ItemConfigLoader.GetItemConfigByID(iID);

    return pItem ? pItem->sName : "";
}

const string ItemManager::GetDescriptionByID(const int iID) const 
{
    const ItemConfig *pItem = g_ItemConfigLoader.GetItemConfigByID(iID);

    return pItem ? pItem->sDescription : "";
}

const ItemConfig *ItemManager::GetItemByID(const int iID) const
{
    return g_ItemConfigLoader.GetItemConfigByID(iID);
}
