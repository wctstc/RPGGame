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
		COMMAND_IDLE,

		/*!< 开始 */
		COMMAND_START,

		/*!< 展示背包 */
		COMMAND_SHOW_BAG = 10001,

		/*!< 展示物品 */
		COMMAND_SHOW_ITEM = 10002,
	};

}



#endif // __CMD_H__

