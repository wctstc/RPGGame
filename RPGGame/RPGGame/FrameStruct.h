#ifndef __FRAMESTRUCT_H__
#define __FRAMESTRUCT_H__

/**
 * @brief 框的数据
 */
namespace frame_data
{
    /**
     * @brief 主界面属性框数据
     */
    struct PropertyFrameData
    {
        /*!< 血量 */
        int iHp;

        /*!< 最大血量 */
        int iMaxHp;

        /*!< 货币 */
        int iMoney;

        /*!< 等级 */
        int iLevel;

        /*!< 当前经验 */
        int iExp;

        /*!< 下级经验 */
        int iTotalExp;

        /*!< 背包物品数量 */
        int iBag;

        /*!< 背包总容量 */
        int iTotalBag;
    };

}

#endif // __FRAMESTRUCT_H__
