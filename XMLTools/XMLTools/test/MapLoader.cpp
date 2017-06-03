

#include "MapLoader.h"

#include "dataconfig_map.pb.h"
#include "Platform.h"

bool MapLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_map.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::MAPArray ayMap;
	if (!ayMap.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayMap.items_size(); ++i)
	{
	    Map oMap;
		
		oMap.iID = (property_type)(ayMap.items(i).id());

		oMap.sName = platform::UTF_82ASCII(ayMap.items(i).name());

		for(int j = 0; j < ayMap.items(i).action_id_size(); ++j)
		{
			oMap.veciAction_id.push_back(ayMap.items(i).action_id());
		}


        m_vecRecords.push_back(oMap);
	}
}
	
const Map *MapLoader::GetMapByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const Map *MapLoader::GetMapByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
