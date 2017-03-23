#ifndef __EVENT_H__
#define __EVENT_H__


#include <string>
using std::string;

enum EventType
{
	EVENT_NET,
	EVENT_KEYBORAD,
	EVENT_SYSTEM,
	EVENT_MOUNCE,
	EVENT_TIMER,
	EVENT_UNKNOW
};

class Event
{
public:
public:
	Event();
	~Event();
public:
	bool Init(EventType eType, int iCmd, string sData);
public:
	inline EventType GetType()const{ return m_eType; }
	inline int GetCmd()const{ return m_iCmd; }
	inline string GetData()const{ return m_sData; }
private:
	EventType m_eType;
	int m_iCmd;
	string m_sData;
};


#endif // __EVENT_H__

