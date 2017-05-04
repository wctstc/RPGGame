#ifndef __HOMEMANAGER_H__
#define __HOMEMANAGER_H__

#include <string.h>

#include "Singleton.h"
#include "Bag.h"

using std::string;

class HomeManager : public Singleton<HomeManager>
{
public:
    HomeManager();
    virtual ~HomeManager();
public:
    /**
    * @brief 初始化
    */
    virtual bool Init();

    /**
    * @brief 保存
    */
    virtual bool Save(const string sFile);

    /**
    * @brief 加载
    */
    virtual bool Load(const string sFile);
public:
    /**
     * @brief 获取仓库
     */
    const Bag &GetStorage();
    
    /**
     * @brief 存放进仓库
     */
    bool AddToStorage(const int iItemID, const int iItemNum);

    /**
     * @brief 从仓库取出
     */
    int RemoveFromStorage(const int iItemID);
private:
    Bag m_oStorage;
};



#endif // __HOMEMANAGER_H__


