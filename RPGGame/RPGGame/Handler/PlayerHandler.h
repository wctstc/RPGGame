#ifndef __PLAYERHANDLER_H__
#define __PLAYERHANDLER_H__


#include "Singleton.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"
#include "Notify.h"

class PlayerHandler:public Singleton<PlayerHandler>
{
public:
	PlayerHandler();
	virtual ~PlayerHandler();
public:

    /**
     * @brief 展示背包
     */
    int HandleShowBag(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 展示物品
     */
    int HandleShowBagItem(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);
    
public:

};



#endif // __PLAYERHANDLER_H__

