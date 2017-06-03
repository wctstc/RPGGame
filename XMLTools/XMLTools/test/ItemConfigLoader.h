
#ifndef __ITEMCONFIG_LOADER_H__
#define __ITEMCONFIG_LOADER_H__

#include <vector>

#include "Singleton.h"

using std::vector;

class ItemConfigLoader : public Singleton<ItemConfigLoader>
{
public:
	/**
	 * @brief 物品数据
	 */
	struct ItemConfig
	{	
	/*!< 类型 */
	ItemType eType;
		
	/*!< 名字 */
	string sName;
		
	/*!< 描述 */
	string sDescription;
	
	}

public:
	/**
	 * @brief 初始化
	 */
    bool Init();
	
public:
	
	/**
	 * @brief 通过类型获取配置
	 */
	const ItemConfig *GetItemConfigByType(const ItemType eType);
		
	/**
	 * @brief 通过名字获取配置
	 */
	const ItemConfig *GetItemConfigByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const ItemConfig *GetItemConfigByDescription(const string sDescription);
	
private:
    vector<ItemConfig> m_vecRecords;
}


#endif //__ITEMCONFIG_LOADER_H__
