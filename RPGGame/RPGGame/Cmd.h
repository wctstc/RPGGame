#ifndef __CMD_H__
#define __CMD_H__

/**
* @brief 命令命名空间
*/
namespace cmd
{
	/**
	 * @brief 命令枚举
	 */
	enum Command
	{
		/*!< 空 */
		COMMAND_IDLE = 0,

		/*!< 开始 */
		COMMAND_START,

		/*!< 展示背包 */
        COMMAND_SHOW_BAG = 2100000,

        /*!< 展示物品 */
        COMMAND_SHOW_ITEM = 2110000,

        /*!< 展示商店 */
        COMMAND_SHOW_SHOP = 1200000,

        /*!< 展示商品 */
        COMMAND_SHOW_SHOP_ITEM = 1210000,

        /*!< 展示仓库 */
        COMMAND_SHOW_STOGAE = 1121000,
        
        /*!< 展示仓库物品 */
        COMMAND_SHOW_STOGAE_ITEM = 1121100,

        /*!< 在家展示背包 */
        COMMAND_HOME_SHOW_BAG = 1122000,

        /*!< 在家展示背包物品 */
        COMMAND_HOME_SHOW_BAG_ITEM = 1122100,

    };

    /**
    * @brief 通知枚举
    */
    enum NotifyCommand
    {
        /*!< 空 */
        NOTIFY_IDLE = 0,
        /*!< 商店 */
        NOTIFY_SHOP_BUY = 1210001,
        NOTIFY_SHOP_SELL = 1210002,



        /*!< 仓库 */
        NOTIFY_STORAGE_TAKEOUT = 1121101,
        NOTIFY_STORAGE_DEPOSIT = 1122101,


        /*!< 界面 */
        NOTIFY_UPDATE_PROPERTY = 20001,
        NOTIFY_UPDATE_INFORMATION = 20002,
    };
}



#endif // __CMD_H__

