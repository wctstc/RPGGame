
#ifndef __SHOPCONFIG_LOADER_H__
#define __SHOPCONFIG_LOADER_H__



#define g_ShopConfigLoader ShopConfigLoader::GetInstance()

#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 掉落
 */
struct ShopConfig
{	
		/*!< 编号 */
		int iID;
		
		/*!< 物品编号 */
		int iItemID;
		
		/*!< 物品数量 */
		int iItemNum;
		
		/*!< 价格 */
		int iPrice;
		
		/*!< 物品数量 */
		int iDiscount;
	



};

class ShopConfigLoader : public Singleton<ShopConfigLoader>
{
public:
	/**
	 * @brief 初始化
	 */
    bool Init();
	
public:
	/**
	 * @brief 获取全部配置
	 */
	const vector<ShopConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const ShopConfig *GetShopConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const ShopConfig *GetShopConfigByID(const int iID);
		
	/**
	 * @brief 通过物品编号获取配置
	 */
	const ShopConfig *GetShopConfigByItemID(const int iItemID);
		
	/**
	 * @brief 通过物品数量获取配置
	 */
	const ShopConfig *GetShopConfigByItemNum(const int iItemNum);
		
	/**
	 * @brief 通过价格获取配置
	 */
	const ShopConfig *GetShopConfigByPrice(const int iPrice);
		
	/**
	 * @brief 通过物品数量获取配置
	 */
	const ShopConfig *GetShopConfigByDiscount(const int iDiscount);
	

private:
	/*!< 配置数据 */
    vector<ShopConfig> m_vecRecords;
};

#endif //__SHOPCONFIG_LOADER_H__
