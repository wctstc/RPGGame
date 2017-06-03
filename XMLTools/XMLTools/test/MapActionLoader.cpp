

#include "MapActionLoader.h"

#include "dataconfig_mapaction.pb.h"
#include "Platform.h"

bool MapActionLoader::Init()
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
		
		oMapAction.iID = (property_type)(ayMapAction.items(i).id());
		oMapAction.eType = (property_type)(ayMapAction.items(i).type());
		oMapAction.iPower_cost = (property_type)(ayMapAction.items(i).power_cost());
		oMapAction.iTime_cost = (property_type)(ayMapAction.items(i).time_cost());
		oMapAction.iMaxtime = (property_type)(ayMapAction.items(i).maxtime());
		oMapAction.iRecovery = (property_type)(ayMapAction.items(i).recovery());

		oMapAction.sName = platform::UTF_82ASCII(ayMapAction.items(i).name());
		oMapAction.sDescription = platform::UTF_82ASCII(ayMapAction.items(i).description());

		for(int j = 0; j < ayMapAction.items(i).monster_id_size(); ++j)
		{
			oMapAction.veciMonster_id.push_back(ayMapAction.items(i).monster_id());
		}
		for(int j = 0; j < ayMapAction.items(i).drop_id_size(); ++j)
		{
			oMapAction.veciDrop_id.push_back(ayMapAction.items(i).drop_id());
		}


        m_vecRecords.push_back(oMapAction);
	}
}
	
const MapAction *MapActionLoader::GetMapActionByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByType(const MapAction::MapActionType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByPower_cost(const int iPower_cost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iPower_cost == iPower_cost)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByTime_cost(const int iTime_cost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iTime_cost == iTime_cost)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByMaxtime(const int iMaxtime)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxtime == iMaxtime)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByRecovery(const int iRecovery)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iRecovery == iRecovery)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const MapAction *MapActionLoader::GetMapActionByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const MapAction *MapActionLoader::GetMapActionByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
