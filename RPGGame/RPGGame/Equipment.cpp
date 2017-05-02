#include "Equipment.h"



Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

bool Equipment::Init(const Equipment &oEquipment)
{
    if (!Item::Init(oEquipment))
        return false;

    m_stEquipmentData = oEquipment.m_stEquipmentData;
    return true;
}

bool Equipment::Init(
    const int iID,
    const Item::ItemType eType,
    const string &sName,
    const string &sDescription,
    const Equipment::EquipmentType eEquipmentType,
    const int iMaxHp,
    const int iAttack,
    const int iDefance)
{
    if (!Item::Init(iID, eType, sName, sDescription))
        return false;

    m_stEquipmentData.eType = eEquipmentType;
    m_stEquipmentData.iMaxHp = iMaxHp;
    m_stEquipmentData.iAttack = iAttack;
    m_stEquipmentData.iDefance = iDefance;
    return true;
}
