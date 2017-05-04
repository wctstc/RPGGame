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

    /**
     * @brief 保存
     */
    virtual bool Save(const string sFile);

    /**
     * @brief 加载
     */
    virtual bool Load(const string sFile);
public:
	/**
	* @brief 获取背包
	*/
	const Bag &GetBag();

     /**
      * @brief 买东西
      */
    bool Buy(const int iItemID, const int iPrice);

    /**
    * @brief 卖东西
    */
    bool Sell(const int iItemID, const int iPrice);

    /**
     * @brief 获取玩家
     */
    const Player & GetPlayer();
private:
	/*!< 玩家 */
	Player m_oPlayer;
};

#endif // __PLAYERMANAGER_H__
