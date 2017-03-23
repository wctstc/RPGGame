#include "EventManager.h"



EventManager::EventManager()
	:m_iTimerCount(0)
{
}


EventManager::~EventManager()
{
}

bool EventManager::Init(App* pApp, Config *pConfig)
{
	bool bRet = Manager::Init(pApp, pConfig);

	if (!bRet)
		return false;
	
	RegisterCmd(cmd::COMMAND_IDLE);

	return true;
}
int EventManager::Handle(int iCmd, Req &oReq)
{
	if (iCmd != cmd::COMMAND_IDLE)
		return -1;
	
	Event event;

	int iRet = -1;

	int selected = 0;

	for (int i = 0; i < TIMEGAP_MAX / TIMEGAP_MIN; ++i)
	{
		if (m_iTimerCount > TIMEGAP_TIMER / TIMEGAP_MIN)
		{
			event.Init(EVENT_TIMER, TIMEGAP_TIMER, "");
			iRet = 0;
		}

		if (_kbhit())
		{
			int input = _getch();

			if (input == 13)//回车
			{
				event.Init(EVENT_KEYBORAD, 13, "");
				iRet = 0;
			}
			else if (input == 27)//ESC
			{
				event.Init(EVENT_KEYBORAD, 27, "");
				iRet = 0;
			}

			//方向键
			if (input == 224)
			{
				if (_kbhit())
				{
					input = _getch();
					switch (input)//移动
					{
					case 75:
					case 77:
					case 72:
					case 80:
						event.Init(EVENT_KEYBORAD, input, "");
						iRet = 0;
						break;
					}
				}
			}
		}
		Sleep(TIMEGAP_MIN);
	}

	if (iRet)
	{
	}

	return 0;
}

