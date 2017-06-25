#ifndef __HANDER_H__
#define __HANDER_H__

#include "Config.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"
#include "Notify.h"


class App;
/**
* @brief 处理类
*/
class CHandler
{
public:
	CHandler();
	virtual ~CHandler();
public:
	/**
	* @brief 初始化
	*/
	virtual bool Init(Config *pConfig);
	/**
	* @brief 启动模块
	*/
	virtual int Start();
	/**
	* @brief 停止模块
	*/
	virtual int Stop();
	/**
	* @brief 释放模块
	*/
	virtual void Finish();
public:
    /**
    * @brief 转发发送的命令
    */
    int Forword(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 转发发送的通知
    */
    void Notify(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);
public:
	/**
	* @brief 路由命令到处理函数
	*/
	virtual int Handle(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp) = 0;

    /**
    * @brief 路由通知到处理函数
    */
    virtual void Handle(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify) = 0;
protected:
	/**
	* @brief 注册命令处理函数
	*/
	void RegisterCmd(const cmd::Command eCmd);

	/**
	* @brief 注销命令处理函数
	*/
	void UnRegisterCmd(const cmd::Command eCmd);


    /**
    * @brief 注册通知处理函数
    */
    void RegisterNotify(const cmd::NotifyCommand eNotify);

    /**
    * @brief 注销通知处理函数
    */
    void UnRegisterNotify(const cmd::NotifyCommand eNotify);
};


#endif // __HANDER_H__

