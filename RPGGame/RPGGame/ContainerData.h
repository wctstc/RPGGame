#ifndef __CONTAINERDATA_H__
#define __CONTAINERDATA_H__

#include <vector>

namespace dataD
{
    /**
     * @brief 单元格数据
     */
    struct UnitData
    {
        /*!< 编号 */
        int iID;

        /*!< 物品编号 */
        int iItemID;

        /*!< 物品数量 */
        int iItemNum;

        /*!< 物品最大叠加 */
        int iCapacity;
    };

    /**
     * @brief 容器数据
     */
    struct ContainerData 
    {
        /*!< 编号 */
        int iID;

        /*!< 容量 */
        int iCapacity;

        /*!< 单元格数据 */
        std::vector<data::UnitData> vUnits;
    };

    struct Goods
    {

    };
    struct ShopData
}


#endif // __CONTAINERDATA_H__
