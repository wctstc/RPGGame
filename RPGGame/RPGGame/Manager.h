#ifndef __MANAGER_H__
#define __MANAGER_H__
/**
 * @file Manager.h
 * @author Lost
 * @date ÈýÔÂ 2017
 * @brief 
 */

#include "Config.h"
#include "Cmd.h"
#include "Req.h"
#include "Rsp.h"

class App;
class Manager
{
public:
	Manager();
	virtual ~Manager();
public:
	virtual bool Init(App* pApp,Config *pConfig);
	virtual int Start();
	virtual int Stop();
	virtual void Finish();
public:
	void Request(int iCmd, Req &oReq);
public:
	virtual int Handle(int iCmd, Req &oReq, Rsp &oRsp) = 0;
protected:
	void RegisterCmd(int iCmd);
	void UnRegisterCmd(int iCmd);
private:
	App *m_pApp;
};


#endif // __MANAGER_H__

