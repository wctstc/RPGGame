
#include "FrameData.h"

FrameData::FrameData()
:m_iData(0)
,m_iIndex(0)
,m_eState(FrameData::FRAME_STATE_NORMAL)

{


}

FrameData::~FrameData()
{

}

const FrameData &FrameData::GetNoFrameData()
{
	static FrameData oFrameData;
	return oFrameData;
}

bool FrameData::Init()
{	
	m_iData = int(0);
	
	m_iIndex = int(0);
	
	m_eState = FrameData::FrameState(FrameData::FRAME_STATE_NORMAL);




    return true;
}

bool FrameData::Init(const FrameData &oFrameData)
{
	m_iData = oFrameData.m_iData;

	m_iIndex = oFrameData.m_iIndex;

	m_eState = oFrameData.m_eState;


    return true;
}

string FrameData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool FrameData::FromString(const string sBuffer)
{
    return true;
}








