

#include "ItemConfigLoader.h"

#include "dataconfig_itemconfig.pb.h"
#include "Platform.h"

bool ItemConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_itemconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::ItemConfigArray ayItemConfig;
	if (!ayItemConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayItemConfig.items_size(); ++i)
	{
	    ItemConfig oItemConfig;
		
		oItemConfig.iID = (int)(ayItemConfig.items(i).id());
		oItemConfig.eType = (ItemType)(ayItemConfig.items(i).type());

		oItemConfig.sName = platform::UTF_82ASCII(ayItemConfig.items(i).name());
		oItemConfig.sDescription = platform::UTF_82ASCII(ayItemConfig.items(i).description());



        m_vecRecords.push_back(oItemConfig);
	}
	
	return true;
}
const vector<ItemConfig> &ItemConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const ItemConfig *ItemConfigLoader::GetItemConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const ItemConfig *ItemConfigLoader::GetItemConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ItemConfig *ItemConfigLoader::GetItemConfigByType(const ItemType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const ItemConfig *ItemConfigLoader::GetItemConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ItemConfig *ItemConfigLoader::GetItemConfigByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
			return &m_vecRecords[i];
	}
	return NULL;
}
	
