

#include "FrameConfigLoader.h"

#include "dataconfig_frameconfig.pb.h"
#include "Platform.h"

bool FrameConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_frameconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::FrameConfigArray ayFrameConfig;
	if (!ayFrameConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayFrameConfig.items_size(); ++i)
	{
	    FrameConfig oFrameConfig;
		
		oFrameConfig.iID = (int)(ayFrameConfig.items(i).id());
		oFrameConfig.iHandleID = (int)(ayFrameConfig.items(i).handleid());

		oFrameConfig.sName = platform::UTF_82ASCII(ayFrameConfig.items(i).name());
		oFrameConfig.sDescription = platform::UTF_82ASCII(ayFrameConfig.items(i).description());



		for (int j = 0; j < ayFrameConfig.items(i).option_size(); ++j)
		{
			Option stOption;

			stOption.iNotify = (int)(ayFrameConfig.items(i).option(j).notify());
			stOption.iFrameID = (int)(ayFrameConfig.items(i).option(j).frameid());

			stOption.sDescription = platform::UTF_82ASCII(ayFrameConfig.items(i).option(j).description());

			oFrameConfig.vecOption.push_back(stOption);
		}

        m_vecRecords.push_back(oFrameConfig);
	}
	
	return true;
}
const vector<FrameConfig> &FrameConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const FrameConfig *FrameConfigLoader::GetFrameConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const FrameConfig *FrameConfigLoader::GetFrameConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const FrameConfig *FrameConfigLoader::GetFrameConfigByHandleID(const int iHandleID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iHandleID == iHandleID)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const FrameConfig *FrameConfigLoader::GetFrameConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const FrameConfig *FrameConfigLoader::GetFrameConfigByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
