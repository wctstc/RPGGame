

#include "MapConfigLoader.h"

#include "dataconfig_mapconfig.pb.h"
#include "Platform.h"

bool MapConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_mapconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MapConfigArray ayMapConfig;
	if (!ayMapConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMapConfig.items_size(); ++i)
	{
	    MapConfig oMapConfig;
		
		oMapConfig.iID = (int)(ayMapConfig.items(i).id());

		oMapConfig.sName = platform::UTF_82ASCII(ayMapConfig.items(i).name());

		for(int j = 0; j < ayMapConfig.items(i).actionid_size(); ++j)
		{
			oMapConfig.veciActionID.push_back(ayMapConfig.items(i).actionid(j));
		}


        m_vecRecords.push_back(oMapConfig);
	}
	
	return true;
}
const vector<MapConfig> &MapConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const MapConfig *MapConfigLoader::GetMapConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const MapConfig *MapConfigLoader::GetMapConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const MapConfig *MapConfigLoader::GetMapConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
