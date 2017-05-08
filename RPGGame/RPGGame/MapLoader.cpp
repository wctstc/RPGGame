#include "MapLoader.h"


#include "dataconfig_map.pb.h"

#include "Platform.h"
#include "FileUtil.h"



using dataconfig::MAP;
using dataconfig::MAPArray;

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

    vector<int> vMonster;
    vector<int> vDrop;
    for (int i = 0; i < arrayMap.items_size(); ++i)
    {
        vMonster.clear();
        vDrop.clear();

        const MAP *pConfig = &(arrayMap.items(i));

        for (int j = 0; j < pConfig->monster_id_size(); ++j)
            vMonster.push_back(pConfig->monster_id(j));

        for (int j = 0; j < pConfig->drop_id_size(); ++j)
            vDrop.push_back(pConfig->drop_id(j));

        Map oMap;
        if (!oMap.Init(
            pConfig->id(),
            static_cast<Map::MapType>(pConfig->type()),
            pConfig->maxtime(),
            pConfig->recovery(),
            vMonster,
            vDrop))
            return false;

        m_mapMaps.insert(make_pair(oMap.GetID(), oMap));
    }

    return true;
}

const Map &MapLoader::GetMapByID(const int iID)const
{
    map<int, Map>::const_iterator it = m_mapMaps.find(iID);
    if (it != m_mapMaps.end())
        return it->second;
    return Map::GetNoMap();
}
