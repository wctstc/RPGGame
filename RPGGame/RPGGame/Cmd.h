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
		COMMAND_SHOW_BAG = 10001,

        /*!< 展示物品 */
        COMMAND_SHOW_ITEM = 10002,

        /*!< 展示商店 */
        COMMAND_SHOW_SHOP = 10003,

        /*!< 展示商品 */
        COMMAND_SHOW_SHOP_ITEM = 10004,



        
    };

    /**
    * @brief 通知枚举
    */
    enum Notify
    {
        /*!< 空 */
        NOTIFY_IDLE = 0,
        NOTIFY_SHOP_BUY = 30001,

        NOTIFY_UPDATE_PROPERTY = 20001,
        NOTIFY_UPDATE_INFORMATION = 20002,
    };
}



#endif // __CMD_H__

