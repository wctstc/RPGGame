#ifndef __FRAMEMANAGER_H__
#define __FRAMEMANAGER_H__

#include <list>
#include <vector>

#include "Singleton.h"
#include "Hander.h"
#include "FrameWithOption.h"


using std::list;
using std::vector;
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
	int HandleIdle(req::Req &oReq);

	/**
	 * @brief 处理开始界面
	 */
	int HandleStart(req::Req &oReq);
private:
	/**
	 * @brief 处理命令路由
	 */
	virtual int Handle(const cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp);

    /**
     * @brief 处理通知路由
     */
    virtual void Handle(const cmd::NotifyCommand eNotify, const notify::Notify &oNotify);

private:
    /**
     * @brief 处理请求
     */
    int DoForword( FrameWithOption *const pFrame);

    /**
     * @brief 处理通知
     */
    void DoNotify(const cmd::NotifyCommand eNotifyCommand, const int iIndex, const int iDataID);

    /**
     * @brief 框入栈
     */
    void PushStackFrame(const int iIndex, const data::Option &stOption);

    /**
     * @brief 框出栈
     */
    void PopStackFrame();

private:
	/*!< 显示框的栈 */
    vector<FrameWithOption*> m_vStackFrames;
};

#endif // __FRAMEMANAGER_H__
