
#include "PlayerData.h"

PlayerData::PlayerData()
:	m_iID(0)
,	m_iHp(0)
,	m_iMaxHp(0)
,	m_iBaseAttack(0)
,	m_iBaseDefance(0)
,	m_iMoney(0)
,	m_iLevel(0)
,	m_iExp(0)
,	m_iWeapon(0)
,	m_iArmor(0)
,	m_iAccessory(0)

{



}

PlayerData::~PlayerData()
{

}

const PlayerData &PlayerData::GetNoPlayerData()
{
	static PlayerData oPlayerData;
	return oPlayerData;
}

bool PlayerData::Init()
{
	
	m_iID = 0;
	
	m_iHp = 0;
	
	m_iMaxHp = 0;
	
	m_iBaseAttack = 0;
	
	m_iBaseDefance = 0;
	
	m_iMoney = 0;
	
	m_iLevel = 0;
	
	m_iExp = 0;
	
	m_iWeapon = 0;
	
	m_iArmor = 0;
	
	m_iAccessory = 0;





    return true;
}

bool PlayerData::Init(const PlayerData &oPlayerData)
{

	m_iID = oPlayerData.m_iID;

	m_iHp = oPlayerData.m_iHp;

	m_iMaxHp = oPlayerData.m_iMaxHp;

	m_iBaseAttack = oPlayerData.m_iBaseAttack;

	m_iBaseDefance = oPlayerData.m_iBaseDefance;

	m_iMoney = oPlayerData.m_iMoney;

	m_iLevel = oPlayerData.m_iLevel;

	m_iExp = oPlayerData.m_iExp;

	m_iWeapon = oPlayerData.m_iWeapon;

	m_iArmor = oPlayerData.m_iArmor;

	m_iAccessory = oPlayerData.m_iAccessory;


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









