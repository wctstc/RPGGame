#include "Map.h"



Map::Map()
{
    m_stMapData.iID = 0;
    m_stMapData.eType = MapType::MAP_TYPE_NO_MAP;
    m_stMapData.iMaxTime = 0;
    m_stMapData.iRecovery = 0;
    m_stMapData.vMonsterID.clear();
    m_stMapData.vDropID.clear();
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

bool Map::Init(
    const int          iID, 
    const MapType      eType, 
    const int          iMaxTime, 
    const int          iRecovery, 
    const vector<int> &vMonsterID, 
    const vector<int> &vDropID)
{
    m_stMapData.iID        = iID;
    m_stMapData.eType      = eType;
    m_stMapData.iMaxTime   = iMaxTime;
    m_stMapData.iRecovery  = iRecovery;
    m_stMapData.vMonsterID = vMonsterID;
    m_stMapData.vDropID    = vDropID;

    return true;
}
