#ifndef __PLAYERDATA_H__
#define __PLAYERDATA_H__

#include "ItemData.h"

namespace dataD
{
    /**
    * @brief 行动者数据
    */
    struct ActorData
    {
        /*!< 编号 */
        int iID;
        /*!< 名字 */
        string sName;
        /*!< 生命 */
        int iHp;
        /*!< 生命上限 */
        int iMaxHp;
        /*!< 攻击力 */
        int iAttack;
        /*!< 防御力 */
        int iDefance;
    };


    struct PlayerData
    {
        /*!< 行动者 */
        ActorData stActorData

        /*!< 钱 */
        int iMoney;

        /*!< 当前获得经验 */
        int iExp;

        /*!< 下一级所需经验 */
        int iTotalExp;
    };
}












#endif // __PLAYERDATA_H__

