#ifndef __PROPERTYFRAME_H__
#define __PROPERTYFRAME_H__

#include "Singleton.h"
#include "Frame.h"



/**
 * @brief 主界面属性框
 */
class PropertyFrame : public Frame, public Singleton<PropertyFrame>
{
public:
    PropertyFrame();
    ~PropertyFrame();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init(const FrameConfig &stConfig);


public:
    /**
     * @brief 更新框
     */
    virtual void Update();

public:
    inline void SetHp(const int iHp) { m_iHp = iHp; }
    inline void SetMaxHp(const int MaxHp) { m_iMaxHp = MaxHp; }
    inline void SetMoney(const int iMoney) { m_iMoney = iMoney; }
    inline void SetLevel(const int iLevel) { m_iLevel = iLevel; }
    inline void SetExp(const int iExp) { m_iExp = iExp; }
    inline void SetTotalExp(const int iTotalExp) { m_iTotalExp = iTotalExp; }
    inline void SetBag(const int iBag) { m_iBag = iBag; }
    inline void SetTotalBag(const int iTotalBag) { m_iTotalBag = iTotalBag; }
private:
    /*!< 血量 */
    int m_iHp;

    /*!< 最大血量 */
    int m_iMaxHp;

    /*!< 货币 */
    int m_iMoney;

    /*!< 等级 */
    int m_iLevel;

    /*!< 当前经验 */
    int m_iExp;

    /*!< 下级经验 */
    int m_iTotalExp;

    /*!< 背包物品数量 */
    int m_iBag;

    /*!< 背包总容量 */
    int m_iTotalBag;
};


#endif // __PROPERTYFRAME_H__


