
#ifndef __MAPCONFIG_LOADER_H__
#define __MAPCONFIG_LOADER_H__



#define g_MapConfigLoader MapConfigLoader::GetInstance()

#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 地图数据
 */
struct MapConfig
{	
		/*!< 编号 */
		int iID;
	
	
		/*!< 名称 */
		string sName;
	
	
		/*!< 行动 */
		vector< int > veciActionID;
	

};

class MapConfigLoader : public Singleton<MapConfigLoader>
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
	const vector<MapConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const MapConfig *GetMapConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const MapConfig *GetMapConfigByID(const int iID);
	
	
	/**
	 * @brief 通过名称获取配置
	 */
	const MapConfig *GetMapConfigByName(const string sName);
	
private:
	/*!< 配置数据 */
    vector<MapConfig> m_vecRecords;
};

#endif //__MAPCONFIG_LOADER_H__
