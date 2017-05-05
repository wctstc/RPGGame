#ifndef __HANDERIMPLEMENT_H__
#define __HANDERIMPLEMENT_H__


#include "Cmd.h"
#include "Singleton.h"
#include "Hander.h"
#include "ItemLoader.h"

/**
* @brief 管理处理类，管理类的门户接口
*/
class ManagerHander :public Singleton<ManagerHander>,public Hander
{
public:
	ManagerHander();
	~ManagerHander();
public:
	/**
	* @brief 初始化
	*/
	virtual bool Init(Config *pConfig);

    /**
    * @brief 启动模块
    */
    virtual int Start();
public:
	/**
	* @brief 分发命令到各个处理函数
	*/
	virtual int Handle(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 路由通知到处理函数
    */
    virtual void Handle(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);
private:
	/**
	 * @brief 展示背包
	 */
	int HandleShowBag(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);

	/**
	 * @brief 展示物品
	 */
	int HandleShowItem(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 展示商店
     */
    int HandleShowShop(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 展示商品
     */
    int HandleShowShopItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 展示仓库
    */
    int HandleShowStorage(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 展示仓库物品
     */
    int HandleShowStorageItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 在家展示背包
    */
    int HandleHomeShowBag(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 在家展示背包物品
    */
    int HandleHomeShowBagItem(const cmd::Command eCmd, const req::Req &oReq, rsp::Rsp &oRsp);







    /**
     * @brief 买商品
     */
    void HandleBuyShopItem(const cmd::NotifyCommand eNotify,const notify::Notify &oNotify);

    /**
    * @brief 卖商品
    */
    void HandleSellShopItem(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

    /**
     * @brief 取出仓库
     */
    void HandleStorageTakeOut(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

    /**
     * @brief 存放仓库
     */
    void HandleStorageDeposit(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

};



#endif