
#include "ItemData.h"

ItemData::ItemData()
:	m_iID(0)
,	m_eType(ItemData::ITEM_TYPE_NO)

{
	
	m_iNameLen = 0;
	memset(m_Name, 0, MAX_NAME_SIZE);
		
	m_iDescriptionLen = 0;
	memset(m_Description, 0, MAX_DESCRIPTION_SIZE);
	


}

ItemData::~ItemData()
{

}

bool ItemData::Init()
{

	
	m_iID = 0;
	
	m_eType = ItemData::ITEM_TYPE_NO;

	
	m_iNameLen = 0;
	memset(m_Name, 0, MAX_NAME_SIZE);
		
	m_iDescriptionLen = 0;
	memset(m_Description, 0, MAX_DESCRIPTION_SIZE);
	



    return true;
}

bool ItemData::Init(const ItemData &oItemData)
{


	m_iID = oItemData.m_iID;

	m_eType = oItemData.m_eType;


    return true;
}

string ItemData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool ItemData::FromString(const string sBuffer)
{
    return true;
}

const char *ItemData::GetName() const
{
	return m_Name;
}
	
const int ItemData::GetNameLen() const
{
	return m_iNameLen;
}

const char *ItemData::GetDescription() const
{
	return m_Description;
}
	
const int ItemData::GetDescriptionLen() const
{
	return m_iDescriptionLen;
}


bool ItemData::SetName(const char *pName, const int iLen)
{
	if (pName == NULL || iLen >= MAX_NAME_SIZE)
		return false;
		
	memcpy(m_Name, pName, iLen);
	m_iNameLen = iLen;
	
	return true;
}

bool ItemData::SetDescription(const char *pDescription, const int iLen)
{
	if (pDescription == NULL || iLen >= MAX_DESCRIPTION_SIZE)
		return false;
		
	memcpy(m_Description, pDescription, iLen);
	m_iDescriptionLen = iLen;
	
	return true;
}








