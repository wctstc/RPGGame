#ifndef __MANAGERHANDLER_H__
#define __MANAGERHANDLER_H__


#include "Cmd.h"
#include "Singleton.h"
#include "Handler.h"

/*!< 管理处理类实例 */
#define g_ManagerHandler ManagerHandler::GetInstance()

/**
* @brief 管理处理类，管理类的门户接口
*/
class ManagerHandler :public Singleton<ManagerHandler>,public CHandler
{
public:
	ManagerHandler();
	~ManagerHandler();
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

public:
    /**
     * @brief 发送消息至提示框
     */
    void UpdateTipsFrame( const string sNotifyMessage );

    /**
     * @brief 发送消息至属性框
     */
    void UpdatePropertyFrame();

public:
    /**
    * @brief 检查请求索引参数
    */
    bool CheckReqIndex(const int iIndexMax, const req::Req &oReq, rsp::Rsp &oRsp) const;

    /**
    * @brief 检查请求数据参数
    */
    bool CheckReqData(const req::Req &oReq, rsp::Rsp &oRsp) const;

    /**
     * @brief 检查通知数据参数
     */
    bool CheckNotifyData(const int iDataMax, const notify::Notify &oNotify) const;

    /**
     * @brief 返回无选项
     */
    bool RspWithNoOption(const string sDescription, rsp::Rsp &oRsp);

};



#endif //__MANAGERHANDLER_H__