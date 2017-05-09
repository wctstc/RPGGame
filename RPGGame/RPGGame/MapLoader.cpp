#include "MapLoader.h"

#include "dataconfig_map.pb.h"
#include "Platform.h"

using dataconfig::MAPArray;
using dataconfig::MAP;

using platform::UTF_82ASCII;

MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

bool MapLoader::Load()
{
    MAPArray arrayMap;

    if (!GetConfigArray(arrayMap))
        return false;

    m_mapMaps.clear();
    vector<int> vMapActionID;
    for (int i = 0; i < arrayMap.items_size(); ++i)
    {
        vMapActionID.clear();

        const MAP &pConfig = arrayMap.items(i);

        for (int j = 0; j < pConfig.action_id_size(); ++j)
            vMapActionID.push_back(pConfig.action_id(j));

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
