

#include "ShopConfigLoader.h"

#include "dataconfig_shopconfig.pb.h"
#include "Platform.h"

bool ShopConfigLoader::Init()
{
	FILE *pFile;
	pFile = fopen("proto/data/dataconfig_shopconfig.data", "rb");
	
	if (pFile == NULL)
		return false;
	
	char csBuffer[128*1024];
	int iLength = fread(csBuffer, 1, 128*1024, pFile);

	if (iLength <= 0)
	    return false;
	
	dataconfig::ShopConfigArray ayShopConfig;
	if (!ayShopConfig.ParseFromArray(csBuffer, iLength))
	    return false;
	
	m_vecRecords.clear();
	for(int i = 0;i < ayShopConfig.items_size(); ++i)
	{
	    ShopConfig oShopConfig;
		
		oShopConfig.iID = (int)(ayShopConfig.items(i).id());
		oShopConfig.iItemID = (int)(ayShopConfig.items(i).itemid());
		oShopConfig.iItemNum = (int)(ayShopConfig.items(i).itemnum());
		oShopConfig.iPrice = (int)(ayShopConfig.items(i).price());
		oShopConfig.iDiscount = (int)(ayShopConfig.items(i).discount());




        m_vecRecords.push_back(oShopConfig);
	}
	
	return true;
}
const vector<ShopConfig> &ShopConfigLoader::GetAllConfig()
{
	return m_vecRecords;
}
const ShopConfig *ShopConfigLoader::GetShopConfigByIndex(const unsigned int uIndex)
{
	if (uIndex <= m_vecRecords.size())
	{
		return &m_vecRecords[uIndex];
	}
	return NULL;
}
	
const ShopConfig *ShopConfigLoader::GetShopConfigByID(const int iID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iID == iID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ShopConfig *ShopConfigLoader::GetShopConfigByItemID(const int iItemID)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItemID == iItemID)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ShopConfig *ShopConfigLoader::GetShopConfigByItemNum(const int iItemNum)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iItemNum == iItemNum)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ShopConfig *ShopConfigLoader::GetShopConfigByPrice(const int iPrice)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iPrice == iPrice)
			return &m_vecRecords[i];
	}
	return NULL;
}
		
const ShopConfig *ShopConfigLoader::GetShopConfigByDiscount(const int iDiscount)
{
    for(size_t i = 0; i < m_vecRecords.size(); ++i)
	{
	     if (m_vecRecords[i].iDiscount == iDiscount)
			return &m_vecRecords[i];
	}
	return NULL;
}
	

