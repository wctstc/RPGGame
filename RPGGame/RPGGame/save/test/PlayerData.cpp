
#include "PlayerData.h"

PlayerData::PlayerData()
:m_iHp(0)
,m_iHp(0)
,m_iHp(0)
,m_iHp(0)
,m_iHp(0)
,m_iHp(0)

{


}

PlayerData::~PlayerData()
{

}

bool PlayerData::Init()
{

    m_iHp = 0;
    m_iHp = 0;
    m_iHp = 0;
    m_iHp = 0;
    m_iHp = 0;
    m_iHp = 0;



    return true;
}

bool PlayerData::Init(const PlayerData &oPlayerData)
{

    m_iHp = oPlayerData.m_iHp;
    m_iHp = oPlayerData.m_iHp;
    m_iHp = oPlayerData.m_iHp;
    m_iHp = oPlayerData.m_iHp;
    m_iHp = oPlayerData.m_iHp;
    m_iHp = oPlayerData.m_iHp;

    return true;
}

string PlayerData::ToString()const
{
    char csBuffer[10240] = {'\0'};
    return csBuffer;
}

bool PlayerData::FromString(const string sBuffer)
{
    return true;
}







