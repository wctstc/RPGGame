#include "PlayerManager.h"



PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}

bool PlayerManager::Init()
{
    m_oPlayer.Init();

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
    const int iLength = sizeof(csBuffer);
    int iLeft = sizeof(csBuffer);
    int iUsed = 0;

    if (!m_oPlayer.Save(iLeft, csBuffer))
        return false;

    iUsed += iLeft;
    iLeft = iLength - iUsed;
    if (!m_oBag.Save(iLeft, csBuffer+iUsed))
        return false;
        
    iUsed += iLeft;
    iUsed = fwrite(csBuffer, 1, iUsed, pFile);
    if (iUsed <= 0)
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

    int iLeft = iLength;
    int iUsed = 0;
    if (!m_oPlayer.Load(iLeft, csBuffer))
        return false;

    iUsed = iLeft;
    iLeft = iLength - iUsed;

    if (!m_oBag.Load(iLeft, csBuffer+iUsed))
        return false;

    return true;
}

const ContainerData & PlayerManager::GetBag()const
{
    return m_oPlayer.GetPlayerData().GetBag();
}

bool PlayerManager::AddToBag(const int iItemID, const int iNum)
{
    return m_oPlayer.UseBag.Add(iItemID, iNum);
}

bool PlayerManager::ReduceFromBag(const int iItemID, const int iNum)
{
    return m_oPlayer.UseBag().Remove(iItemID, iNum);
}

bool PlayerManager::Buy(const int iItemID, const int iPrice)
{
    if (!m_oPlayer.ReduceMoney(iPrice))
        return false;

    if (!m_oPlayer.UseBag().Add(iItemID, 1))
    {
        m_oPlayer.AddMoney(iPrice);
        return false;
    }



    return true;
}

bool PlayerManager::Sell(const int iItemID, const int iPrice)
{
    if (!m_oBag.Reduce(iItemID, 1))
        return false;

    if (!m_oPlayer.AddMoney(iPrice))
    {
        m_oBag.Add(iItemID, 1);
        return false;
    }

    return true;
}

void PlayerManager::Attack(Actor &oActor)
{
    int iDamage = m_oPlayer.Attack();

    oActor.Defance(iDamage);
    if (!oActor.IsDie())
    {
        iDamage = oActor.Attack();
        m_oPlayer.Defance(iDamage);
    }
}

const Player & PlayerManager::GetPlayer()
{
    return m_oPlayer;
}

