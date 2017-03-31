#include "BagFrame.h"



BagFrame::BagFrame()
{
}


BagFrame::~BagFrame()
{
}

void BagFrame::PrepareReq(Req &oReq)
{

}

void BagFrame::PrepareRsp(const Rsp &oRsp)
{
	vector<Rsp> vRsps = oRsp.GetVector("bag");
	vector<Option> vOptions;
	Option oOption;
	for (vector<Rsp>::const_iterator it = vRsps.begin(); it != vRsps.end(); ++it )
	{
		oOption.sDescription = it->GetString("description");
		oOption.iFrameID = 4;
		vOptions.push_back(oOption);
	}
	SetOptions(vOptions);
}
