#ifndef __PLAYERMANAGER_H__
#define __PLAYERMANAGER_H__

#include "Singleton.h"
#include "Manager.h"
#include "Player.h"
#include "Container.h"
/**
* @brief 玩家管理
*/
class PlayerManager:public Singleton<PlayerManager>,public Manager
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
	const Container &GetBag()const;

    /**
    * @brief 添加到背包
    */
    bool AddToBag( const int iItemID, const int iNum);

    /**
     * @brief 从背包取出
     */
    bool ReduceFromBag(const int iItemID, const int iNum);

     /**
      * @brief 买东西
      */
    bool Buy(const int iItemID, const int iPrice);

    /**
    * @brief 卖东西
    */
    bool Sell(const int iItemID, const int iPrice);


    /**
     * @brief 攻击
     */
    void Attack(Actor &oActor);
    /**
     * @brief 获取玩家
     */
    const Player & GetPlayer();
private:
	/*!< 玩家 */
	Player m_oPlayer;
};

#endif // __PLAYERMANAGER_H__
