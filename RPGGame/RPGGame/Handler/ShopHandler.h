#ifndef __SHOPHANDLER_H__
#define __SHOPHANDLER_H__


#include "Singleton.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"
#include "Notify.h"

class ShopHandler:public Singleton<ShopHandler>
{
public:
    ShopHandler();
    ~ShopHandler();
public:
    /**
    * @brief 展示商店
    */
    int HandleShowShop(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 展示商品
    */
    int HandleShowShopItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

public:
        /**
    * @brief 买商品
    */
    void HandleBuyShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

    /**
    * @brief 卖商品
    */
    void HandleSellShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);
};


#endif // __SHOPHANDLER_H__
