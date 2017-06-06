

#include "MapActionConfigLoader.h"

#include "dataconfig_mapactionconfig.pb.h"
#include "Platform.h"

bool MapActionConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_mapactionconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[128*1024];
	int iLength = fread(csBuffer, 1, 128*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MapActionConfigArray ayMapActionConfig;
	if (!ayMapActionConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMapActionConfig.items_size(); ++i)
	{
	    MapActionConfig oMapActionConfig;
		
		oMapActionConfig.iID = (int)(ayMapActionConfig.items(i).id());
		oMapActionConfig.eType = (MapActionType)(ayMapActionConfig.items(i).type());
		oMapActionConfig.iPowerCost = (int)(ayMapActionConfig.items(i).powercost());
		oMapActionConfig.iTimeCost = (int)(ayMapActionConfig.items(i).timecost());
		oMapActionConfig.iMaxtime = (int)(ayMapActionConfig.items(i).maxtime());
		oMapActionConfig.iRecovery = (int)(ayMapActionConfig.items(i).recovery());

		oMapActionConfig.sName = platform::UTF_82ASCII(ayMapActionConfig.items(i).name());
		oMapActionConfig.sDescription = platform::UTF_82ASCII(ayMapActionConfig.items(i).description());

		for(int j = 0; j < ayMapActionConfig.items(i).monsterid_size(); ++j)
		{
			oMapActionConfig.veciMonsterID.push_back(ayMapActionConfig.items(i).monsterid(j));
		}
		for(int j = 0; j < ayMapActionConfig.items(i).dropid_size(); ++j)
		{
			oMapActionConfig.veciDropID.push_back(ayMapActionConfig.items(i).dropid(j));
		}


        m_vecRecords.push_back(oMapActionConfig);
	}
	
	return true;
}
const vector<MapActionConfig> &MapActionConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByType(const MapActionType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByPowerCost(const int iPowerCost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iPowerCost == iPowerCost)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByTimeCost(const int iTimeCost)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iTimeCost == iTimeCost)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByMaxtime(const int iMaxtime)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iMaxtime == iMaxtime)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByRecovery(const int iRecovery)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iRecovery == iRecovery)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const MapActionConfig *MapActionConfigLoader::GetMapActionConfigByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
