#ifndef __TIPSFRAME_H__
#define __TIPSFRAME_H__

#include "Frame.h"
#include "Singleton.h"

/**
* @brief 主界面提示框类
*/
class TipsFrame : public Frame, public Singleton<TipsFrame>
{
public:
    TipsFrame();
    ~TipsFrame();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init(const FrameConfig &stConfig);
};



#endif // __TIPSFRAME_H__
