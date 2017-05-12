#ifndef __CREATECPPFILE_H__
#define __CREATECPPFILE_H__

#include <stdarg.h>

#include "ParseXML.h"


/**
 * @brief 创建c++源文件
 */
class CreateCppFile
{
public:
    CreateCppFile();
    ~CreateCppFile();

public:
    /**
     * @brief 创建源文件
     */
    bool Create(const ParseXML &oParseXml);

private:
    string Format(const char *csFormat, ...);

    void Replace(string &sSrcStr, const string sOldStr, const string sNewStr)const;

    const string GetVariablesArg(const ParseXML &oParseXml);
    const string GetVariablesList(const ParseXML &oParseXml);
    const string GetVariablesInit(const ParseXML &oParseXml);
    const string GetVariablesGetSet(const ParseXML &oParseXml);
    const string GetVariablesGetSetImplement(const ParseXML &oParseXml);

    const string GetVariablesInit0(const ParseXML &oParseXml);
    const string GetVariablesInitClassName(const ParseXML &oParseXml);
    const string GetVariablesInitArg(const ParseXML &oParseXml);
    const string GetVariablesCreateInit(const ParseXML &oParseXml);
private:
    string m_sClassName;

};



#endif // __CREATECPPFILE_H__
