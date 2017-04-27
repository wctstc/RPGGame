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

    m_oPlayer.Init(10, 10, 10, 1, 1);
    m_oPlayer.AddItemToBag(1, 2);
    m_oPlayer.AddItemToBag(2, 3);
    m_oPlayer.AddItemToBag(3, 4);
    m_oPlayer.AddItemToBag(1, 5);

    m_oPlayer.SetMoney(10000);

	return true;
}

const Container & PlayerManager::GetBag()
{
	return m_oPlayer.GetBag();
}

bool PlayerManager::Buy(const Goods &oGoods)
{
    if (!m_oPlayer.CanAddItemToBag(oGoods.GetItemID(),oGoods.GetAmount()))
        return false;

    if (!m_oPlayer.Pay(oGoods.GetPrice()))
        return false;

    return m_oPlayer.AddItemToBag(oGoods.GetItemID(), oGoods.GetAmount());
}

