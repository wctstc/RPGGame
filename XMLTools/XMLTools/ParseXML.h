#ifndef __PARSEXML_H__
#define __PARSEXML_H__

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "tinyxml2.h"

using namespace tinyxml2;

/**
 * @brief 解析xml
 */

class ParseXML
{
public:
    /**
     * @brief 结构类型枚举
     */
    enum Type
    {
        /*!< 未知类型 */
        UNKNOWN,

        /*!< 类 */
        CLASS,

        /*!< 结构体 */
        STRUCT,

        /*!< 枚举 */
        ENUM,
    };
    /**
     * @brief 结构数据结构
     */
    struct StructureData
    {
        /*!< 结构类型 */
        Type type;

        /*!< 结构名字 */
        string name;
    };
    /**
     * @brief 变量数据结构
     */
    struct VariableData
    {
        /*!< 变量名 */
        string name;

        /*!< 变量类型 */
        string type;

        /*!< 类型前缀 */
        string prefix;

        /*!< 类型格式化输出 */
        string format;

        /*!< 注释 */
        string comment;
    };


public:
    ParseXML();
    ~ParseXML();

public:
    /**
     * @brief 解析xml
     */
    bool Parse( const XMLElement *cpXmlElement);
    
    /**
     * @brief 获取类型
     */
    const ParseXML::Type GetType() const;

    /**
     * @brief 获取结构数据
     */
    const StructureData &GetStructureData()const;


    /**
     * @brief 获取变量数量
     */
    int GetVariableDataNum()const;


    /**
     * @brief 获取变量数据
     */
    const VariableData *GetVariableData(int iIndex)const;

private:
    /**
    * @brief 解析类
    */
    bool ParseClass(const XMLElement *cpXmlElement);
    
    /**
     * @brief 解析结构体
     */
    bool ParseStruct(const XMLElement *cpXmlElement);
    
    /**
     * @brief 解析枚举
     */
    bool ParseEnum(const XMLElement *cpXmlElement);

    /**
     * @brief 判断变量类型是否正确
     */
    bool CheckVariableType(const string type);

    /**
     * @brief 根据变量类型获取前缀
     */
    string GetPrefixByVariableType(const string type);

    /**
     * @brief 根据变量类型获取格式输出
     */
    string GetFormatByVariableType(const string type);
private:
    /*!< 结构数据 */
    StructureData m_stStructureData;

    /*!< 变量数据 */
    vector<VariableData> m_vVariables;


};

#endif // __PARSEXML_H__

