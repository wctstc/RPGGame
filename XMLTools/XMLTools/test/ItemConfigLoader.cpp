

#include "ItemConfigLoader.h"

#include "dataconfig_itemconfig.pb.h"
#include "Platform.h"

using dataconfig::ITEMCONFIG;
using dataconfig::ITEMCONFIGArray;

using platform::UTF_82ASCII;

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
	
	ITEMCONFIGArray ayItemConfig;
	if (!ayItemConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	for(int i = 0;i < ayItemConfig.itemconfigs_size(); ++i)
	{
	    ItemConfig oItemConfig;
		
		oItemConfig.eType = ayItemConfig.itemconfigs(i).type();		oItemConfig.sName = ayItemConfig.itemconfigs(i).name();		oItemConfig.sDescription = ayItemConfig.itemconfigs(i).description();

        m_vecRecords.push_back(oItemConfig);
	}
}
	
const ItemConfig *ItemConfigLoader::GetItemConfigByType(const ItemType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const ItemConfig *ItemConfigLoader::GetItemConfigByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const ItemConfig *ItemConfigLoader::GetItemConfigByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
