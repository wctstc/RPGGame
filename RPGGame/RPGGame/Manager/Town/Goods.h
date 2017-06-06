#ifndef __GOODS_H__
#define __GOODS_H__

#include "Struct.h"

class Goods
{
public:
    Goods(const Goods &stGoods);
    Goods(const int iID, const int iItemID, const int iItemNum, const int iBuyPrice, const int iSellPrice);
    ~Goods();
public:
    bool Buy(const int iItemNum);
    bool Sell(const int iItemNum);
public:
    SET_GET(int, i, ID,        m_stGoodsData.iID)
    SET_GET(int, i, ItemID,    m_stGoodsData.iItemID)
    SET_GET(int, i, ItemNum,   m_stGoodsData.iItemNum)
    SET_GET(int, i, BuyPrice,  m_stGoodsData.iBuyPrice)
    SET_GET(int, i, SellPrice, m_stGoodsData.iSellPrice)
private:
    /**
    * @brief 商品数据
    */
    struct GoodsData
    {
        /*!< 商品编号 */
        int iID;

        /*!< 物品编号 */
        int iItemID;

        /*!< 物品库存 */
        int iItemNum;

        /*!< 单次购买价格 */
        int iBuyPrice;

        /*!< 单次出售价格 */
        int iSellPrice;
    };
private:
    GoodsData m_stGoodsData;
};

#endif // __GOODS_H__

