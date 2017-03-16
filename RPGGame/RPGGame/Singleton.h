#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template<class T>
class Singleton
{
public:
	inline static T& GetInstance()
	{
		static T t;
		return t;
	}
};



#endif // __SINGLETON_H__
