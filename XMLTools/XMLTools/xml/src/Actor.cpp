
#include "Actor.h"

Actor::Actor()
:m_iID(0)
,m_sName("")
,m_iPreHp(0)
,m_iHp(0)
,m_iBaseMaxHp(0)
,m_iBaseAttack(0)
,m_iBaseDefance(0)

{


}

Actor::~Actor()
{

}

bool Actor::Init()
{

    m_iID = 0;
    m_sName = "";
    m_iPreHp = 0;
    m_iHp = 0;
    m_iBaseMaxHp = 0;
    m_iBaseAttack = 0;
    m_iBaseDefance = 0;



    return true;
}

bool Actor::Init(const Actor &oActor)
{

    m_iID = oActor.m_iID;
    m_sName = oActor.m_sName;
    m_iPreHp = oActor.m_iPreHp;
    m_iHp = oActor.m_iHp;
    m_iBaseMaxHp = oActor.m_iBaseMaxHp;
    m_iBaseAttack = oActor.m_iBaseAttack;
    m_iBaseDefance = oActor.m_iBaseDefance;

    return true;
}

string Actor::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool Actor::FromString(const string sBuffer)
{
    return true;
}





