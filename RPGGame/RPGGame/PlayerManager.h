#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "Singleton.h"
#include "Player.h"
#include "Goods.h"

/**
* @brief 玩家管理
*/
class PlayerManager:public Singleton<PlayerManager>
{
public:
	PlayerManager();
	~PlayerManager();
public:
	/**
	* @brief 初始化
	*/
	virtual bool Init();
public:
	/**
	* @brief 获取背包
	*/
	const Container &GetBag();

     /**
      * @brief 买东西
      */
    bool Buy( const Goods &oGoods );
private:
	/*!< 玩家 */
	Player m_oPlayer;
};

#endif // __PLAYERMANAGER_H__
