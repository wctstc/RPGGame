#ifndef __ITEMMANAGER_H__
#define __ITEMMANAGER_H__

#include <string>

#include "Singleton.h"
#include "Item.h"

using std::string;
/**
* @brief 物品管理
*/
class ItemManager :public Singleton<ItemManager>
{
public:
	ItemManager();
	~ItemManager();
public:
	/**
	 * @brief 初始化
	 */
	virtual bool Init();
public:
    /**
     * @brief 获取物品描述
     */
    const Item::ItemType GetTypeByID(const int iID)const;

    /**
     * @brief 获取物品描述
     */
    const string GetNameByID(const int iID)const;

    /**
     * @brief 获取物品描述
     */
    const string GetDescriptionByID(const int iID)const;

    /**
     * @brief 获取物品描述
     */
    const Item &GetItemByID(const int iID)const;

};

#endif