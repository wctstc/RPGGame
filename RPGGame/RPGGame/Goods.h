#ifndef __GOODS_H__
#define __GOODS_H__

#include "Struct.h"

class Goods
{
public:
    Goods();
    Goods(const int iID, const int iItemID, const int iAmount, const int iPrice);
    Goods(const data::GoodsData &stGoodsData);
    ~Goods();
public:
    SET_GET(int, i, ID,     m_stGoodsData.iID);
    SET_GET(int, i, ItemID, m_stGoodsData.iItemID);
    SET_GET(int, i, Amount, m_stGoodsData.iAmount);
    SET_GET(int, i, Price,  m_stGoodsData.iPrice);
private:
    data::GoodsData m_stGoodsData;
};

#endif // __GOODS_H__

