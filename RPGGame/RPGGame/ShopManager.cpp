#include "ShopManager.h"



ShopManager::ShopManager()
{
}


ShopManager::~ShopManager()
{
}

bool ShopManager::Init()
{
    data::GoodsData data;
    data.iItemID = 1;
    data.iAmount = 1;
    data.iPrice = 10;
    m_vGoods.push_back(data);
    data.iItemID = 2;
    data.iAmount = 1;
    data.iPrice = 20;
    m_vGoods.push_back(data);
    data.iItemID = 3;
    data.iAmount = 1;
    data.iPrice = 30;
    m_vGoods.push_back(data);
    return true;
}

const ShopManager::VecGoods & ShopManager::GetAllGoods() const
{
    return m_vGoods;
}

bool ShopManager::GetGoods(const int iIndex, Goods &stGoods) const
{
    const int iSize = m_vGoods.size();
    if (iIndex < iSize)
    {
        stGoods = m_vGoods.at(iIndex);
        return true;
    }
    return false;
}

bool ShopManager::SellGoods(const int iPrice, const int iGoodID)

{
    for (VecGoodsIt it = m_vGoods.begin();it != m_vGoods.end(); ++it)
    {
        if (it->GetID() == iGoodID && it->GetPrice() == iPrice)
            return true;
    }
    return false;
}

int ShopManager::GetNumberOfGoodsCategory()const
{
    return m_vGoods.size();
}

int ShopManager::GetGoodsItemID(const int index)const
{
    const int iSize = m_vGoods.size();
    if (index < iSize)
        return m_vGoods.at(index).GetItemID();
    return -1;
}

int ShopManager::GetGoodsAmount(const int index)const
{
    const int iSize = m_vGoods.size();
    if (index < iSize)
        return m_vGoods.at(index).GetAmount();
    return -1;
}

int ShopManager::GetGoodsPrice(const int index)const
{
    const int iSize = m_vGoods.size();
    if (index < iSize)
        return m_vGoods.at(index).GetPrice();
    return -1;
}
