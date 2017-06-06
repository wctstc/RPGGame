#include "HomeManager.h"
#include "FileUtil.h"


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
    if (sFile.empty())
        return true;

    FILE *pFile = fopen(sFile.c_str(), "wb");
    if (pFile == NULL)
        return false;


    char csBuffer[10240];
    int  iLength = sizeof(csBuffer);

    if (!m_oStorage.Save(iLength, csBuffer))
        return false;

    if (FileUtil::SaveFileWithBinary(sFile, csBuffer, iLength) <= 0)
        return false;

    return true;
}

bool HomeManager::Load(const string sFile)
{
    char csBuffer[10240];
    int iLength = sizeof(csBuffer);

    iLength = FileUtil::LoadFileWithBinary(sFile, csBuffer, iLength);

    if (iLength <= 0)
        return false;

    if (!m_oStorage.Load(iLength, csBuffer))
        return false;

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

bool HomeManager::ReduceFromStorage(const int iItemID, const int iItemNum)
{
    return m_oStorage.Reduce(iItemID, iItemNum);
}

int HomeManager::RemoveFromStorage(const int iItemID)
{
    int iNum = m_oStorage.GetItemNumByItemID(iItemID);

    if (iNum > 0 && m_oStorage.Reduce(iItemID, iNum))
        return iNum;
    return 0;
}
