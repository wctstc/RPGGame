
#ifndef __MAP_LOADER_H__
#define __MAP_LOADER_H__



#include <vector>
#include <string>

#include "Singleton.h"


using std::vector;
using std::string;



/**
 * @brief 地图数据
 */
struct Map
{	
		/*!< 编号 */
		int iID;
	
	
		/*!< 名称 */
		string sName;
	
	
		/*!< 行动 */
		vector< int > veciAction_id;
	

};

class MapConfig : public Singleton<MapConfig>
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
	const Map *GetMapByID(const int iID);
	
	
	/**
	 * @brief 通过名称获取配置
	 */
	const Map *GetMapByName(const string sName);
	
private:
	/*!< 配置数据 */
    vector<Map> m_vecRecords;
};

#endif //__MAP_LOADER_H__
