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



        
    };

    /**
    * @brief 通知枚举
    */
    enum Notify
    {
        /*!< 空 */
        NOTIFY_IDLE = 0,
        NOTIFY_SHOP_BUY = 1210001,
        NOTIFY_SHOP_SELL = 1210002,

        NOTIFY_UPDATE_PROPERTY = 20001,
        NOTIFY_UPDATE_INFORMATION = 20002,
    };
}



#endif // __CMD_H__

