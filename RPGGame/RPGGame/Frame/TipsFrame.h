#ifndef __TIPSFRAME_H__
#define __TIPSFRAME_H__

#include "Frame.h"
#include "Singleton.h"


class TipsFrame : public Frame, public Singleton<TipsFrame>
{
public:
    TipsFrame();
    ~TipsFrame();
public:
    /**
    * @brief ≥ı ºªØ
    */
    virtual bool Init();
};



#endif // __TIPSFRAME_H__
