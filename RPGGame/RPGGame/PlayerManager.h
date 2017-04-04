#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "Actor.h"
#include "Singleton.h"


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
	const Bag &GetBag();

private:
	/*!< 玩家 */
	Actor m_oActor;
};

#endif // __PLAYERMANAGER_H__
