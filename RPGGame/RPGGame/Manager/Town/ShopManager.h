#ifndef __SHOPMANAGER_H__
#define __SHOPMANAGER_H__

#include "Singleton.h"

#include "Shop.h"

class ShopManager :public Singleton<ShopManager>
{
public:
    ShopManager();
    ~ShopManager();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init();

public:
    const Shop &GetShop();

    /**
    * @brief 购买商品
    */
    bool BuyGoods(const int iGoodsID, const int iNum, int &iPrice, int &iCapacity);

    /**
    * @brief 出售商品
    */
    bool SellGoods(const int iIndex, const int iNum);
private:
    /*!< 商品 */
    Shop m_oShop;
};



#endif // __SHOPMANAGER_H__


