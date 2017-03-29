#ifndef __ACTOR__H__
#define __ACTOR__H__

#include "ActorData.h"
#include "Equipment.h"

enum EquipmentOperator
{
	EQUIPMENT_OPERATOR_PUTON,
	EQUIPMENT_OPERATOR_GETOFF,
	EQUIPMENT_OPERATOR_CHANGE
};
struct EquipmentState
{
	bool bIsEquip;
	Equipment oEquipment;
};

class Actor
{
public:
	Actor();
	~Actor();
public:
	bool Init(int iMaxHp, int iAttack, int iDefance);
	void Reset();
	EquipmentOperator Equip(
		const EquipmentOperator eEquipmentOperator,
		const Equipment &oNewEquipment,
		Equipment &oOldEuipment);
	void Defance(int iDamage);
	int Attack();
	bool IsDie();
	bool AddItemToBag(const Item &oItem);

public:
	int GetHp();
	int GetMaxHp();
	int GetAttack();
	int GetDefance();
	int GetBaseMaxHp();
	int GetBaseAttack();
	int GetBaseDefance();
	int GetExtendMaxHp();
	int GetExtendAttack();
	int GetExtendDefance();
	const Bag& GetBag()const;

private:
	ActorData m_oActorData;
	EquipmentState m_ayEquipments[EquipmentType::EQUIPMENT_TYPE_MAX];
	Bag m_oBag;
};



#endif