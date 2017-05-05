#include "ItemManager.h"
#include "ItemLoader.h"

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

bool ItemManager::Init()
{
	if (!ItemLoader::GetInstance().Init())
		return false;
	return true;
}

const Item::ItemType ItemManager::GetTypeByID(const int iID) const
{
    const Item &oItem = ItemLoader::GetInstance().GetItemByID(iID);
    return oItem.GetType();
}

const string ItemManager::GetNameByID(const int iID) const
{
    const Item &oItem = ItemLoader::GetInstance().GetItemByID(iID);
    return oItem.GetName();
}

const string ItemManager::GetDescriptionByID(const int iID) const 
{
    const Item &oItem = ItemLoader::GetInstance().GetItemByID(iID);
    return oItem.GetDescription();
}

const Item & ItemManager::GetItemByID(const int iID) const
{
    return ItemLoader::GetInstance().GetItemByID(iID);
}
