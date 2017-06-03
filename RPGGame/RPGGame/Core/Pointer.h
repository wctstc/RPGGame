#ifndef __POINTER_H__
#define __POINTER_H__

#include <map>
#include <iostream>

using std::map;
using std::make_pair;
using std::cout;
using std::endl;

/**
* @brief 智能指针引用
*/
class CPointRef
{

};

/**
 * @brief 智能指针
 */
template< class Type>
class CPointer
{
public:
	CPointer()
	{
	}
	CPointer( Type *type )
	{
		//计数
		if (type != NULL)
		{
			map<Type *, unsigned int>::iterator it;
			it = g_mapCount.find(type);
			if (it == g_mapCount.end())
				g_mapCount.insert(make_pair(type, 1));
			else
				++it->second;
		}

		//保存实例
		m_pInstance = type;
	}
	CPointer(const CPointer &oPointer)
	{
		if (oPointer.m_pInstance != NULL)
		{
			map<Type *, unsigned int>::iterator it;
			it = g_mapCount.find(oPointer.m_pInstance);
			if (it != g_mapCount.end())
				++it->second;
		}
		//保存实例
		m_pInstance = oPointer.m_pInstance;
	}
	~CPointer()
	{
		if (m_pInstance != NULL)
		{
			map<Type *, unsigned int>::iterator it;
			it = g_mapCount.find(m_pInstance);
			if (it != g_mapCount.end())
			{
				--it->second;
				if (0 == it->second)
				{
					g_mapCount.erase(it);
					delete m_pInstance;
					m_pInstance = NULL;
				}
			}
		}
	}
public:
	CPointer &operator = (CPointer &oPointer)
	{
		map<Type *, unsigned int>::iterator it;
		if (&oPointer != this)//排除自身
		{
			//去掉之前引用
			if (m_pInstance != NULL)
			{
				it = g_mapCount.find(m_pInstance);
				if (it != g_mapCount.end())
					--(it->second);
				if (it->second == 0)
				{
					g_mapCount.erase(it);
					delete m_pInstance;
					m_pInstance = NULL;
				}
			}
			//设置新引用
			if (oPointer.m_pInstance != NULL)
			{
				it = g_mapCount.find(oPointer.m_pInstance);
				if (it != g_mapCount.end())
					++(it->second);
			}
			m_pInstance = oPointer.m_pInstance;
		}
		return *this;
	}
	CPointer &operator = (Type *pType)
	{
		if (pType != NULL)
		{
			map<Type *, unsigned int>::iterator it;
			//去掉之前引用
			if (m_pInstance != NULL)
			{
				it = g_mapCount.find(m_pInstance);
				if (it != g_mapCount.end())
					--(it->second);
				if (it->second == 0)
				{
					g_mapCount.erase(it);
					delete m_pInstance;
					m_pInstance = NULL;
				}
			}
			//设置新引用
			it = g_mapCount.find(pType);
			if (it == g_mapCount.end())
				g_mapCount.insert(make_pair(pType, 1));
			else
				++(it->second);
		}
		m_pInstance = pType;
		return *this;
	}
	operator Type*()
	{
		return m_pInstance;
	}
	Type*operator ->()
	{
		return m_pInstance;
	}
public:
	static void LogCount()
	{
		cout << "LogCount" << endl;
		map<Type*, unsigned int>::iterator it;
		cout << "size:" << g_mapCount.size() << endl;
		for (it = g_mapCount.begin(); it != g_mapCount.end(); ++it)
		{
			cout << (int)it->first << "count:" << it->second << endl;
		}
	}
private:
	static map<Type*, unsigned int> g_mapCount;
	Type *m_pInstance;
};

template< class Type>
map<Type*, unsigned int> CPointer<Type>::g_mapCount;

#endif // __POINTER_H__
