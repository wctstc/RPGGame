#include "ItemLoader.h"


#include "dataconfig_item.pb.h"
#include "Platform.h"

using dataconfig::ITEM;
using dataconfig::ITEMArray;

using platform::UTF_82ASCII;

ItemLoader::ItemLoader()
{
}


ItemLoader::~ItemLoader()
{
}

bool ItemLoader::Init()
{
	ITEMArray ayItems;
	FILE *file;
	file = fopen("proto/data/dataconfig_item.data", "rb");
	if (file == NULL)
		return 0;
	char buffer[1024];
	int length = fread(buffer, 1, 1024, file);
	printf("length:%d", length);

	ayItems.ParseFromArray(buffer, length);

	const ITEM *pItemConfig;
	ItemData oItemData;
	for (int i = 0; i < ayItems.items_size(); ++i)
	{
		pItemConfig = &(ayItems.items(i));
		oItemData.iID = pItemConfig->id();
		oItemData.eType = static_cast<data::ItemType>(pItemConfig->type());
		oItemData.sDescription = UTF_82ASCII(pItemConfig->description());

		m_mapItemDatas.insert(pair<int, ItemData>(oItemData.iID, oItemData));
	}

	return true;
}

Item * ItemLoader::GetItemByID(int iID)
{
	Item *pItem = NULL;
	map<int, ItemData>::iterator it = m_mapItemDatas.find(iID);
	if (it != m_mapItemDatas.end())
	{
		pItem = CreateItemInstanceByType(it->second.eType);
		pItem->Init(it->second);
	}
	return pItem;
}

const ItemData ItemLoader::GetItemDataByID(const int iID) const
{
	map<int, ItemData>::const_iterator it = m_mapItemDatas.find(iID);
	if (it != m_mapItemDatas.end())
		return it->second;
	return ItemData();
}

void ItemLoader::ReleaseItem(Item *pItem)
{
	if (pItem != NULL)
		delete pItem;
}


Item * ItemLoader::CreateItemInstanceByType(const int iType)
{
	Item *pItem;
	switch (iType)
	{
	case data::ITEM_TYPE_NORMAL:
		pItem = new Item();
		break;
	default:
		pItem = new Item();
		break;
	}
	return pItem;
}
