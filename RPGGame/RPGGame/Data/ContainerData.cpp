
#include "ContainerData.h"

ContainerData::ContainerData()
:m_iID(0)

{


	m_iCellNum = 0;
	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);

}

ContainerData::~ContainerData()
{

}

const ContainerData &ContainerData::GetNoContainerData()
{
	static ContainerData oContainerData;
	return oContainerData;
}

bool ContainerData::Init()
{	
	m_iID = int(0);



	m_iCellNum = 0;
	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);


    return true;
}

bool ContainerData::Init(const ContainerData &oContainerData)
{
	m_iID = oContainerData.m_iID;


	m_iCellNum = oContainerData.m_iCellNum;
	memcpy(m_astCell, oContainerData.m_astCell, sizeof(CellData)*oContainerData.m_iCellNum);

    return true;
}

string ContainerData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool ContainerData::FromString(const string sBuffer)
{
    return true;
}


	
int ContainerData::GetCellNum() const
{
	return m_iCellNum;
}


bool ContainerData::GetCell(const int iIndex, CellData &stCell) const
{
	if(iIndex < 0 || iIndex >= m_iCellNum)
		return false;

	stCell = m_astCell[iIndex];
	return true;
}



bool ContainerData::AddCell(const CellData &stCell)
{
	if(m_iCellNum >= MAX_CONTAINER_CAPACITY)
		return false;
		
	m_astCell[m_iCellNum++] = stCell;
	return true;
}

 
CellData *ContainerData::UseCell(const int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iCellNum)
		return NULL;

	return &m_astCell[iIndex];
}

	
bool ContainerData::RemoveCell(const int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iCellNum)
		return false;

	--m_iCellNum;
	
	for (int i = iIndex; i < m_iCellNum; ++i)
		m_astCell[i] = m_astCell[i+1];

	return true;
}

