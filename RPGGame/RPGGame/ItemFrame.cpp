#include "ItemFrame.h"



ItemFrame::ItemFrame()
{
}


ItemFrame::~ItemFrame()
{
}

void ItemFrame::PrepareReq(Req &oReq)
{

}

void ItemFrame::PrepareRsp(const Rsp &oRsp)
{
	string sDescription = oRsp.GetString("description");
	SetDescription(sDescription);
}
