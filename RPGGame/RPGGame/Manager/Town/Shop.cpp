#include "Shop.h"



Shop::Shop()
{
}


Shop::~Shop()
{
}

bool Shop::Init()
{
    m_stData.iID = 1;
    m_stData.eType = Shop::SHOP_TYPE_NORMAL;

    Goods oGoods1(0,1,100,50,50);
    m_vGoods.push_back(oGoods1);

    Goods oGoods2(0, 2, 100, 20, 20);
    m_vGoods.push_back(oGoods2);

    Goods oGoods3(0, 3, 100, 80, 80);
    m_vGoods.push_back(oGoods3);

    Goods oGoods4(0, 4, 100, 40, 40);
    m_vGoods.push_back(oGoods4);
    return true;
}

const vector<Goods> & Shop::GetAllGoods() const
{
    return m_vGoods;
}

bool Shop::BuyGoods(const int iIndex, const int iNum)
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).Buy(iNum);
    return false;
}

bool Shop::SellGoods(const int iIndex, const int iNum)
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).Sell(iNum);
    return false;
}

int Shop::GetGoodsNum() const
{
    return m_vGoods.size();
}


int Shop::GetGoodsItemID(const int iIndex)const
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).GetItemID();
    return 0;
}

int Shop::GetGoodsItemNum(const int iIndex) const
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).GetItemNum();
    return 0;
}

int Shop::GetGoodsBuyPrice(const int iIndex) const
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).GetBuyPrice();
    return 0;
}

int Shop::GetGoodsSellPrice(const int iIndex) const
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
        return m_vGoods.at(iIndex).GetSellPrice();
    return 0;
}
