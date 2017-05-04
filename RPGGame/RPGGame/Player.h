#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Actor.h"
#include "Struct.h"
#include "Bag.h"
#include "Equipment.h"
#include "Goods.h"

/**
* @brief 玩家类
*/
class Player : public Actor
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
    virtual bool Init(const Player &oPlayer);
    /**
     * @brief 初始化数据
     */
    virtual bool Init( 
        const int iID,
        const int iHp,
        const int iMaxHp,
        const int iAttack,
        const int iDefance,
        const int iMoney, 
        const int iLevel,
        const int iExp,
        const int iTotalExp);


    /**
     * @brief 保存
     */
    virtual bool Save(int &iLength, char *csBuffer)const;

    /**
     * @brief 加载
     */
    virtual bool Load(int &iLength, const char *const csBuffer);

    /**
     * @brief 重置生命值
     */
    virtual void Reset();

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
    virtual void Defance(const int iDamage);

    /**
     * @brief 普攻伤害
     */
    virtual int Attack();

    /**
     * @brief 添加到背包
     */
    bool AddItemToBag(const int iItemID, const int iNumber);

    /**
    * @brief 从背包减少
    */
    bool ReduceItemFromBag(const int iItemID, const int iNumber);
//     /**
//      * @brief 添加到背包，多出来的丢弃
//      */
//     void AddItemToBagFocus(const int iItemID, const int iNumber);
// 
//     /**
//      * @brief 是否可以添加到背包
//      */
//     bool CanAddItemToBag(const int iItemID, const int iNumber);

    /**
     * @brief 加钱
     */
    bool AddMoney(const int iMoney);
    /**
     * @brief 减钱
     */
    bool ReduceMoney(const int iMoney);

public:

    /**
    * @brief 获取加成的生命上限
    */
    int GetExtendMaxHp()const;

    /**
     * @brief 获取加成的攻击力
     */
    int GetExtendAttack()const;

    /**
     * @brief 获取加成的防御力
     */
    int GetExtendDefance()const;


public://-模块数据获取----------------------------------------------------//
    ///**
    // * @brief 获取背包
    // */
    //const Bag& GetBag()const;

public:
    SET_GET(int,  i, Money,    m_stPlayerData.iMoney);
    SET_GET(int,  i, Level,    m_stPlayerData.iLevel);
    SET_GET(int,  i, Exp,      m_stPlayerData.iExp);
    SET_GET(int,  i, TotalExp, m_stPlayerData.iTotalExp);
    SET_GET(Bag&, o, Bag,    m_stBag);
private:
    /**
     * @brief 玩家数据
     */
    struct PlayerData
    {
        /*!< 钱 */
        int iMoney;

        /*!< 等级 */
        int iLevel;

        /*!< 当前获得经验 */
        int iExp;

        /*!< 下一级所需经验 */
        int iTotalExp;
    };
private:
    /*!< 背包 */
    Bag m_stBag;
    /*!< 玩家数据 */
    PlayerData m_stPlayerData;
    EquipmentState m_ayEquipments[Equipment::EQUIPMENT_TYPE_MAX];
};


#endif // __PLAYER_H__
