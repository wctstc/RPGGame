#include "HomeManager.h"



HomeManager::HomeManager()
{
}


HomeManager::~HomeManager()
{
}

bool HomeManager::Init()
{
    m_oStorage.Init(1, 50);
    AddToStorage(1, 2);
    AddToStorage(2, 3);
    AddToStorage(3, 7);
    AddToStorage(4, 10);

    return true;
}

bool HomeManager::Save(const string sFile)
{
    return true;
}

bool HomeManager::Load(const string sFile)
{
    return true;
}

const Bag & HomeManager::GetStorage()
{
    return m_oStorage;
}

bool HomeManager::AddToStorage(const int iItemID, const int iItemNum)
{
    return m_oStorage.Add(iItemID, iItemNum);
}

int HomeManager::RemoveFromStorage(const int iItemID)
{
    int iNum = m_oStorage.GetItemNumByItemID(iItemID);

    if (iNum != 0)
        m_oStorage.Reduce(iItemID, iNum);

    return iNum;
}
