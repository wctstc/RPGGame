#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "Config.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"


class App;
/**
* @brief 处理类
*/
class Hander
{
public:
	Hander();
	virtual ~Hander();
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
	int Forword(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp);
public:
	/**
	* @brief 路由命令到处理函数
	*/
	virtual int Handle(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp) = 0;
protected:
	/**
	* @brief 注册处理函数
	*/
	void RegisterCmd(cmd::Command eCmd);

	/**
	* @brief 注销处理函数
	*/
	void UnRegisterCmd(cmd::Command eCmd);
};


#endif // __MANAGER_H__

