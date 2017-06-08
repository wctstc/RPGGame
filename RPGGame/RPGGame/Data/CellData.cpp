
#include "CellData.h"

CellData::CellData()
:m_iID(0)
,m_iItemID(0)
,m_iItemNum(0)
,m_iUnitCapacity(0)

{


}

CellData::~CellData()
{

}

const CellData &CellData::GetNoCellData()
{
	static CellData oCellData;
	return oCellData;
}

bool CellData::Init()
{	
	m_iID = int(0);
	
	m_iItemID = int(0);
	
	m_iItemNum = int(0);
	
	m_iUnitCapacity = int(0);




    return true;
}

bool CellData::Init(const CellData &oCellData)
{
	m_iID = oCellData.m_iID;

	m_iItemID = oCellData.m_iItemID;

	m_iItemNum = oCellData.m_iItemNum;

	m_iUnitCapacity = oCellData.m_iUnitCapacity;


    return true;
}

string CellData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool CellData::FromString(const string sBuffer)
{
    return true;
}







