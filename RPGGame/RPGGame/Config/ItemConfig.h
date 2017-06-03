
#ifndef __ITEM_LOADER_H__
#define __ITEM_LOADER_H__



#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;

/**
 * @brief 物品类型
 */
enum ItemType
{
		/*!< 空类型 */
		ITEM_TYPE_NO = 0,

		/*!< 普通类型 */
		ITEM_TYPE_NORMAL = 1,

		/*!< 武器类型 */
		ITEM_TYPE_EQUIPMENT = 2,

		/*!< 类型最大值 */
		ITEM_TYPE_MAX = 3,

};

/**
 * @brief 物品数据
 */
struct Item
{	
		/*!< 编号 */
		int iID;
		
		/*!< 类型 */
		ItemType eType;
	
	
		/*!< 名字 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	


};

class ItemConfig : public Singleton<ItemConfig>
{
public:
	/**
	 * @brief 初始化
	 */
    bool Init();
	
public:
	
	/**
	 * @brief 通过编号获取配置
	 */
	const Item *GetItemByID(const int iID);
		
	/**
	 * @brief 通过类型获取配置
	 */
	const Item *GetItemByType(const ItemType eType);
	
	
	/**
	 * @brief 通过名字获取配置
	 */
	const Item *GetItemByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const Item *GetItemByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<Item> m_vecRecords;
};

#endif //__ITEM_LOADER_H__
