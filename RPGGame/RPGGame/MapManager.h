#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include "Manager.h"
#include "Singleton.h"
#include "Drop.h"
#include "Monster.h"
#include "MapAction.h"
#include "Map.h"

/**
 * @brief 地图管理
 */
class MapManager :public Manager,public Singleton<MapManager>
{
public:
    MapManager();
    ~MapManager();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();

    /**
     * @brief 保存
     */
    virtual bool Save(const string sFile);

    /**
     * @brief 加载
     */
    virtual bool Load(const string sFile);

public:
    /**
     * @brief 获取掉落
     */
    const Drop &GetDropByID(const int iID);
    
    /**
     * @brief 获取掉落数量
     */
    int GetDropTotalNum()const;

    /**
     * @brief 获取怪物
     */
    const Monster &GetMonsterByID(const int iID);

    /**
     * @brief 获取怪物数量
     */
    int GetMonsterTotalNum();
    
    /**
     * @brief 获取地图动作
     */
    const MapAction &GetMapActionByID(const int iID);
    /**
     * @brief 获取地图数量
     */
    int GetMapActionTotalNum();

    /**
     * @brief 获取地图
     */
    const Map &GetMapByID(const int iID);

    /**
     * @brief 获取地图数量
     */
    int GetMapTotalNum();

public:
    /**
     * @brief 随机野怪
     */
    const Monster &MeetMonster(const int iMapActionID);
private:
    /*!< 遇到的怪物 */
    Monster m_oCurrentMonster;
};




#endif // __MAPMANAGER_H__
