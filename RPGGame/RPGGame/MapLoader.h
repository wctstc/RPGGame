#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__

#include "Singleton.h"

#include <map>

#include "Map.h"

using std::map;
using std::make_pair;

/**
 * @brief 地图配置加载
 */
class MapLoader :public Singleton<MapLoader>
{
public:
    MapLoader();
    ~MapLoader();
public:

    /**
    * @brief 初始化
    */
    bool Init();

private:
    map<int, Map> m_mapMaps;
};


#endif // __MAPLOADER_H__


