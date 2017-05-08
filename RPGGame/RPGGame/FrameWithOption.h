#ifndef __FRAMEWITHOPTION_H__
#define __FRAMEWITHOPTION_H__


#include <conio.h>

#include "Frame.h"
#include "Req.h"
#include "Rsp.h"




/**
* @brief 框类
*/
class FrameWithOption : public Frame
{
public:
	FrameWithOption(void);
	~FrameWithOption(void);
public:
	/**
	* @brief 初始化
	*/
	virtual bool Init( const data::FrameData &oFrameData );

	/**
	* @brief 生成请求数据
	*/
	virtual void PrepareReq(const int iIndex, req::Req &oReq);

	/**
	 * @brief 处理响应数据
	 */
	virtual void PrepareRsp(const rsp::Rsp &oRsp);

public:
	/**
	* @brief 获取第一个选项位置
	*/
	bool GetArrawDefaultPosition(data::Position &stPosition) const;

	/**
	* @brief 展示框
	*/
	void Show()const;

    /**
     * @brief 获取选择
     */
    int GetSelectIndex();

    /**
     * @brief 获取选项
     */
    bool GetOptionByIndex(unsigned int iIndex, data::Option &stOption)const;
private:
    /**
     * @brief 清理框
     */
    virtual void ClearFrame() const;

    /**
     * @brief 清理内容
     */
    virtual void ClearContent() const;

    /**
     * @brief 展示框
     */
    virtual void ShowFrame() const;

    /**
    * @brief 展示描述
    */
    virtual void ShowDescription() const;

    /**
     * @brief 展示选项
     */
    virtual void ShowOptions() const;

public:
    /**
    * @brief 检查回报响应码
    */
    bool CheckRsp(const rsp::Rsp &oRsp);
public:
	SET_GET(int,                   i, ID,          m_oFrameData.iID)
	SET_GET(data::FrameType,       e, Type,        m_oFrameData.eType)
	SET_GET(data::Position&,       o, Position,    m_oFrameData.oPosition)
	SET_GET(data::Size&,           o, Size,        m_oFrameData.oSize)
	SET_GET(string,                s, Description, m_oFrameData.sDescription)
	SET_GET(data::Direction,       e, Direction,   m_oFrameData.eDirection)
	SET_GET(int,                   i, Handler,     m_oFrameData.iHandlerID)
    SET_GET(int,                   i, Data,        m_oFrameData.iData)
    SET_GET(int,                   i, Index,       m_oFrameData.iIndex)
	SET_GET(vector<data::Option>&, v, Options,     m_oFrameData.vOptions)
private:
    /*!< 框数据 */
	data::FrameData m_oFrameData;
};



#endif // __FRAMEWITHOPTION_H__
