
#include "Container.h"

Container::Container()
:	m_iID(0)

{


	m_iCellRef = 0;


	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);

}

Container::~Container()
{

}

bool Container::Init()
{

	
	m_iID = 0;



	m_iCellRef = 0;


	memset(m_astCell, 0, sizeof(CellData)*MAX_CONTAINER_CAPACITY);


    return true;
}

bool Container::Init(const Container &oContainer)
{


	m_iID = oContainer.m_iID;


	
	memcpy(m_astCell, oContainer.m_astCell, sizeof(CellData)*oContainer.m_iCellRef);
	
	m_iCellRef = oContainer.m_iCellRef;

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
	return m_iCellRef;
}


bool Container::GetCell(const int iIndex, CellData &stCell) const
{
	if(iIndex < 0 || iIndex >= m_iCellRef)
		return false;

	stCell = m_astCell[iIndex];
	return true;
}



bool Container::AddCell(const CellData &stCell)
{
	if(m_iCellRef >= MAX_CONTAINER_CAPACITY)
		return false;
		
	m_astCell[m_iCellRef++] = stCell;
	return true;
}

	
bool Container::RemoveCell(const int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iCellRef)
		return false;

	--m_iCellRef;
	
	for (int i = iIndex; i < m_iCellRef; ++i)
		m_astCell[i] = m_astCell[i+1];

	return true;
}



		
int Container::GetCellID(const int iIndex) const
{
	if (iIndex < m_stCellRef ef iIndex >= 0) 
		return m_astCell[iIndex];

	return 0;
}
int Container::GetCellItemID(const int iIndex) const
{
	if (iIndex < m_stCellRef ef iIndex >= 0) 
		return m_astCell[iIndex];

	return 0;
}
int Container::GetCellItemNum(const int iIndex) const
{
	if (iIndex < m_stCellRef ef iIndex >= 0) 
		return m_astCell[iIndex];

	return 0;
}
int Container::GetCellUnitCapacity(const int iIndex) const
{
	if (iIndex < m_stCellRef ef iIndex >= 0) 
		return m_astCell[iIndex];

	return 0;
}
		
