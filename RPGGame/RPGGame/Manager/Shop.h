#ifndef __SHOP_H__
#define __SHOP_H__

#include <vector>

#include "Goods.h"

using std::vector;

class Shop
{
public:
    /**
    * @brief 商店类型
    */
    enum ShopType
    {
        SHOP_TYPE_NORMAL,
        SHOP_TYPE_MAX,
    };
public:
    Shop();
    ~Shop();

public:
    /**
    * @brief 初始化
    */
    virtual bool Init();

public:
    /**
    * @brief 获取全部商品信息
    */
    const vector<Goods> &GetAllGoods()const;

    /**
    * @brief 购买商品
    */
    bool BuyGoods(const int iIndex, const int iNum);

    /**
    * @brief 出售商品
    */
    bool SellGoods(const int iIndex, const int iNum);

public:
    /**
    * @brief 获取商品类别数量
    */
    int GetGoodsNum()const;

    /**
    * @brief 获取商品的物品编号
    */
    int GetGoodsItemID(const int iIndex)const;

    /**
    * @brief 获取商品数量
    */
    int GetGoodsItemNum(const int iIndex)const;

    /**
    * @brief 获取商品购买价格
    */
    int GetGoodsBuyPrice(const int iIndex)const;

    /**
    * @brief 获取商品出售价格
    */
    int GetGoodsSellPrice(const int iIndex)const;

public:
    SET_GET(int,      i, ID,   m_stData.iID)
    SET_GET(ShopType, e, Type, m_stData.eType)

private:
    struct ShopData
    {
        /*!< 编号 */
        int iID;

        /*!< 类型 */
        ShopType eType;
    };
private:
    ShopData m_stData;
    /*!< 商品 */
    vector<Goods> m_vGoods;
};




#endif // __SHOP_H__