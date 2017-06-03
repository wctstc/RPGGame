#ifndef __EQUIPMENT__H__
#define __EQUIPMENT__H__

#include "Item.h"

/**
* @brief 装备类
*/
class Equipment : public Item
{
public:
    /**
    * @brief 装备类型
    */
    enum EquipmentType
    {
        /*!< 武器 */
        EQUIPMENT_TYPE_WEAPON = 0,

        /*!< 防具 */
        EQUIPMENT_TYPE_AEMOR = 1,

        /*!< 饰品 */
        EQUIPMENT_TYPE_ACCESSORY = 2,

        /*!< 类型最大值 */
        EQUIPMENT_TYPE_MAX = 3,
    };
public:
	Equipment();
	~Equipment();
public:

    /**
    * @brief 初始化
    */
    virtual bool Init(const Equipment &oEquipment);
    
    /**
	 * @brief 初始化
	 */
	virtual bool Init( 
        const int iID, 
        const Item::ItemType eType,
        const string &sName,
        const string &sDescription,
        const Equipment::EquipmentType eEquipmentType,
        const int iMaxHp,
        const int iAttack,
        const int iDefance );


private:
    /**
    * @brief 装备数据
    */
    struct EquipmentData
    {
        /*<! 类型 */
        Equipment::EquipmentType eType;

        /*<! 附加生命上限 */
        int iMaxHp;

        /*<! 附加攻击力 */
        int iAttack;

        /*<! 附加防御力 */
        int iDefance;
    };
private:
	/*!< 装备数据 */
    EquipmentData m_stEquipmentData;
public:
    SET_GET(Equipment::EquipmentType, e, Type, m_stEquipmentData.eType);
    SET_GET(int, i, MaxHp, m_stEquipmentData.iMaxHp);
    SET_GET(int, i, Attack, m_stEquipmentData.iAttack);
    SET_GET(int, i, Defance, m_stEquipmentData.iDefance);
};



#endif
