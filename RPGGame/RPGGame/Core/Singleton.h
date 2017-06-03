#ifndef __SINGLETON_H__
#define __SINGLETON_H__


/**
* @brief 单例设计模式
*/
template<class T>
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
