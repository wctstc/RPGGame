#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__
#include "Thread.h"

class Schedule :public Thread<Schedule>
{
public:
	Schedule();
	~Schedule();
private:
	virtual void Run(Schedule*);
};


#endif // __SCHEDULE_H__