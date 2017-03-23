#include "Event.h"



Event::Event()
:m_eType(EVENT_UNKNOW)
,m_iCmd(0)
,m_sData("")
{
}


Event::~Event()
{
}

bool Event::Init(EventType eType, int iCmd, string sData)
{
	m_eType = eType;
	m_iCmd = iCmd;
	m_sData = sData;
	return true;
}
