#ifndef __LOADER_H__
#define __LOADER_H__

#include <map>
#include <string>
#include <google/protobuf/message.h>

using std::string;
using std::map;
using std::make_pair;

/**
 * @brief 加载类
 */
class Loader
{
public:
    Loader();
    virtual ~Loader();
public:
    /**
     * @brief 初始化
     */
    virtual bool Init(const string sFile);
    /**
     * @brief 加载配置文件
     */
    virtual bool Load() = 0;
public:
    /**
     * @brief 获取配置文件全部数据
     */
    bool GetConfigArray( google::protobuf::Message &oProtobuf);
private:
    /*!< 配置文件 */
    string m_sFile;
};



#endif // __LOADER_H__

