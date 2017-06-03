#include "MapLoader.h"

#include "dataconfig_mapconfig.pb.h"
#include "Platform.h"

using dataconfig::MapConfigArray;
using dataconfig::MapConfig;

using platform::UTF_82ASCII;

MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

bool MapLoader::Load()
{
    MapConfigArray arrayMap;

    if (!GetConfigArray(arrayMap))
        return false;

    m_mapMaps.clear();
    vector<int> vMapActionID;
    for (int i = 0; i < arrayMap.items_size(); ++i)
    {
        vMapActionID.clear();

        const MapConfig &pConfig = arrayMap.items(i);

        for (int j = 0; j < pConfig.actionid_size(); ++j)
            vMapActionID.push_back(pConfig.actionid(j));

        Map oMap;
        if (!oMap.Init(pConfig.id(), UTF_82ASCII(pConfig.name()), vMapActionID))
            return false;

        m_mapMaps.insert(make_pair(oMap.GetID(), oMap));
    }


    return true;
}

int MapLoader::GetMapNum() const
{
    return m_mapMaps.size();
}

const Map & MapLoader::GetMapByID(const int iID)const
{
    map<int, Map>::const_iterator it = m_mapMaps.find(iID);
    if (it != m_mapMaps.end())
        return it->second;
    return Map::GetNoMap();
}
