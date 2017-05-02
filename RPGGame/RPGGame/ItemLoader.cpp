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
	char buffer[10240];
	int length = fread(buffer, 1, 10240, file);

	ayItems.ParseFromArray(buffer, length);

	const ITEM *pItemConfig;
	for (int i = 0; i < ayItems.items_size(); ++i)
	{
        Item oItem;
		pItemConfig = &(ayItems.items(i));
        oItem.Init(
            pItemConfig->id(),
		    static_cast<Item::ItemType>(pItemConfig->type()),
            "",
		    UTF_82ASCII(pItemConfig->description()));

		m_mapItemDatas.insert(pair<int, Item>(oItem.GetID(), oItem));
	}

	return true;
}

Item * ItemLoader::GetItemByID(int iID)
{
	Item *pItem = NULL;
	map<int, Item>::iterator it = m_mapItemDatas.find(iID);
	if (it != m_mapItemDatas.end())
	{
		pItem = CreateItemInstanceByType(it->second.GetType());
		pItem->Init(it->second);
	}
	return pItem;
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
	case Item::ITEM_TYPE_NORMAL:
		pItem = new Item();
		break;
	default:
		pItem = new Item();
		break;
	}
	return pItem;
}
