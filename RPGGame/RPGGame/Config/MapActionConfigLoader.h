
#ifndef __MAPACTIONCONFIG_LOADER_H__
#define __MAPACTIONCONFIG_LOADER_H__



#define g_MapActionConfigLoader MapActionConfigLoader::GetInstance()

#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;

/**
 * @brief 地图行为类型
 */
enum MapActionType
{
		/*!< 采集 */
		MAP_ACTION_TYPE_COLLECTION = 1,

		/*!< 狩猎 */
		MAP_ACTION_TYPE_HANTING = 2,

};

/**
 * @brief 地图行为数据
 */
struct MapActionConfig
{	
		/*!< 编号 */
		int iID;
		
		/*!< 类型 */
		MapActionType eType;
		
		/*!< 消耗体力值 */
		int iPowerCost;
		
		/*!< 消耗时间 */
		int iTimeCost;
		
		/*!< 最大次数 */
		int iMaxtime;
		
		/*!< 恢复速度 */
		int iRecovery;
	
	
		/*!< 名字 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	
	
		/*!< 怪物 */
		vector< int > veciMonsterID;
		
		/*!< 掉落 */
		vector< int > veciDropID;
	

};

class MapActionConfigLoader : public Singleton<MapActionConfigLoader>
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
	const vector<MapActionConfig> &GetAllConfig();
	
	/**
	 * @brief 通过索引获取配置
	 */
	const MapActionConfig *GetMapActionConfigByIndex(const unsigned int uIndex);
	
	/**
	 * @brief 通过编号获取配置
	 */
	const MapActionConfig *GetMapActionConfigByID(const int iID);
		
	/**
	 * @brief 通过类型获取配置
	 */
	const MapActionConfig *GetMapActionConfigByType(const MapActionType eType);
		
	/**
	 * @brief 通过消耗体力值获取配置
	 */
	const MapActionConfig *GetMapActionConfigByPowerCost(const int iPowerCost);
		
	/**
	 * @brief 通过消耗时间获取配置
	 */
	const MapActionConfig *GetMapActionConfigByTimeCost(const int iTimeCost);
		
	/**
	 * @brief 通过最大次数获取配置
	 */
	const MapActionConfig *GetMapActionConfigByMaxtime(const int iMaxtime);
		
	/**
	 * @brief 通过恢复速度获取配置
	 */
	const MapActionConfig *GetMapActionConfigByRecovery(const int iRecovery);
	
	
	/**
	 * @brief 通过名字获取配置
	 */
	const MapActionConfig *GetMapActionConfigByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const MapActionConfig *GetMapActionConfigByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<MapActionConfig> m_vecRecords;
};

#endif //__MAPACTIONCONFIG_LOADER_H__
