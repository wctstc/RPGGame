#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

#include <time.h>
#include <conio.h>

#include "Manager.h"
#include "UIBase.h"
#include "Event.h"

//最小检查的时间间隔(ms)
#define TIMEGAP_MIN 10
//定时器检查的时间间隔(ms)
#define TIMEGAP_TIMER 100
//键盘检查的时间间隔(ms)
#define TIMEGAP_KEYBOARD 10

//每次检查的时间(ms)
#define TIMEGAP_MAX 10000

class EventManager :public Manager
{
public:
	EventManager();
	~EventManager();
public:
	virtual bool Init(App* pApp, Config *pConfig);

private:
	virtual int Handle(int iCmd, Req &oReq);
private:
	int m_iTimerCount;
};


#endif // __EVENTMANAGER_H__

