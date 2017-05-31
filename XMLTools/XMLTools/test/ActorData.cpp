
#include "ActorData.h"

ActorData::ActorData()
:	m_iID(0)
,	m_iHp(0)

{


}

ActorData::~ActorData()
{

}

bool ActorData::Init()
{

	
	m_iID = 0;
	
	m_iHp = 0;



    return true;
}

bool ActorData::Init(const ActorData &oActorData)
{


	m_iID = oActorData.m_iID;

	m_iHp = oActorData.m_iHp;

    return true;
}

string ActorData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool ActorData::FromString(const string sBuffer)
{
    return true;
}






#struct_set_implement#



