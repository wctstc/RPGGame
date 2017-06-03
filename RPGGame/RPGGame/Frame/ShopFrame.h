#ifndef __SHOWFRAME_H__
#define __SHOWFRAME_H__

#include "FrameWithOption.h"

/**
 * @brief 商店框类
 */
class ShopFrame :public FrameWithOption
{
public:
    /**
    * @brief 生成请求数据
    */
    virtual void PrepareReq(const int iIndex, req::Req &oReq);

    /**
    * @brief 处理响应数据
    */
    virtual void PrepareRsp(const rsp::Rsp &oRsp);
};


#endif // __SHOWFRAME_H__

