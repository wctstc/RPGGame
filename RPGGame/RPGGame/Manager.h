#ifndef __MANAGER_H__
#define __MANAGER_H__
/**
 * @file Manager.h
 * @author Lost
 * @date ÈýÔÂ 2017
 * @brief 
 */

#include "Config.h"
#include "Req.h"
#include "Rsp.h"

class App;
class Manager
{
public:
	Manager();
	virtual ~Manager();
public:
	virtual bool Init(App* app,Config *config);
	virtual int Start();
	virtual int Stop();
	virtual void Finish();
public:
	void Ask(int cmd, Req &req, Rsp &rsp);
public:
	virtual int Handle(int cmd, Req &req, Rsp &rsp) = 0;
protected:
	void RegiterCmd(int cmd);
	void UnRegiterCmd(int cmd);


private:
	App *m_app;
};


#endif // __MANAGER_H__

