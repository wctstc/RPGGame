#ifndef __EQUIPMENTDATA__H__
#define __EQUIPMENTDATA__H__


enum EquipmentType
{
	EQUIPMENT_TYPE_WEAPON = 0,
	EQUIPMENT_TYPE_AEMOR = 1,
	EQUIPMENT_TYPE_ACCESSORY = 2,
	EQUIPMENT_TYPE_MAX = 3,
};


class EquipmentData
{
public:
	EquipmentData();
	~EquipmentData();

public:
	EquipmentType GetType() const { return m_eType; }
	int GetMaxHp() const { return m_iMaxHp; }
	int GetAttack() const { return m_iAttack; }
	int GetDefance() const { return m_iDefance; }

	void SetType(EquipmentType eType) { m_eType = eType; }
	void SetMaxHp(int iMaxHp) { m_iMaxHp = iMaxHp; }
	void SetAttack(int iAttack) { m_iAttack = iAttack; }
	void SetDefance(int iDefance) { m_iDefance = iDefance; }
private:
	EquipmentType m_eType;
	int m_iMaxHp;
	int m_iAttack;
	int m_iDefance;
};



#endif
