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

bool MapLoader::Init()
{
    string sFile = "proto/data/dataconfig_map.data";

    char csBuffer[10240];
    int iLength = sizeof(csBuffer);
    iLength = FileUtil::LoadFileWithBinary(sFile, csBuffer, iLength);

    if (iLength <= 0)
        return false;
    
    MAPArray arrayMap;
    if (!arrayMap.ParseFromArray(csBuffer, iLength))
        return false;


    vector<int> vMonster;
    vector<int> vDrop;
    const MAP *pConfig;
    for (int i = 0; i < arrayMap.items_size(); ++i)
    {
        vMonster.clear();
        vDrop.clear();

        pConfig = &(arrayMap.items(i));

        for (int j = 0; j < pConfig->monster_size(); ++j)
            vMonster.push_back(pConfig->monster(j));

        for (int j = 0; j < pConfig->drop_size(); ++j)
            vDrop.push_back(pConfig->drop(j));

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
