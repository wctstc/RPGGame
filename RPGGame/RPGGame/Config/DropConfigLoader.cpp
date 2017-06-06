

#include "DropConfigLoader.h"

#include "dataconfig_dropconfig.pb.h"
#include "Platform.h"

bool DropConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_dropconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[128*1024];
	int iLength = fread(csBuffer, 1, 128*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::DropConfigArray ayDropConfig;
	if (!ayDropConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayDropConfig.items_size(); ++i)
	{
	    DropConfig oDropConfig;
		
		oDropConfig.iID = (int)(ayDropConfig.items(i).id());
		oDropConfig.iItemID = (int)(ayDropConfig.items(i).itemid());
		oDropConfig.iItemNum = (int)(ayDropConfig.items(i).itemnum());




        m_vecRecords.push_back(oDropConfig);
	}
	
	return true;
}
const vector<DropConfig> &DropConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const DropConfig *DropConfigLoader::GetDropConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const DropConfig *DropConfigLoader::GetDropConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const DropConfig *DropConfigLoader::GetDropConfigByItemID(const int iItemID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItemID == iItemID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const DropConfig *DropConfigLoader::GetDropConfigByItemNum(const int iItemNum)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItemNum == iItemNum)
			return &m_vecRecords[i];
	}
	return NULL;
}
	

