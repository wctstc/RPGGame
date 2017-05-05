#ifndef __ITEMLOADER_H__
#define __ITEMLOADER_H__

#include <map>

using std::map;
using std::pair;


#include "Singleton.h"
#include "Struct.h"
#include "Item.h"


/**
* @brief 物品加载器
*/
class ItemLoader :public Singleton<ItemLoader>
{
public:
	ItemLoader();
	~ItemLoader();
public:
	/**
	* @brief 初始化
	*/
	bool Init();
public:
	/**
	* @brief 通过编号获取物品
	*/
	const Item & GetItemByID(const int iID)const ;

private:
	/*!< 编号与物品数据映射 */
	map<int, Item> m_mapItemDatas;
};


#endif