#include "Goods.h"



Goods::Goods()
{
}

Goods::Goods(const int iID, const int iItemID, const int iAmount, const int iPrice)
{
    m_stGoodsData.iID     = iID;
    m_stGoodsData.iItemID = iItemID;
    m_stGoodsData.iAmount = iAmount;
    m_stGoodsData.iPrice  = iPrice;
}

Goods::Goods(const data::GoodsData &stGoodsData)
{
    m_stGoodsData = stGoodsData;
}


Goods::~Goods()
{
}
