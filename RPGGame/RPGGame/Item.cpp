#include "Item.h"


Item::Item()
{
}


Item::~Item()
{
}

bool Item::Init(const ItemData &oItemData)
{
	m_oItemData = oItemData;
	return true;
}
