#ifndef __SHOPITEMFRAME_H__
#define __SHOPITEMFRAME_H__

#include "Frame.h"
/**
 * @brief 商品框
 */
class ShopItemFrame :public Frame
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

#endif // __SHOPITEMFRAME_H__
#include "Frame.h"

