#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Struct.h"
#include "Container.h"
#include "Equipment.h"

/**
* @brief 玩家类
*/
class Player
{
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
public:
	Player();
	~Player();
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
    bool AddItemToBag(const int iItemID, const int iNumber);

    /**
    * @brief 添加到背包，多出来的丢弃
    */
    void AddItemToBagFocus(const int iItemID, const int iNumber);

    /**
    * @brief 是否可以添加到背包
    */
    bool CanAddItemToBag(const int iItemID, const int iNumber);

    /**
     * @brief 付钱
     */
    bool Pay(const int iMoney);


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
    SET_GET(int, i, BaseID, m_stPlayerData.stActorData.iID);
    SET_GET(string, s, BaseName, m_stPlayerData.stActorData.sName);
    SET_GET(int, i, BaseHp, m_stPlayerData.stActorData.iHp);
    SET_GET(int, i, BaseMaxHp, m_stPlayerData.stActorData.iMaxHp);
    SET_GET(int, i, BaseAttack, m_stPlayerData.stActorData.iAttack);
    SET_GET(int, i, BaseDefance, m_stPlayerData.stActorData.iDefance);
    SET_GET(int, i, Money, m_stPlayerData.stActorExternData.iMoney);
protected:
    /*!< 玩家数据 */
    data::PlayerData m_stPlayerData;

    /*!< 装备状态数组 */
    EquipmentState m_ayEquipments[EquipmentType::EQUIPMENT_TYPE_MAX];

    /*!< 背包 */
    Container m_oBag;
};


#endif // __PLAYER_H__
