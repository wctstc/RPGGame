#ifndef __RPGAPP_H__
#define __RPGAPP_H__

#include <map>
#include <queue>

using std::map;
using std::pair;
using std::queue;

#include "Manager.h"
#include "FrameManager.h"
#include "Singleton.h"
#include "Cmd.h"

using cmd::Command;

class App : public Singleton<App>
{
private:
	typedef struct ASK 
	{
		int cmd;
		Req req;
		Rsp rsp;
	}ASK;
public:
	virtual bool Init();
	virtual int Start();
	virtual int Stop();
	virtual void Finish();

public:
	int AddCmd(int cmd, Manager& manager);
	int RemoveCmd(int cmd);
	int AddAsk(int iCmd, Req &oReq, Rsp &oRsp);
private:
	map<int, Manager&> m_cmd_map;
	queue<ASK> m_ask_queue;
	bool m_is_running;
private:
#define g_FrameLoader FrameLoader::GetInstance()
#define g_FrameManager FrameManager::GetInstance()
};




#endif // __RPGAPP_H__
