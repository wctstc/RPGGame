#ifndef __HANDLERMANAGER_H__
#define __HANDLERMANAGER_H__

#include <map>

#include "HanderBase.h"
#include "Manager.h"

using std::map;

class HandlerManager:public Manager
{
public:
	HandlerManager();
	~HandlerManager();
public:
	virtual int Handle(int iCmd, Req &oReq, Rsp &oRsp);
// public:
// 	virtual bool RegisterHandler();
// 	virtual void UnregisterHander();
private:
	map<int, HanderBase*> m_mapHanders;
};


#endif // __HANDLERMANAGER_H__

