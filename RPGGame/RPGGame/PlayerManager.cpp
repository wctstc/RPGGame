#include "PlayerManager.h"
#include "PlayerLoader.h"


PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Init()
{
	//PlayerLoader::GetInstance().Init();

    m_oPlayer.Init(10,10, 10, 10, 1, 1,1,1, 1000);
    m_oPlayer.AddItemToBag(1, 2);
    m_oPlayer.AddItemToBag(2, 3);
    m_oPlayer.AddItemToBag(1, 5);

    m_oPlayer.SetMoney(10000);

	return true;
}

bool PlayerManager::Save(const string sFile)
{
    if (sFile.empty())
        return true;


    FILE *pFile = fopen(sFile.c_str(), "wb");
    if (pFile == NULL)
        return false;


    char csBuffer[10240];
    int iLength = sizeof(csBuffer);

    if (!m_oPlayer.Save(iLength, csBuffer))
        return false;
        
    iLength = fwrite(csBuffer, 1, iLength, pFile);
    if (iLength <= 0)
        return false;

    return true;
}

bool PlayerManager::Load(const string sFile)
{
    if (sFile.empty())
        return true;


    FILE *pFile = fopen(sFile.c_str(), "rb");
    if (pFile == NULL)
        return false;


    char csBuffer[10240];
    int iLength = fread(csBuffer, 1, 10240, pFile);
    if (iLength >= 10000)
        return false;

    if (!m_oPlayer.Load(iLength, csBuffer))
        return false;

    return true;
}

const Bag & PlayerManager::GetBag()
{
	return m_oPlayer.GetBag();
}

bool PlayerManager::AddItemToBag(const int iItemID, const int iNum)
{
    return m_oPlayer.AddItemToBag(iItemID, iNum);
}

bool PlayerManager::ReduceItemFromBag(const int iItemID, const int iNum)
{
    return m_oPlayer.ReduceItemFromBag(iItemID, iNum);
}

bool PlayerManager::Buy(const int iItemID, const int iPrice)
{
//     if (!m_oPlayer.CanAddItemToBag(oGoods.GetItemID(),oGoods.GetAmount()))
//         return false;

    if (!m_oPlayer.ReduceMoney(iPrice))
        return false;

    return m_oPlayer.AddItemToBag(iItemID, 1);
}

bool PlayerManager::Sell(const int iItemID, const int iPrice)
{
    if (!m_oPlayer.ReduceItemFromBag(iItemID, 1))
        return false;

    return m_oPlayer.AddMoney(iPrice);
}

const Player & PlayerManager::GetPlayer()
{
    return m_oPlayer;
}

