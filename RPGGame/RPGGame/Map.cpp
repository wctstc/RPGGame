#include "Map.h"



Map::Map()
{
    m_stMapData.iID = 0;
    m_stMapData.sName = "ÎÞµØÍ¼";
    m_stMapData.vMapActionID.clear();
}


Map::~Map()
{
}

const Map & Map::GetNoMap()
{
    static Map oMap;
    return oMap;
}

bool Map::Init(const Map &oMap)
{
    m_stMapData = oMap.m_stMapData;
    return true;
}

bool Map::Init(const int iID, const string sName, const vector<int> &vMapActionID)
{
    m_stMapData.iID          = iID;
    m_stMapData.sName        = sName;
    m_stMapData.vMapActionID = vMapActionID;
    return true;
}
