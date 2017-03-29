#ifndef __RPGAPP_H__
#define __RPGAPP_H__

#include <map>
#include <queue>

using std::multimap;
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
	typedef struct ReqData_
	{
		int cmd;
		Req req;
	}ReqData;
public:
	virtual bool Init();
	virtual int Start();
	virtual int Stop();
	virtual void Finish();

public:
	int AddCmdHandle(int iCmd, Manager& oManager);
	int RemoveCmdHandle(int iCmd, Manager& oManager);
	int Request(int iCmd, Req &oReq);
	int Handler(int iCmd, Req &oReq, Rsp &oRsp);
	//int AddTimeHandle(Manager &manager);
	//int RemoveTimeHandle(Manager &manager);
private:
	typedef multimap <int, Manager&>::const_iterator MMIter;
	multimap<int, Manager&> m_mmapCmdToManagers;
	queue<ReqData> m_qRequestDatas;
	bool m_bIsRuning;

	
private:
#define g_FrameLoader FrameLoader::GetInstance()
#define g_FrameManager FrameManager::GetInstance()
};




#endif // __RPGAPP_H__
