
#ifndef __DROPCONFIG_LOADER_H__
#define __DROPCONFIG_LOADER_H__



#define g_DropConfigLoader DropConfigLoader::GetInstance()

#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 掉落
 */
struct DropConfig
{	
		/*!< 编号 */
		int iID;
		
		/*!< 物品编号 */
		int iItemID;
		
		/*!< 物品数量 */
		int iItemNum;
	



};

class DropConfigLoader : public Singleton<DropConfigLoader>
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
	const vector<DropConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const DropConfig *GetDropConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const DropConfig *GetDropConfigByID(const int iID);
		
	/**
	 * @brief 通过物品编号获取配置
	 */
	const DropConfig *GetDropConfigByItemID(const int iItemID);
		
	/**
	 * @brief 通过物品数量获取配置
	 */
	const DropConfig *GetDropConfigByItemNum(const int iItemNum);
	

private:
	/*!< 配置数据 */
    vector<DropConfig> m_vecRecords;
};

#endif //__DROPCONFIG_LOADER_H__
