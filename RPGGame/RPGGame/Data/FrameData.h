
#ifndef __FRAMEDATA_H__
#define __FRAMEDATA_H__

#include <string>





using std::string;

/**
 * @brief 框数据
 */
class FrameData
{
public:

	/**
	 * @brief 框状态
	 */
	enum FrameState
	{
		/*<! 正常*/
		FRAME_STATE_NORMAL = 0,

		/*<! 结束*/
		FRAME_STATE_FINISH = 0,

	};

public:
    FrameData();
    ~FrameData();
public:
    /**
     * @brief 空对象
     */
    static const FrameData &GetNoFrameData();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init();
    
    /**
     * @brief 初始化
     */
    virtual bool Init(const FrameData &oFrameData);
    
    /**
     * @brief 字符串化
     */
    virtual string ToString()const;
    
    /**
     * @brief 反字符串化
     */
    virtual bool FromString(const string sBuffer);

public:    

	/**
	 * @brief 获取数据
	 */
	inline const int &GetData() const{return m_iData;}

	/**
	 * @brief 获取选中选项
	 */
	inline const int &GetIndex() const{return m_iIndex;}

	/**
	 * @brief 获取框状态
	 */
	inline const FrameData::FrameState &GetState() const{return m_eState;}


	/**
	 * @brief 使用数据
	 */
	inline int &UseData(){return m_iData;}

	/**
	 * @brief 使用选中选项
	 */
	inline int &UseIndex(){return m_iIndex;}

	/**
	 * @brief 使用框状态
	 */
	inline FrameData::FrameState &UseState(){return m_eState;}

	
	/**
	 * @brief 设置数据
	 */
	inline void SetData(const int &iData){m_iData = iData;}
	
	/**
	 * @brief 设置选中选项
	 */
	inline void SetIndex(const int &iIndex){m_iIndex = iIndex;}
	
	/**
	 * @brief 设置框状态
	 */
	inline void SetState(const FrameData::FrameState &eState){m_eState = eState;}







private:  

	/*<! 数据*/
	int m_iData;

	/*<! 选中选项*/
	int m_iIndex;

	/*<! 框状态*/
	FrameData::FrameState m_eState;



};

#endif //__FRAMEDATA_H__
