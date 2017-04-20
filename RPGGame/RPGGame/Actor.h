#ifndef __ACTOR__H__
#define __ACTOR__H__

#include "Struct.h"

#include "Item.h"
#include "Container.h"
#include "Equipment.h"


using data::ActorData;

/**
 * @brief 装备操作
 */
enum EquipmentOperator
{
	/*!< 装上 */
	EQUIPMENT_OPERATOR_PUTON,
	/*!< 卸下 */
	EQUIPMENT_OPERATOR_GETOFF,
	/*!< 替换 */
	EQUIPMENT_OPERATOR_CHANGE
};

/**
 * @brief 行动装备位的状态
 */
struct EquipmentState
{
	/*!< 是否有装备，true有装备，false 无装备 */
	bool bIsEquip;
	/*!< 装备信息 */
	Equipment oEquipment;
};

/**
 * @brief 行动者
 */
class Actor
{
public:
	Actor();
	~Actor();
public://-操作----------------------------------------------------//
	/**
	 * @brief 初始化数据
	 */
	bool Init(int iID, int iHp, int iMaxHp, int iAttack, int iDefance);

	/**
	 * @brief 重置生命值
	 */
	void Reset();

	/**
	 * @brief 装上装备或者卸下装备
	 */
	EquipmentOperator Equip(
		const EquipmentOperator eEquipmentOperator,
		const Equipment &oNewEquipment,
		Equipment &oOldEuipment);

	/**
	 * @brief 防御伤害
	 */
	void Defance(int iDamage);

	/**
	 * @brief 普攻伤害
	 */
	int Attack();

	/**
	 * @brief 判断是否死亡
	 */
	bool IsDie();

	/**
	 * @brief 添加到背包
	 */
	bool AddItemToBag(const Item &oItem);

public://-基本属性获取----------------------------------------------------//
	/**
	 * @brief 获取总生命
	 */
	int GetHp();

	/**
 	 * @brief 获取总生命上限
	 */
	int GetMaxHp();

	/**
	 * @brief 获取总攻击力
	 */
	int GetAttack();

	/**
	 * @brief 获取总防御力
	 */
	int GetDefance();

	/**
	 * @brief 获取加成的生命上限
	 */
	int GetExtendMaxHp();

	/**
	 * @brief 获取加成的攻击力
	 */
	int GetExtendAttack();

	/**
	 * @brief 获取加成的防御力
	 */
	int GetExtendDefance();


public://-模块数据获取----------------------------------------------------//
	/**
	 * @brief 获取背包
	 */
	const Container& GetBag()const;

public:
	SET_GET(int,    i, BaseID,      m_oActorData.iID);
	SET_GET(string, s, BaseName,    m_oActorData.sName);
	SET_GET(int,    i, BaseHp,      m_oActorData.iHp);
	SET_GET(int,    i, BaseMaxHp,   m_oActorData.iMaxHp);
	SET_GET(int,    i, BaseAttack,  m_oActorData.iAttack);
	SET_GET(int,    i, BaseDefance, m_oActorData.iDefance);
protected:
	/*!< 行动者数据 */
	ActorData m_oActorData;
	/*!< 装备状态数组 */
	EquipmentState m_ayEquipments[EquipmentType::EQUIPMENT_TYPE_MAX];
	/*!< 背包 */
	Container m_oBag;
};



#endif