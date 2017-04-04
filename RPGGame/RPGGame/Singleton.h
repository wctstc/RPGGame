#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<class T>

/**
* @brief 单例设计模式
*/
class Singleton
{
public:
	/**
	* @brief 获取实例
	*/
	inline static T& GetInstance()
	{
		static T t;
		return t;
	}
};



#endif // __SINGLETON_H__
