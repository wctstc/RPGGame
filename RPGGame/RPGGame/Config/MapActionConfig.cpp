

#include "MapActionConfig.h"

#include "dataconfig_mapaction.pb.h"
#include "Platform.h"

bool MapActionConfig::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_mapaction.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MAPACTIONArray ayMapAction;
	if (!ayMapAction.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMapAction.items_size(); ++i)
	{
	    MapAction oMapAction;
		
		oMapAction.iID = (int)(ayMapAction.items(i).id());
		oMapAction.eType = (MapActionType)(ayMapAction.items(i).type());
		oMapAction.iPower_cost = (int)(ayMapAction.items(i).power_cost());
		oMapAction.iTime_cost = (int)(ayMapAction.items(i).time_cost());
		oMapAction.iMaxtime = (int)(ayMapAction.items(i).maxtime());
		oMapAction.iRecovery = (int)(ayMapAction.items(i).recovery());

		oMapAction.sName = platform::UTF_82ASCII(ayMapAction.items(i).name());
		oMapAction.sDescription = platform::UTF_82ASCII(ayMapAction.items(i).description());

		for(int j = 0; j < ayMapAction.items(i).monster_id_size(); ++j)
		{
			oMapAction.veciMonster_id.push_back(ayMapAction.items(i).monster_id(j));
		}
		for(int j = 0; j < ayMapAction.items(i).drop_id_size(); ++j)
		{
			oMapAction.veciDrop_id.push_back(ayMapAction.items(i).drop_id(j));
		}


        m_vecRecords.push_back(oMapAction);
	}
	
	return true;
}
	
const MapAction *MapActionConfig::GetMapActionByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByType(const MapActionType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByPower_cost(const int iPower_cost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iPower_cost == iPower_cost)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByTime_cost(const int iTime_cost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iTime_cost == iTime_cost)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByMaxtime(const int iMaxtime)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxtime == iMaxtime)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByRecovery(const int iRecovery)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iRecovery == iRecovery)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const MapAction *MapActionConfig::GetMapActionByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionConfig::GetMapActionByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
