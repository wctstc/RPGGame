#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <string>

using std::string;

class Manager
{
public:
    Manager();
    virtual ~Manager();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init() = 0;

    /**
    * @brief 保存
    */
    virtual bool Save(const string sFile) = 0;

    /**
    * @brief 加载
    */
    virtual bool Load(const string sFile) = 0;
};



#endif // __MANAGER_H__


