#include "MapActionLoader.h"


#include "dataconfig_mapactionconfig.pb.h"

#include "Platform.h"
#include "FileUtil.h"



using dataconfig::MapActionConfig;
using dataconfig::MapActionConfigArray;

using platform::UTF_82ASCII;

MapActionLoader::MapActionLoader()
{
}


MapActionLoader::~MapActionLoader()
{
}

bool MapActionLoader::Load()
{
    MapActionConfigArray arrayMapAction;
    if (!GetConfigArray(arrayMapAction))
        return false;

    m_mapMapActions.clear();

    vector<int> vMonster;
    vector<int> vDrop;
    for (int i = 0; i < arrayMapAction.items_size(); ++i)
    {
        vMonster.clear();
        vDrop.clear();

        const MapActionConfig *pConfig = &(arrayMapAction.items(i));

        for (int j = 0; j < pConfig->monsterid_size(); ++j)
            vMonster.push_back(pConfig->monsterid(j));

        for (int j = 0; j < pConfig->dropid_size(); ++j)
            vDrop.push_back(pConfig->dropid(j));

        MapAction oMapAction;
        if (!oMapAction.Init(
            pConfig->id(),
            static_cast<MapAction::MapActionType>(pConfig->type()),
            UTF_82ASCII(pConfig->name()),
            UTF_82ASCII(pConfig->description()),
            pConfig->powercost(),
            pConfig->timecost(),
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
