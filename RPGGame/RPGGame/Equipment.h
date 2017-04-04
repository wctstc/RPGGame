#ifndef __EQUIPMENT__H__
#define __EQUIPMENT__H__

#include "Struct.h"

using data::EquipmentType;
using data::EquipmentData;

/**
* @brief 装备类
*/
class Equipment
{
public:
	Equipment();
	~Equipment();
public:
	/**
	 * @brief 初始化
	 */
	virtual bool Init( int iID, EquipmentType eType, int iMaxHp, int iAttack, int iDefance );
public:
	SET_GET(int,           i, ID,      m_oEquipmentData.iID);
	SET_GET(EquipmentType, e, Type,    m_oEquipmentData.eType);
	SET_GET(int,           i, MaxHp,   m_oEquipmentData.iMaxHp);
	SET_GET(int,           i, Attack,  m_oEquipmentData.iAttack);
	SET_GET(int,           i, Defance, m_oEquipmentData.iDefance);
private:
	/*!< 装备数据 */
	EquipmentData m_oEquipmentData;
};



#endif
