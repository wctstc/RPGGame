#ifndef __PARSEXML_H__
#define __PARSEXML_H__

#include <string>
#include <map>
#include <vector>

using namespace std;

#include "tinyxml2.h"

using namespace tinyxml2;

/**
 * @brief 解析xml
 */

class ParseXML
{
public:
    ParseXML();
    ~ParseXML();

public:
    /**
     * @brief 解析数据
     */
    struct Data
    {
        /*!< 节点名称 */
        string node;

        /*!< 节点属性 */
        map<string, string> mapClassAttr;

        /*!< 成员变量 */
        vector<map<string, string>> vecPropertyAttr;

        /*!< 内嵌数据 */
        vector<Data> vecInner;
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
     * @brief 解析类
     */
    bool ParseClass(const XMLElement *cpXmlElement, Data &stData);
    
    /**
     * @brief 解析结构体
     */
    bool ParseStruct(const XMLElement *cpXmlElement, Data &stData);
    
    /**
     * @brief 解析枚举
     */
    bool ParseEnum(const XMLElement *cpXmlElement, Data &stData);

    /**
     * @brief 解析成员
     */
    bool ParseProperty(const XMLElement *cpXmlElement, Data &stData);

    /**
     * @brief 解析属性
     */
    bool ParseAttribute(const XMLElement *cpXmlElement, map<string,string> &mapAttr);


private:
    /*!< 文件名 */
    string m_sFileName;

    /*!< 解析数据 */
    vector<Data> m_vecData;
};

#endif // __PARSEXML_H__

