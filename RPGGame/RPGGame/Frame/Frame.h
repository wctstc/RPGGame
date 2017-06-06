#ifndef __FRAME_H__
#define __FRAME_H__

#include "FrameConfigLoader.h"
#include "FrameData.h"

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

public:
    /**
     * @brief 展示框
     */
    void Show()const;

protected:
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
    inline FrameConfig &UseFrameConfig() { return m_stConfig; }
    inline FrameData &UseFrameData() { return m_stData; }

    inline const FrameConfig &GetFrameConfig() const { return m_stConfig; }
    inline const FrameData &GetFrameData() const { return m_stData; }

    inline void SetFrameConfig(const FrameConfig &stFrameConfig) { m_stConfig = stFrameConfig; }
    inline void SetFrameData(const FrameData &stFrameData) { m_stData = stFrameData; }
private:
    /*!< 框配置 */
    FrameConfig m_stConfig;

    /*!< 框数据 */
    FrameData m_stData;
};

#endif // __FRAME_H__



