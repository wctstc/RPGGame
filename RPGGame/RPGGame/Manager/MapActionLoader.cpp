#include "MapActionLoader.h"


#include "dataconfig_mapaction.pb.h"

#include "Platform.h"
#include "FileUtil.h"



using dataconfig::MAPACTION;
using dataconfig::MAPACTIONArray;

using platform::UTF_82ASCII;

MapActionLoader::MapActionLoader()
{
}


MapActionLoader::~MapActionLoader()
{
}

bool MapActionLoader::Load()
{
    MAPACTIONArray arrayMapAction;
    if (!GetConfigArray(arrayMapAction))
        return false;

    m_mapMapActions.clear();

    vector<int> vMonster;
    vector<int> vDrop;
    for (int i = 0; i < arrayMapAction.items_size(); ++i)
    {
        vMonster.clear();
        vDrop.clear();

        const MAPACTION *pConfig = &(arrayMapAction.items(i));

        for (int j = 0; j < pConfig->monster_id_size(); ++j)
            vMonster.push_back(pConfig->monster_id(j));

        for (int j = 0; j < pConfig->drop_id_size(); ++j)
            vDrop.push_back(pConfig->drop_id(j));

        MapAction oMapAction;
        if (!oMapAction.Init(
            pConfig->id(),
            static_cast<MapAction::MapActionType>(pConfig->type()),
            UTF_82ASCII(pConfig->name()),
            UTF_82ASCII(pConfig->description()),
            pConfig->power_cost(),
            pConfig->time_cost(),
            pConfig->maxtime(),
            pConfig->recovery(),
            vMonster,
            vDrop))
            return false;

        m_mapMapActions.insert(make_pair(oMapAction.GetID(), oMapAction));
    }

    return true;
}

const MapAction &MapActionLoader::GetMapActionByID(const int iID)const
{
    map<int, MapAction>::const_iterator it = m_mapMapActions.find(iID);
    if (it != m_mapMapActions.end())
        return it->second;
    return MapAction::GetNoMapAction();
}

int MapActionLoader::GetMapActionNum() const
{
    return m_mapMapActions.size();
}
