#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__


#include "Singleton.h"
#include "Loader.h"
#include "Map.h"

/**
 * @brief 地图配置加载
 */
class MapLoader : public Loader, public Singleton<MapLoader>
{
public:
    MapLoader();
    ~MapLoader();

public:   
    /**
     * @brief 加载配置文件
     */
    virtual bool Load() override;

public:
    /**
     * @brief 获取数量
     */
    int GetMapNum()const;

    /**
     * @brief 获取配置
     */
    const Map &GetMapByID(const int iID)const;

private:
    /*!< 编号与地图映射 */
    map<int, Map> m_mapMaps;
};



#endif // __MAPLOADER_H__


