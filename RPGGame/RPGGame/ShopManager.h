#ifndef __SHOPMANAGER_H__
#define __SHOPMANAGER_H__

#include "Singleton.h"
#include "Goods.h"



class ShopManager :public Singleton<ShopManager>
{
public:
    typedef vector<Goods> VecGoods;
    typedef vector<Goods>::iterator VecGoodsIt;
public:
    ShopManager();
    ~ShopManager();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init();

public:
    /**
     * @brief 获取全部商品信息
     */
    const ShopManager::VecGoods &GetAllGoods()const;

    /**
     * @brief 获取商品信息
     */
    bool GetGoods(const int iIndex, Goods &stGoods)const;

    /**
     * @brief 卖出商品
     */
    bool SellGoods( const int iPrice, const int iGoodID );

    /**
     * @brief 获取商品类别数量
     */
    int GetNumberOfGoodsCategory()const;

    /**
     * @brief 获取商品的物品编号
     */
    int GetGoodsItemID(const int index)const;

    /**
     * @brief 获取商品数量
     */
    int GetGoodsAmount(const int index)const;

    /**
     * @brief 获取商品价格
     */
    int GetGoodsPrice(const int index)const;
private:
    /*!< 商品 */
    VecGoods m_vGoods;
};



#endif // __SHOPMANAGER_H__


