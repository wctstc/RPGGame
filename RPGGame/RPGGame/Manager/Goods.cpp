#include "Goods.h"


Goods::Goods(const Goods &oGoods)
{
    m_stGoodsData = oGoods.m_stGoodsData;
}

Goods::Goods(const int iID, const int iItemID, const int iItemNum, const int iBuyPrice, const int iSellPrice)
{
    m_stGoodsData.iID        = iID;
    m_stGoodsData.iItemID    = iItemID;
    m_stGoodsData.iItemNum   = iItemNum;
    m_stGoodsData.iBuyPrice  = iBuyPrice;
    m_stGoodsData.iSellPrice = iSellPrice;
}



Goods::~Goods()
{
}

bool Goods::Buy(const int iItemNum)
{
    if (iItemNum > m_stGoodsData.iItemNum)
        return false;

    m_stGoodsData.iItemNum -= iItemNum;
    return true;
}

bool Goods::Sell(const int iItemNum)
{
    m_stGoodsData.iItemNum += iItemNum;
    return true;
}
