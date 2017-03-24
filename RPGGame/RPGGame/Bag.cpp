#include "Bag.h"



Bag::Bag()
{
}


Bag::~Bag()
{
}

int Bag::GetItemsNumber()const
{
	return m_vItems.size();
}

bool Bag::AddItem(const Item& oItem)
{
	m_vItems.push_back(oItem);
	return true;
}

unsigned int Bag::GetItemID(int iIndex)const
{
	if (iIndex > 0 && iIndex < m_vItems.size())
		return m_vItems[iIndex].GetID();
	return 0;
}

const string Bag::GetItemDescription(int iIndex)const
{
	if (iIndex > 0 && iIndex < m_vItems.size())
		return m_vItems[iIndex].GetDescription();
	return "";
}
