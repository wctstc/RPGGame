#include "Shop.h"
#include "Log.h"


Shop::Shop()
{
}


Shop::~Shop()
{
}

bool Shop::Init()
{
	ShopConfigLoader &oLoader = ShopConfigLoader::GetInstance();
	if (!oLoader.Init())
	{
		GLogError("ShopConfigLoader fail");
		return false;
	}
	
	m_vecGoods = oLoader.GetAllConfig();

    return true;
}

const vector<ShopConfig> & Shop::GetAllGoods() const
{
    return m_vecGoods;
}

bool Shop::BuyGoods(const int iGoodsID, const int iNum, int &iPrice, int &iCapacity)
{
	if (iNum > iCapacity)
	{
		GLogWarning("capacity is not enought");

		return false;
	}

	const ShopConfig *pShopConfig = ShopConfigLoader::GetInstance().GetShopConfigByID(iGoodsID);
	if (pShopConfig == NULL)
	{
		return false;
	}
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).Buy(iNum);
    return false;
}

bool Shop::SellGoods(const int iIndex, const int iNum)
{
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).Sell(iNum);
    return false;
}

int Shop::GetGoodsNum() const
{
    return m_vecGoods.size();
}


int Shop::GetGoodsItemID(const int iIndex)const
{
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).GetItemID();
    return 0;
}

int Shop::GetGoodsItemNum(const int iIndex) const
{
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).GetItemNum();
    return 0;
}

int Shop::GetGoodsBuyPrice(const int iIndex) const
{
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).GetBuyPrice();
    return 0;
}

int Shop::GetGoodsSellPrice(const int iIndex) const
{
    const int iSize = m_vecGoods.size();
    if (iIndex < iSize)
        return m_vecGoods.at(iIndex).GetSellPrice();
    return 0;
}
