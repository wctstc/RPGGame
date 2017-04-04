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
	return ItemLoader::GetInstance().GetItemDataByID(iID).sDescription;
}
