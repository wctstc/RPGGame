#ifndef __PARSEDATA_H__
#define __PARSEDATA_H__

#include <string>
#include <map>
#include <vector>

using namespace std;

#include "tinyxml2.h"

using namespace tinyxml2;

class ParseData
{
public:
    /**
     * @brief 数据结构体
     */
    struct Data
    {
        /*!< 节点名称 */
        string node;

        /*!< 节点属性 */
        map<string, string> mapAttr;

        /*!< 子类 */
        map<string, vector<Data>> mapChildren;
    };

public:
    /**
    * @brief 解析xml
    */
    bool Parse(const string sFileName);

    /**
    * @brief 清理
    */
    void Clear();

    /**
    * @brief 获取数据
    */
    const vector<Data>& GetData()const;

private:
    /**
    * @brief 解析xml
    */
    bool Parse(const XMLElement *cpXmlElement, Data &stData);

    /**
    * @brief 解析属性
    */
    bool ParseAttribute(const XMLElement *cpXmlElement, Data &stData);
private:

    /*!< 文件名 */
    string m_sFileName;

    /*!< 解析数据 */
    vector<Data> m_vecData;
};

#endif

