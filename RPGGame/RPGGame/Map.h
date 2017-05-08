#ifndef __MAP_H__
#define __MAP_H__

#include "Struct.h"

/**
 * @brief 地图
 */
class Map
{
public:
    /**
     * @brief 地图类型
     */
    enum MapType
    {
        /*!< 无地图 */
        MAP_TYPE_NO_MAP = 0,

        /*!< 资源地图 */
        MAP_TYPE_RESOURCE = 1,

        /*!< 怪物地图 */
        MAP_TYPE_MONSTER = 2,
    };
public:
    Map();
    virtual ~Map();
public:
    /**
    * @brief 无地图
    */
    static const Map &GetNoMap();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init(const Map &oMap);

    /**
    * @brief 初始化
    */
    virtual bool Init(
        const int iID, 
        const Map::MapType eType, 
        const int iMaxTime,
        const int iRecovery,
        const vector<int> &vMonsterID,
        const vector<int> &vDropID);


public:
    SET_GET(int,          i, ID,        m_stMapData.iID)
    SET_GET(Map::MapType, e, Type,      m_stMapData.eType)
    SET_GET(int,          i, MaxTime,   m_stMapData.iMaxTime)
    SET_GET(int,          i, Recovery,  m_stMapData.iRecovery)
    SET_GET(vector<int>&, v, MonsterID, m_stMapData.vMonsterID)
    SET_GET(vector<int>&, v, DropID,    m_stMapData.vDropID)

private:
    /**
     * @brief 地图数据结构体
     */
    struct MapData
    {
        /*!< 编号 */
        int iID;

        /*!< 类型 */
        Map::MapType eType;

        /*!< 最大次数 */
        int iMaxTime;

        /*!< 恢复速度 */
        int iRecovery;

        /*!< 怪物编号 */
        vector<int> vMonsterID;

        /*!< 掉落编号 */
        vector<int> vDropID;
    };
private:
    /*!< 地图数据 */
    MapData m_stMapData;
};


#endif // __MAP_H__
