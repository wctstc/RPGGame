#ifndef __CREATEFILE_H__
#define __CREATEFILE_H__
 
#include <stdarg.h>
 
#include "ParseXML.h"
 
 
/**
* @brief 创建c++源文件
*/
class CreateFile
{
public:
    CreateFile();
    ~CreateFile();

public:
    struct ReplaceMap
    {
        //基础类型
        map<string, string> mapReplace;

        //数组类型
        vector<map<string, string>> mapReplaceList;

        //复合类型
        vector<ReplaceMap> mapMultiReplace;
    };

    class TranslateClass
    {
    public:
        bool Translate(const XMLElement *cpXmlElement, const ParseXML::Data &stData, map<string, string> &mapBase);
    private:
        bool TranslateParam(string &sValue, const char * csParam);
        bool TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase);
        bool TranslateBaseList(
            const XMLElement *cpXmlElement,
            const vector<map<string, string>> vecData,
            vector<map<string, string>> &vecBaseList);
        bool TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase);
    private:
        void Replace(string &sSrcStr, const string sOldStr, const string sNewStr)const;
        void Replace(string &sSrcStr, const map<string, string> &mapReplace)const;
    private:
        //基础属性
        map<string, string> m_mapBase;

        //基础属性
        map<string, vector<map<string, string>>> m_vecBaseList;
    };
public:
    /**
    * @brief 创建源文件
    */
    bool Create(const string sTemplateFile, const ParseXML::Data &stData);
 
private:
    bool Create(const XMLElement *cpXmlElement, const ParseXML::Data &stData);
//    bool CreateClass(const XMLElement *cpXmlElement, const ParseXML::Data &stData, ReplaceMap &stReplaceMap);
//     bool CreateEnum(const XMLElement *cpXmlElement, const ParseXML::Data &stData);
//     bool CreateStruct();

    bool TranslateParam(string &sValue, const char * csParam);
    bool TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase);
    bool TranslateBaseList(
        const XMLElement *cpXmlElement, 
        const vector<map<string, string>> vecData, 
        vector<map<string, string>> &vecBaseList);
    bool TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase);
    bool TranslateEnum(const XMLElement *cpXmlElement, const ParseXML::Data &stData, map<string, string> &mapBase);
    bool TranslateFile(const XMLElement *cpXmlElement, map<string, string> &mapBase);

    string Format(const char *csFormat, ...);
 
    void Replace(string &sSrcStr, const string sOldStr, const string sNewStr)const;
    void Replace(string &sSrcStr, const map<string, string> &mapReplace)const;

private:
    //替换数据
    ReplaceMap m_stReplaceMap;

    //基础属性
    map<string, string> m_mapBase;

    //基础属性
    map<string,vector<map<string, string>>> m_vecBaseList;

    //合成组件
    map<string, string> m_mapCompose;

    //文件
    map<string, string> m_mapFile;
};
 
 
 
#endif // __CREATECPPFILE_H__
