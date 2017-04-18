#ifndef __FRAMEMANAGER_H__
#define __FRAMEMANAGER_H__

#include <list>

#include "Singleton.h"
#include "Hander.h"
#include "Frame.h"

using std::list;
using cmd::Command;

/**
* @brief 框处理类
*/
class FrameHander : public Singleton<FrameHander>,public Hander
{
public:
	FrameHander();
	virtual ~FrameHander();
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
	 * @brief 处理空闲界面
	 */
	int HandleIdle(Req &oReq);

	/**
	 * @brief 处理开始界面
	 */
	int HandleStart(Req &oReq);
private:
	/**
	 * @brief 处理命令路由
	 */
	virtual int Handle(cmd::Command eCmd, Req &oReq, Rsp &oRsp);

private:
	/*!< 显示框的栈 */
	list<Frame*> m_lsFrames;
};

#endif // __FRAMEMANAGER_H__
