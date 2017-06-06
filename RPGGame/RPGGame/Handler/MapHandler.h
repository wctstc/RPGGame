#ifndef __MAPHANDLER_H__
#define __MAPHANDLER_H__

#include "Singleton.h"

#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"
#include "Notify.h"


/**
 * @brief 野外
 */
class MapHandler:public Singleton<MapHandler>
{
public:
    MapHandler();
    ~MapHandler();

public:
    /**
     * @brief 展示地图列表
     */
    int HandlerShowMap(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);
    /**
     * @brief 展示地图操作
     */
    int HandlerShowMapAction(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);
    /**
    * @brief 找怪
    */
    int HandlerShowMonster(const cmd::Command eCmd, const  req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 攻击
     */
    int HandleMapAttack(const cmd::NotifyCommand eNotifyCommand, const notify::Notify &oNotify);


    /**
    * @brief 逃跑
    */
    int HandleMapRun(const cmd::NotifyCommand eNotifyCommand, const notify::Notify &oNotify);
};



#endif // __MAPHANDLER_H__

