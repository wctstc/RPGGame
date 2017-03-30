#include "Equipment.h"



Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

bool Equipment::Init(int iID, EquipmentType eType, int iMaxHp, int iAttack, int iDefance)
{
	m_oEquipmentData.iID      = iID;
	m_oEquipmentData.eType    = eType;
	m_oEquipmentData.iMaxHp   = iMaxHp;
	m_oEquipmentData.iAttack  = iAttack;
	m_oEquipmentData.iDefance = iDefance;
	return true;
}
