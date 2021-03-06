

#include "ItemLoader.h"

#include "dataconfig_item.pb.h"
#include "Platform.h"

bool ItemLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_item.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::ITEMArray ayItem;
	if (!ayItem.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayItem.items_size(); ++i)
	{
	    Item oItem;
		
		oItem.iID = (property_type)(ayItem.items(i).id());
		oItem.eType = (property_type)(ayItem.items(i).type());

		oItem.sName = platform::UTF_82ASCII(ayItem.items(i).name());
		oItem.sDescription = platform::UTF_82ASCII(ayItem.items(i).description());



        m_vecRecords.push_back(oItem);
	}
}
	
const Item *ItemLoader::GetItemByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Item *ItemLoader::GetItemByType(const Item::ItemType eType)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].eType == eType)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	
	
const Item *ItemLoader::GetItemByName(const string sName)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sName == sName)
		 return "m_vecRecords[i]
	}
	return NULL;
}
		
const Item *ItemLoader::GetItemByDescription(const string sDescription)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].sDescription == sDescription)
		 return "m_vecRecords[i]
	}
	return NULL;
}
	
