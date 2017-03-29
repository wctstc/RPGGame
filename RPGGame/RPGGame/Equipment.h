#ifndef __EQUIPMENT__H__
#define __EQUIPMENT__H__

#include "EquipmentData.h"

class Equipment
{
public:
	Equipment();
	~Equipment();
public:
	virtual bool Init( int iBaseMaxHp, int iBaseAttack, int iBaseDefance );
public:
	EquipmentType GetType() const { return m_oEquipmentData.GetType(); }
	int GetMaxHp() const { return m_oEquipmentData.GetMaxHp(); }
	int GetAttack() const { return m_oEquipmentData.GetAttack(); }
	int GetDefance() const { return m_oEquipmentData.GetDefance(); }

	void SetType(EquipmentType eType) { m_oEquipmentData.SetType(eType); }
	void SetMaxHp(int iMaxHp) { m_oEquipmentData.SetMaxHp(iMaxHp); }
	void SetAttack(int iAttack) { m_oEquipmentData.SetAttack(iAttack); }
	void SetDefance(int iDefance) { m_oEquipmentData.SetDefance(iDefance); }
private:
	EquipmentData m_oEquipmentData;
};



#endif
