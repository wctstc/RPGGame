
#include "Container.h"

Container::Container()
:	m_iID(0)

{

#compose_init_ref_implement#

	m_iCellNum = 0;
	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);

}

Container::~Container()
{

}

const Container &Container::GetNoContainer()
{
	static Container oContainer;
	return oContainer;
}

bool Container::Init()
{#parent_init_implement#
	
	m_iID = 0;


#compose_init_ref_implement#

	m_iCellNum = 0;
	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);


    return true;
}

bool Container::Init(const Container &oContainer)
{#parent_init_self_implement#

	m_iID = oContainer.m_iID;


	m_iCellNum = oContainer.m_iCellNum;
	memcpy(m_astCell, oContainer.m_astCell, sizeof(CellData)*oContainer.m_iCellNum);

    return true;
}

string Container::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool Container::FromString(const string sBuffer)
{
    return true;
}


	
int Container::GetCellNum() const
{
	return m_iCellNum;
}


bool Container::GetCell(const int iIndex, CellData &stCell) const
{
	if(iIndex < 0 || iIndex >= m_iCellNum)
		return false;

	stCell = m_astCell[iIndex];
	return true;
}



bool Container::AddCell(const CellData &stCell)
{
	if(m_iCellNum >= MAX_CONTAINER_CAPACITY)
		return false;
		
	m_astCell[m_iCellNum++] = stCell;
	return true;
}

	
bool Container::RemoveCell(const int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iCellNum)
		return false;

	--m_iCellNum;
	
	for (int i = iIndex; i < m_iCellNum; ++i)
		m_astCell[i] = m_astCell[i+1];

	return true;
}

