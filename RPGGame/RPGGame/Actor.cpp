#include "Actor.h"



Actor::Actor()
{
}


Actor::~Actor()
{
}

bool Actor::Init(int iMaxHp, int iAttack, int iDefance)
{
	m_oActorData.Init(iMaxHp, iMaxHp, iAttack, iDefance);

	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		m_ayEquipments[i].bIsEquip = false;

	return true;
}

void Actor::Reset()
{
	m_oActorData.SetHp(GetMaxHp());
}

EquipmentOperator Actor::Equip(const EquipmentOperator eEquipmentOperator, const Equipment &oNewEquipment, Equipment &oOldEuipment)
{
	EquipmentOperator eRet;
	EquipmentState *oTempEquipment = NULL;
	if (oNewEquipment.GetType() >= 0
		&& oNewEquipment.GetType() < EQUIPMENT_TYPE_MAX)
	{
		oTempEquipment = &m_ayEquipments[oNewEquipment.GetType()];
		switch (eEquipmentOperator)
		{
		case EQUIPMENT_OPERATOR_PUTON:
		case EQUIPMENT_OPERATOR_CHANGE:
			eRet = EQUIPMENT_OPERATOR_PUTON;
			if (oTempEquipment->bIsEquip)
			{
				eRet = EQUIPMENT_OPERATOR_CHANGE;
				oOldEuipment = oTempEquipment->oEquipment;
			}

			oTempEquipment->bIsEquip = true;
			oTempEquipment->oEquipment = oNewEquipment;
			break;
		case EQUIPMENT_OPERATOR_GETOFF:
			oTempEquipment->bIsEquip = false;
			oOldEuipment = oTempEquipment->oEquipment;
			eRet = EQUIPMENT_OPERATOR_GETOFF;
			break;
		}
		oTempEquipment = NULL;
	}

	return eEquipmentOperator;
}

void Actor::Defance(int iDamage)
{
	int iRealDamage = iDamage - GetDefance();
	if (iRealDamage <= 0)
		iRealDamage = 1;
	m_oActorData.SetHp(m_oActorData.GetHp() - iRealDamage);
}

int Actor::Attack()
{
	return GetAttack();
}

bool Actor::IsDie()
{
	return m_oActorData.GetHp() <= 0;
}

bool Actor::AddItemToBag(const Item &oItem)
{
	return m_oBag.AddItem(oItem);
}

int Actor::GetHp()
{
	return m_oActorData.GetHp();
}

int Actor::GetMaxHp()
{
	int iTotalMaxHp = m_oActorData.GetMaxHp();

	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if( m_ayEquipments[i].bIsEquip )
			iTotalMaxHp += m_ayEquipments[i].oEquipment.GetMaxHp();

	return iTotalMaxHp;
}

int Actor::GetAttack()
{
	int iTotalAttack = m_oActorData.GetAttack();

	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if (m_ayEquipments[i].bIsEquip)
			iTotalAttack += m_ayEquipments[i].oEquipment.GetAttack();

	return iTotalAttack;
}

int Actor::GetDefance()
{
	int iTotalDefance = m_oActorData.GetDefance();

	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if (m_ayEquipments[i].bIsEquip)
			iTotalDefance += m_ayEquipments[i].oEquipment.GetDefance();

	return iTotalDefance;
}

int Actor::GetBaseMaxHp()
{
	return m_oActorData.GetMaxHp();
}

int Actor::GetBaseAttack()
{
	return m_oActorData.GetAttack();
}

int Actor::GetBaseDefance()
{
	return m_oActorData.GetDefance();
}

int Actor::GetExtendMaxHp()
{
	int iExtendMaxHp = 0;
	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if (m_ayEquipments[i].bIsEquip)
			iExtendMaxHp += m_ayEquipments[i].oEquipment.GetMaxHp();
	return iExtendMaxHp;
}

int Actor::GetExtendAttack()
{
	int iExtendAttack = 0;
	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if (m_ayEquipments[i].bIsEquip)
			iExtendAttack += m_ayEquipments[i].oEquipment.GetAttack();
	return iExtendAttack;
}

int Actor::GetExtendDefance()
{
	int iExtendDefance = 0;
	for (int i = 0; i < EquipmentType::EQUIPMENT_TYPE_MAX; ++i)
		if (m_ayEquipments[i].bIsEquip)
			iExtendDefance += m_ayEquipments[i].oEquipment.GetDefance();
	return iExtendDefance;
}

const Bag& Actor::GetBag() const
{
	return m_oBag;
}
