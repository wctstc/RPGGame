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

const string ItemManager::GetDescriptionByID(const int iID) const 
{
    string sDescription;
    Item *pItem = ItemLoader::GetInstance().GetItemByID(iID);
    sDescription = pItem->GetDescription();
    ItemLoader::GetInstance().ReleaseItem(pItem);
    return sDescription;
}
