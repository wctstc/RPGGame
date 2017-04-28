#ifndef __ITEMDATA_H__
#define __ITEMDATA_H__

namespace dataD
{
    enum ItemType
    {
        ITEM_TYPE_EQUIPMENT,
        ITEM_TYPE_MAX
    };

    enum EquipmentTYPE
    {
        EQUIPMENT_TYPE_WEAPON,
        EQUIPMENT_TYPE_MAX
    };

    struct ItemData
    {
        /*<! 编号 */
        int iID;

        /*<! 类型 */
        ItemType eType;

        /*<! 名字 */
        string sName;

        /*<! 描述 */
        string sDescripition;
    }

    struct EquipmentData
    {
        /*<! 物品 */
        ItemData stItem;

        /*<! 类型 */
        int eType;

        /*<! 附加生命上限 */
        int iMaxHp;

        /*<! 附加攻击力 */
        int iAttack;

        /*<! 附加防御力 */
        int iDefance;
    };
}


#endif // __ITEMDATA_H__
