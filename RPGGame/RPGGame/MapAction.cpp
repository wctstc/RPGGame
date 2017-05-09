#include "MapAction.h"



MapAction::MapAction()
{
    m_stMapActionData.iID          = 0;
    m_stMapActionData.eType        = MapActionType::MAPACTION_TYPE_NO_MAP;
    m_stMapActionData.sName        = "无动作";
    m_stMapActionData.sDescription = "无动作";
    m_stMapActionData.iPowerCost   = 0;
    m_stMapActionData.iTimeCost    = 0;
    m_stMapActionData.iMaxTime     = 0;
    m_stMapActionData.iRecovery    = 0;
    m_stMapActionData.vMonsterID.clear();
    m_stMapActionData.vDropID.clear();
}


MapAction::~MapAction()
{
}

const MapAction & MapAction::GetNoMapAction()
{
    static MapAction oMapAction;
    return oMapAction;
}

bool MapAction::Init(const MapAction &oMapAction)
{
    m_stMapActionData = oMapAction.m_stMapActionData;
    return true;
}

bool MapAction::Init(
    const int           iID, 
    const MapActionType eType,
    const string        sName,
    const string        sDescription,
    const int           iPowerCost,
    const int           iTimeCost,
    const int           iMaxTime, 
    const int           iRecovery, 
    const vector<int>  &vMonsterID, 
    const vector<int>  &vDropID)
{
    m_stMapActionData.iID          = iID;
    m_stMapActionData.eType        = eType;
    m_stMapActionData.sName        = sName;
    m_stMapActionData.sDescription = sDescription;
    m_stMapActionData.iPowerCost   = iPowerCost;
    m_stMapActionData.iTimeCost    = iTimeCost;
    m_stMapActionData.iMaxTime     = iMaxTime;
    m_stMapActionData.iRecovery    = iRecovery;
    m_stMapActionData.vMonsterID   = vMonsterID;
    m_stMapActionData.vDropID      = vDropID;

    return true;
}
