#ifndef __SHOPMANAGER_H__
#define __SHOPMANAGER_H__

#include "Singleton.h"
#include "Struct.h"

class ShopManager :public Singleton<ShopManager>
{
public:
    ShopManager();
    ~ShopManager();
public:
    /**
    * @brief ≥ı ºªØ
    */
    virtual bool Init();

public:
    int GetNumberOfGoodsCategory()const;
    int GetGoodsItemID(const int index)const;
    int GetGoodsAmount(const int index)const;
    int GetGoodsPrice(const int index)const;
private:
    vector<data::GoodsData> m_vGoods;
};



#endif // __SHOPMANAGER_H__


