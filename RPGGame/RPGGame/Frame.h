#ifndef __FRAME_H__
#define __FRAME_H__

#include "Struct.h"

class Frame
{
public:
    Frame();
    ~Frame();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();

    /**
     * @brief 初始化
     */
    virtual bool Init(const data::FrameData &oFrameData);

public:
    /**
     * @brief 展示框
     */
    void Show()const;
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
public:
    SET_GET(int,                   i, ID,          m_stFrameData.iID);
    SET_GET(data::FrameType,       e, Type,        m_stFrameData.eType);
    SET_GET(data::Position&,       o, Position,    m_stFrameData.oPosition);
    SET_GET(data::Size&,           o, Size,        m_stFrameData.oSize);
    SET_GET(string,                s, Description, m_stFrameData.sDescription);
    SET_GET(data::Direction,       e, Direction,   m_stFrameData.eDirection);
    SET_GET(int,                   i, Handler,     m_stFrameData.iHandlerID);
    SET_GET(int,                   i, DataID,      m_stFrameData.iDataID);
    SET_GET(vector<data::Option>&, v, Options,     m_stFrameData.vOptions);
private:
    /*!< 框数据 */
    data::FrameData m_stFrameData;
};

#endif // __FRAME_H__



