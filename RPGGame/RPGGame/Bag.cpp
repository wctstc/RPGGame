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

bool Bag::RemoveItem(const int iIndex, Item &oItem)
{
	if (iIndex < 0 || iIndex >= m_vItems.size())
		return false;

	oItem = m_vItems[iIndex];

	for (int i = iIndex; i < m_vItems.size()-1; ++i)
		m_vItems[i] = m_vItems[i + 1];
	m_vItems.pop_back();

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
	if (iIndex >= 0 && iIndex < m_vItems.size())
		return m_vItems[iIndex].GetDescription();
	return "";
}
