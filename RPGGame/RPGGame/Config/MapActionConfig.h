
#ifndef __MAPACTION_LOADER_H__
#define __MAPACTION_LOADER_H__



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
struct MapAction
{	
		/*!< 编号 */
		int iID;
		
		/*!< 类型 */
		MapActionType eType;
		
		/*!< 消耗体力值 */
		int iPower_cost;
		
		/*!< 消耗时间 */
		int iTime_cost;
		
		/*!< 最大次数 */
		int iMaxtime;
		
		/*!< 恢复速度 */
		int iRecovery;
	
	
		/*!< 名字 */
		string sName;
		
		/*!< 描述 */
		string sDescription;
	
	
		/*!< 怪物 */
		vector< int > veciMonster_id;
		
		/*!< 掉落 */
		vector< int > veciDrop_id;
	

};

class MapActionConfig : public Singleton<MapActionConfig>
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
	const MapAction *GetMapActionByID(const int iID);
		
	/**
	 * @brief 通过类型获取配置
	 */
	const MapAction *GetMapActionByType(const MapActionType eType);
		
	/**
	 * @brief 通过消耗体力值获取配置
	 */
	const MapAction *GetMapActionByPower_cost(const int iPower_cost);
		
	/**
	 * @brief 通过消耗时间获取配置
	 */
	const MapAction *GetMapActionByTime_cost(const int iTime_cost);
		
	/**
	 * @brief 通过最大次数获取配置
	 */
	const MapAction *GetMapActionByMaxtime(const int iMaxtime);
		
	/**
	 * @brief 通过恢复速度获取配置
	 */
	const MapAction *GetMapActionByRecovery(const int iRecovery);
	
	
	/**
	 * @brief 通过名字获取配置
	 */
	const MapAction *GetMapActionByName(const string sName);
		
	/**
	 * @brief 通过描述获取配置
	 */
	const MapAction *GetMapActionByDescription(const string sDescription);
	
private:
	/*!< 配置数据 */
    vector<MapAction> m_vecRecords;
};

#endif //__MAPACTION_LOADER_H__
