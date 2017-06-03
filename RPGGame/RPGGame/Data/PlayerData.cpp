
#include "PlayerData.h"

PlayerData::PlayerData()
:	m_iID(0)
,	m_iHp(0)
,	m_iMoney(0)
,	m_iLevel(0)
,	m_iExp(0)

{


	m_iEquipmentSlotRef = 0;


	memset(m_astEquipmentSlot, 0, sizeof(EquipmentSlot)*EQUIPMENT_SLOT_SIZE);

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
	
	m_iMoney = 0;
	
	m_iLevel = 0;
	
	m_iExp = 0;



	m_iEquipmentSlotRef = 0;


	memset(m_astEquipmentSlot, 0, sizeof(EquipmentSlot)*EQUIPMENT_SLOT_SIZE);


    return true;
}

bool PlayerData::Init(const PlayerData &oPlayerData)
{

	m_iID = oPlayerData.m_iID;

	m_iHp = oPlayerData.m_iHp;

	m_iMoney = oPlayerData.m_iMoney;

	m_iLevel = oPlayerData.m_iLevel;

	m_iExp = oPlayerData.m_iExp;


	memcpy(m_astEquipmentSlot, oPlayerData.m_astEquipmentSlot, sizeof(EquipmentSlot)*oPlayerData.m_iEquipmentSlotRef);
	
	m_iEquipmentSlotRef = oPlayerData.m_iEquipmentSlotRef;

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


	
int PlayerData::GetEquipmentSlotNum() const
{
	return m_iEquipmentSlotRef;
}


bool PlayerData::GetEquipmentSlot(const int iIndex, EquipmentSlot &stEquipmentSlot) const
{
	if(iIndex < 0 || iIndex >= m_iEquipmentSlotRef)
		return false;

	stEquipmentSlot = m_astEquipmentSlot[iIndex];
	return true;
}



bool PlayerData::AddEquipmentSlot(const EquipmentSlot &stEquipmentSlot)
{
	if(m_iEquipmentSlotRef >= EQUIPMENT_SLOT_SIZE)
		return false;
		
	m_astEquipmentSlot[m_iEquipmentSlotRef++] = stEquipmentSlot;
	return true;
}

	
bool PlayerData::RemoveEquipmentSlot(const int iIndex)
{
	if(iIndex < 0 || iIndex >= m_iEquipmentSlotRef)
		return false;

	--m_iEquipmentSlotRef;
	
	for (int i = iIndex; i < m_iEquipmentSlotRef; ++i)
		m_astEquipmentSlot[i] = m_astEquipmentSlot[i+1];

	return true;
}



		
int PlayerData::GetEquipmentSlotEquipmentID(const int iIndex) const
{
	if (iIndex < m_iEquipmentSlotRef && iIndex >= 0) 
		return m_astEquipmentSlot[iIndex].iEquipmentID;

	return 0;
}
		
