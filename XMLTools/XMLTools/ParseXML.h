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
    struct Data
    {
        string node;
        map<string, string> mapClassAttr;
        vector<map<string,string>> vecPropertyAttr;
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
    string m_sFileName;

    vector<Data> m_vecData;
};

#endif // __PARSEXML_H__

