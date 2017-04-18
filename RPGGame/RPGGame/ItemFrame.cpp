#include "ItemFrame.h"



ItemFrame::ItemFrame()
{
}


ItemFrame::~ItemFrame()
{
}

void ItemFrame::PrepareReq(req::Req &oReq)
{
    oReq.Init(cmd::COMMAND_SHOW_ITEM);
}

void ItemFrame::PrepareRsp(const rsp::Rsp &oRsp)
{
	string sDescription = oRsp.GetString("description");
	SetDescription(sDescription);
}
