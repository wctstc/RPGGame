#ifndef __MAPMANAGER_H__
#define __MAPMANAGER_H__

#include "Manager.h"

/**
 * @brief 地图管理
 */
class MapManager :public Manager
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
    

private:

};




#endif // __MAPMANAGER_H__
