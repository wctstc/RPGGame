#ifndef __MAPACTIONLOADER_H__
#define __MAPACTIONLOADER_H__

#include <map>

#include "Singleton.h"

#include "Loader.h"
#include "MapAction.h"

using std::map;
using std::make_pair;

/**
 * @brief 地图行为配置加载
 */
class MapActionLoader :public Singleton<MapActionLoader>,public Loader
{
public:
    MapActionLoader();
    ~MapActionLoader();
public:
    /**
     * @brief 加载配置文件
     */
    virtual bool Load() override;

public:
    /**
     * @brief 通过编号获取地图行为
     */
    const MapAction &GetMapActionByID(const int iID)const;

    /**
     * @brief 获取地图行为数量
     */
    int GetMapActionNum()const;
private:
    /*!< 编号与地图行为映射 */
    map<int, MapAction> m_mapMapActions;
};


#endif // __MAPACTIONLOADER_H__


