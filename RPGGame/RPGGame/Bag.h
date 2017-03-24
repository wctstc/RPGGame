#ifndef __BAG_H__
#define __BAG_H__

#include "Item.h"

/**
 * @brief 背包类
 */
class Bag
{
public:
	Bag();
	~Bag();
public:
	/**
	 * @brief 获取物品数量
	 */
	int GetItemsNumber()const;

	/**
	 * @brief 添加物品
	 */
	bool AddItem(const Item& oItem );

	/**
	 * @brief 获取物品编号
	 */
	unsigned int GetItemID(int iIndex)const;

	/**
	 * @brief 获取物品描述
	 */
	const string GetItemDescription(int iIndex)const;
private:
	/*!< 物品 */
	vector<Item> m_vItems;
};


#endif // __BAG_H__

