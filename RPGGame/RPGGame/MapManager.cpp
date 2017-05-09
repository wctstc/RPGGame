#include "MapManager.h"

#include "Platform.h"

#include "MapLoader.h"
#include "MapActionLoader.h"
#include "MonsterLoader.h"
#include "DropLoader.h"


#define g_MapLoader       MapLoader::GetInstance()
#define g_MapActionLoader MapActionLoader::GetInstance()
#define g_DropLoader      DropLoader::GetInstance()
#define g_MonsterLoader   MonsterLoader::GetInstance()

MapManager::MapManager()
{
}


MapManager::~MapManager()
{
}

bool MapManager::Init()
{
    if (!g_DropLoader.Init("proto/data/dataconfig_drop.data"))
        return false;
    if (!g_MonsterLoader.Init("proto/data/dataconfig_monster.data"))
        return false;
    if (!g_MapActionLoader.Init("proto/data/dataconfig_mapaction.data"))
        return false;
    if (!g_MapLoader.Init("proto/data/dataconfig_map.data"))
        return false;
    return true;
}

bool MapManager::Save(const string sFile)
{
    return true;
}

bool MapManager::Load(const string sFile)
{
    return true;
}

const Drop & MapManager::GetDropByID(const int iID)
{
    return g_DropLoader.GetDropByID(iID);
}

int MapManager::GetDropTotalNum() const
{
    return g_DropLoader.GetDropNum();
}

const Monster &MapManager::GetMonsterByID(const int iID)
{
    return g_MonsterLoader.GetMonsterByID(iID);
}

int MapManager::GetMonsterTotalNum()
{
    return g_MonsterLoader.GetMonsterNum();
}

const MapAction & MapManager::GetMapActionByID(const int iID)
{
    return g_MapActionLoader.GetMapActionByID(iID);
}

int MapManager::GetMapActionTotalNum()
{
    return g_MapActionLoader.GetMapActionNum();
}

const Map & MapManager::GetMapByID(const int iID)
{
    return g_MapLoader.GetMapByID(iID);
}

int MapManager::GetMapTotalNum()
{
    return g_MapLoader.GetMapNum();
}

const Monster & MapManager::MeetMonster(const int iMapActionID)
{
    const MapAction &oMapAction = g_MapActionLoader.GetMapActionByID(iMapActionID);
    if (&oMapAction == &MapAction::GetNoMapAction())
        return Monster::GetNoMonster();

    const vector<int> vMonsterIDs = oMapAction.GetMonsterID();

    int iRand = platform::Rank(vMonsterIDs.size());

    m_oCurrentMonster = g_MonsterLoader.GetMonsterByID(iRand);

    return m_oCurrentMonster;

}
