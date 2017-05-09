#ifndef __MAP_H__
#define __MAP_H__

#include "Struct.h"

/**
 * @brief 地图类
 */
class Map
{
public:
    Map();
    ~Map();

public:
    /**
    * @brief 无地图
    */
    static const Map &GetNoMap();

public:
    /**
     * @brief 初始化
     */
    bool Init(const Map &oMap);

    /**
     * @brief 初始化
     */
    bool Init(const int iID, const string sName, const vector<int> &vMapActionID);
public:
    SET_GET(int,         i,ID,         m_stMapData.iID)
    SET_GET(string,      s,Name,       m_stMapData.sName)
    SET_GET(vector<int>&,v,MapActionID,m_stMapData.vMapActionID)
private:
    /**
     * @brief 地图数据结构体
     */
    struct MapData
    {
        /*!< 编号 */
        int iID;

        /*!< 名字 */
        string sName;

        /*!< 行为 */
        vector<int> vMapActionID;
    };
private:
    //*!< 地图数据 */
    MapData m_stMapData;
};


#endif // __MAP_H__

