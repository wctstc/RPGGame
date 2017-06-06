#ifndef __HOMEHANDLER_H__
#define __HOMEHANDLER_H__

#include "Singleton.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"
#include "Notify.h"

class HomeHandler:public Singleton<HomeHandler>
{
public:
    HomeHandler();
    virtual ~HomeHandler();

public:
    /**
    * @brief 展示仓库
    */
    int HandleShowStorage(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 展示仓库物品
    */
    int HandleShowStorageItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 展示背包
    */
    int HandleShowBag(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 展示背包物品
    */
    int HandleShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

public:
    /**
    * @brief 取出仓库
    */
    void HandleStorageTakeOut(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

    /**
    * @brief 存放仓库
    */
    void HandleStorageDeposit(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);
};




#endif // __HOMEHANDLER_H__

