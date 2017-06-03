#ifndef __PROPERTYFRAME_H__
#define __PROPERTYFRAME_H__

#include "Singleton.h"
#include "Frame.h"
#include "FrameStruct.h"



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
    virtual bool Init();


public:
    /**
     * @brief 更新框
     */
    virtual void Update();

public:
    SET_GET(int, i, Hp,       m_stPropertyFrameData.iHp)
    SET_GET(int, i, MaxHp,    m_stPropertyFrameData.iMaxHp)
    SET_GET(int, i, Money,    m_stPropertyFrameData.iMoney)
    SET_GET(int, i, Level,    m_stPropertyFrameData.iLevel)
    SET_GET(int, i, Exp,      m_stPropertyFrameData.iExp)
    SET_GET(int, i, TotalExp, m_stPropertyFrameData.iTotalExp)
    SET_GET(int, i, Bag,      m_stPropertyFrameData.iBag)
    SET_GET(int, i, TotalBag, m_stPropertyFrameData.iTotalBag)
private:
    frame_data::PropertyFrameData m_stPropertyFrameData;
};


#endif // __PROPERTYFRAME_H__


