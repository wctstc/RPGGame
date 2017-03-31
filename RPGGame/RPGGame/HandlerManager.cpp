#include "HandlerManager.h"



HandlerManager::HandlerManager()
{
}


HandlerManager::~HandlerManager()
{
}

int HandlerManager::Handle(int iCmd, Req &oReq, Rsp &oRsp)
{
	switch (iCmd)
	{
	case 1:
		break;
	default:
		return -1;
	}
	return -1;
}
