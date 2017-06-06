#include "ShopManager.h"



ShopManager::ShopManager()
{
}


ShopManager::~ShopManager()
{
}

bool ShopManager::Init()
{
    m_oShop.Init();
    return true;
}

const Shop & ShopManager::GetShop()
{
    return m_oShop;
}

bool ShopManager::BuyGoods(const int iIndex, const int iNum)
{
    return m_oShop.BuyGoods(iIndex, iNum);
}

bool ShopManager::SellGoods(const int iIndex, const int iNum)
{
    return m_oShop.SellGoods(iIndex, iNum);
}
