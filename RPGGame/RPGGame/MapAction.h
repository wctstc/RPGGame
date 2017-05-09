#ifndef __MAPACTION_H__
#define __MAPACTION_H__

#include "Struct.h"

/**
 * @brief 地图行为类
 */
class MapAction
{
public:
    /**
     * @brief 地图行为类型
     */
    enum MapActionType
    {
        /*!< 无行为 */
        MAPACTION_TYPE_NO_MAP = 0,

        /*!< 资源相关行为 */
        MAPACTION_TYPE_RESOURCE = 1,

        /*!< 怪物相关行为 */
        MAPACTION_TYPE_MONSTER = 2,
    };
public:
    MapAction();
    virtual ~MapAction();
public:
    /**
    * @brief 无地图行为
    */
    static const MapAction &GetNoMapAction();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init(const MapAction &oMapAction);

    /**
     * @brief 初始化
     */
    virtual bool Init(
        const int iID,
        const MapAction::MapActionType eType,
        const string sName,
        const string sDescription,
        const int iPowerCost,
        const int iTimeCost,
        const int iMaxTime,
        const int iRecovery,
        const vector<int> &vMonsterID,
        const vector<int> &vDropID);


public:
    SET_GET(int,          i, ID,          m_stMapActionData.iID)
    SET_GET(MapAction::MapActionType, e, Type, m_stMapActionData.eType)
    SET_GET(string,       s, Name,        m_stMapActionData.sName)
    SET_GET(string,       s, Description, m_stMapActionData.sDescription)
    SET_GET(int,          i, PowerCost,   m_stMapActionData.iPowerCost)
    SET_GET(int,          i, TimeCost,    m_stMapActionData.iTimeCost)
    SET_GET(int,          i, MaxTime,     m_stMapActionData.iMaxTime)
    SET_GET(int,          i, Recovery,    m_stMapActionData.iRecovery)
    SET_GET(vector<int>&, v, MonsterID,   m_stMapActionData.vMonsterID)
    SET_GET(vector<int>&, v, DropID,      m_stMapActionData.vDropID)

private:
    /**
     * @brief 地图行为数据结构体
     */
    struct MapActionData
    {
        /*!< 编号 */
        int iID;

        /*!< 类型 */
        MapAction::MapActionType eType;

        /*!< 名字 */
        string sName;

        /*!< 描述 */
        string sDescription;

        /*!< 消耗体力值 */
        int iPowerCost;

        /*!< 消耗时间值 */
        int iTimeCost;

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
    /*!< 地图行为数据 */
    MapActionData m_stMapActionData;
};


#endif // __MAPACTION_H__
