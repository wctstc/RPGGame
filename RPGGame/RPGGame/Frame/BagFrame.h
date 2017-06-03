#ifndef __BAGFRAME_H__
#define __BAGFRAME_H__


#include "FrameWithOption.h"

/**
* @brief 背包框类
*/
class BagFrame :public FrameWithOption
{
public:
	BagFrame();
	~BagFrame();
private:
	/**
	* @brief 生成请求数据
    */
    virtual void PrepareReq(const int iSelected, req::Req &oReq);

	/**
	* @brief 处理响应数据
	*/
	virtual void PrepareRsp(const rsp::Rsp &oRsp);
};

#endif // __BAGFRAME_H__
