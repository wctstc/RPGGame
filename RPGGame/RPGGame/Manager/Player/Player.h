#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Actor.h"
#include "Struct.h"
#include "Bag.h"
#include "Equipment.h"
#include "Goods.h"

#include "PlayerData.h"
/**
* @brief 玩家类
*/
class Player
{
     /**
      * @brief 装备操作
      */
//      enum EquipmentOperator
//      {
//          /*!< 装上 */
//          EQUIPMENT_OPERATOR_PUTON,
//          /*!< 卸下 */
//          EQUIPMENT_OPERATOR_GETOFF,
//          /*!< 替换 */
//          EQUIPMENT_OPERATOR_CHANGE
//      };
 
//      /**
//       * @brief 行动装备位的状态
//       */
//      struct EquipmentState
//      {
//          /*!< 是否有装备，true有装备，false 无装备 */
//          bool bIsEquip;
//          /*!< 装备信息 */
//          Equipment oEquipment;
//      };
 public:
 	Player();
 	~Player();
 public://-加载相关----------------------------------------------------//
     /**
      * @brief 初始化
      */
     virtual bool Init();

     /**
      * @brief 保存
      */
     virtual bool Save(int &iLength, char *csBuffer)const;
 
     /**
      * @brief 加载
      */
     virtual bool Load(int &iLength, const char *const csBuffer);
 
     /**
      * @brief 装上装备或者卸下装备
      */
//     EquipmentOperator Equip(
//         const EquipmentOperator eEquipmentOperator,
//         const Equipment &oNewEquipment,
//         Equipment &oOldEuipment);

public://-战斗相关----------------------------------------------------//
    /**
     * @brief 是否死亡
     */
    virtual bool IsDie()const;

    /**
    * @brief 防御伤害
    */
    virtual void Defance(const int iDamage);
 
    /**
    * @brief 普攻伤害
    */
    virtual int Attack();

public://-金钱相关----------------------------------------------------//
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
     inline PlayerData &UsePlayerData() { return m_stPlayerData; }

     inline const PlayerData &GetPlayerData() const { return m_stPlayerData; }
     
     inline void SetPlayerData(PlayerData &stPlayerData) { m_stPlayerData = stPlayerData; }
 private:
     /*!< 玩家数据 */
     PlayerData m_stPlayerData;
 };


#endif // __PLAYER_H__
