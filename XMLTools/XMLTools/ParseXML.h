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

        /*!< 节点名字 */
        string name;

        /*!< 节点父类 */
        string parent;

        /*!< 节点属性 */
        map<string, string> mapClassAttr;


		/*!< 属性数据 */
        vector<Data> vecProperty;

        /*!< 数组属性数据 */
        vector<Data> vecArrayProperty;
		
        /*!< 宏数据 */
        vector<Data> vecMacro;

        /*!< 全局数据 */
        vector<Data> vecGloble;

        /*!< 内部类数据 */
		vector<Data> vecClass;

		/*!< 内部枚举数据 */
		vector<Data> vecEnum;

		/*!< 内部结构体数据 */
		vector<Data> vecStruct;

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
    * @brief 解析数组成员
    */
    bool ParseArrayProperty(const XMLElement *cpXmlElement, Data &stData);
    /**
    * @brief 解析宏
    */
    bool ParseMacro(const XMLElement *cpXmlElement, Data &stData);
    /**
    * @brief 解析全局
    */
    bool ParseGloble(const XMLElement *cpXmlElement, Data &stData);

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

