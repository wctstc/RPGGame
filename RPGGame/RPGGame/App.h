#ifndef __RPGAPP_H__
#define __RPGAPP_H__

#include <map>

using std::multimap;
using std::pair;

#include "Cmd.h"
#include "Singleton.h"
#include "FrameHander.h"
#include "ManagerHander.h"


/*!< 框实例 */
#define g_FrameHander FrameHander::GetInstance()

/*!< 处理实例 */
#define g_ManagerHander ManagerHander::GetInstance()

/*!< 应用实例 */
#define g_App App::GetInstance()

/**
* @brief 应用类，用来管理各个模块
*/
class App : public Singleton<App>
{
public:
	/**
	* @brief 初始化
	*/
	virtual bool Init();
	/**
	* @brief 启动应用服务
	*/
	virtual int Start();
	/**
	* @brief 停止应用服务
	*/
	virtual int Stop();
	/**
	* @brief 清理应用服务
	*/
	virtual void Finish();

public:
	/**
	* @brief 添加命令的处理函数
	*/
	int AddCmdHandle(cmd::Command eCmd, Hander& oManager);

	/**
	* @brief 移除命令的处理函数
	*/
	int RemoveCmdHandle(cmd::Command eCmd, Hander& oManager);

	/**
	* @brief 处理命令
	*/
	int Handler(cmd::Command eCmd, req::Req &oReq, rsp::Rsp &oRsp);

    /**
    * @brief 处理通知
    */
    void Notify(cmd::Notify eNotify, const rsp::Rsp &oRsp);
private:
	typedef multimap <cmd::Command, Hander&>::const_iterator MMapIt;
	/*!< 命令和处理函数的映射关系 */
	multimap<cmd::Command, Hander&> m_mmapCmdToHanders;

	/*!< 是否运行 */
	bool m_bIsRuning;
};




#endif // __RPGAPP_H__
