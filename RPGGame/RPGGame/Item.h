#ifndef __ITEM_H__
#define __ITEM_H__

#include "Struct.h"

using data::ItemData;

/**
 * @brief 物品类
 */
class Item
{
public:
	Item();
	~Item();
public:
	SET_GET(int,    i, ID,          m_oItemData.iID);
	SET_GET(string, s, Description, m_oItemData.sDescription);
public:
	/*!< 物品数据 */
	ItemData m_oItemData;
};


#endif // __ITEM_H__

