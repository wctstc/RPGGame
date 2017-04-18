#ifndef __SHOWFRAME_H__
#define __SHOWFRAME_H__

#include "Frame.h"

/**
 * @brief 商店框类
 */
class ShopFrame :public Frame
{
public:
    /**
    * @brief 生成请求数据
    */
    virtual void PrepareReq(Req &oReq);

    /**
    * @brief 处理响应数据
    */
    virtual void PrepareRsp(const Rsp &oRsp);
};


#endif // __SHOWFRAME_H__

