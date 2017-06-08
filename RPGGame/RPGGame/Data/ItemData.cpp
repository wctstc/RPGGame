
#include "ItemData.h"

ItemData::ItemData()
:m_iID(0)
,m_iNum(0)

{


}

ItemData::~ItemData()
{

}

const ItemData &ItemData::GetNoItemData()
{
	static ItemData oItemData;
	return oItemData;
}

bool ItemData::Init()
{	
	m_iID = int(0);
	
	m_iNum = int(0);




    return true;
}

bool ItemData::Init(const ItemData &oItemData)
{
	m_iID = oItemData.m_iID;

	m_iNum = oItemData.m_iNum;


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







