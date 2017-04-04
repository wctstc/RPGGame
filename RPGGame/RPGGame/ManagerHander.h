#ifndef __HANDERIMPLEMENT_H__
#define __HANDERIMPLEMENT_H__


#include "Cmd.h"
#include "Singleton.h"
#include "Hander.h"

using cmd::Command;



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
public:
	/**
	* @brief 分发命令到各个处理函数
	*/
	virtual int Handle(int iCmd, Req &oReq, Rsp &oRsp);

private:
	/**
	* @brief 展示背包
	*/
	int HandleShowBag(int iCmd, Req &oReq, Rsp &oRsp);

	/**
	* @brief 展示物品
	*/
	int HandleShowItem(int iCmd, Req &oReq, Rsp &oRsp);
};



#endif