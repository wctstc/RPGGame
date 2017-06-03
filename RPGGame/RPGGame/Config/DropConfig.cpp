

#include "DropConfig.h"

#include "dataconfig_drop.pb.h"
#include "Platform.h"

bool DropConfig::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_drop.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[1024*1024];
	int iLength = fread(csBuffer, 1, 1024*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::DROPArray ayDrop;
	if (!ayDrop.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayDrop.items_size(); ++i)
	{
	    Drop oDrop;
		
		oDrop.iID = (int)(ayDrop.items(i).id());
		oDrop.iItem_id = (int)(ayDrop.items(i).item_id());
		oDrop.iItem_num = (int)(ayDrop.items(i).item_num());




        m_vecRecords.push_back(oDrop);
	}
	
	return true;
}
	
const Drop *DropConfig::GetDropByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Drop *DropConfig::GetDropByItem_id(const int iItem_id)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItem_id == iItem_id)
		 return &m_vecRecords[i];
	}
	return NULL;
}
		
const Drop *DropConfig::GetDropByItem_num(const int iItem_num)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItem_num == iItem_num)
		 return &m_vecRecords[i];
	}
	return NULL;
}
	

