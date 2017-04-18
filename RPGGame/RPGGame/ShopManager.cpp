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

int ShopManager::GetNumberOfGoodsCategory()const
{
    return m_vGoods.size();
}

int ShopManager::GetGoodsItemID(const int index)const
{
    if (index < m_vGoods.size())
        return m_vGoods.at(index).iItemID;
    return -1;
}

int ShopManager::GetGoodsAmount(const int index)const
{
    if (index < m_vGoods.size())
        return m_vGoods.at(index).iAmount;
    return -1;
}

int ShopManager::GetGoodsPrice(const int index)const
{
    if (index < m_vGoods.size())
        return m_vGoods.at(index).iPrice;
    return -1;
}
