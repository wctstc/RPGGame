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
    * @brief ≥ı ºªØ
    */
    virtual bool Init();

public:
    const ShopManager::VecGoods &GetAllGoods()const;
    const Goods &GetGoods(const int iIndex)const;

    bool SellGoods( const int iPrice, const int iGoodID );


    int GetNumberOfGoodsCategory()const;
    int GetGoodsItemID(const int index)const;
    int GetGoodsAmount(const int index)const;
    int GetGoodsPrice(const int index)const;
private:
   // vector<data::GoodsData> m_vGoods;
    VecGoods m_vGoods;
};



#endif // __SHOPMANAGER_H__


