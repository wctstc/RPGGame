#include "CreateCppFile.h"
#include "FileUtil.h"

#include <iostream>

using namespace std;

CreateCppFile::CreateCppFile()
{
}


CreateCppFile::~CreateCppFile()
{
}

bool CreateCppFile::Create(const ParseXML &oParseXml)
{
    char csBuffer[10240];

    memset(csBuffer, 0, sizeof(csBuffer));
    
    if (!FileUtil::LoadFileWithChar("cpphead.template", csBuffer, 10240))
        return false;

    string sHeadFile = csBuffer;

    memset(csBuffer, 0, sizeof(csBuffer));
    if (!FileUtil::LoadFileWithChar("cppsource.template", csBuffer, 10240))
        return false;

    string sCppFile = csBuffer;
    memset(csBuffer, 0, sizeof(csBuffer));

    m_sClassName = oParseXml.GetStructureData().name;
    string sInnerClass = "";
    string sVariablsArg = GetVariablesArg(oParseXml);
   


    Replace(sHeadFile, "@matro", "___POINT__H_");
    Replace(sHeadFile, "@classname", m_sClassName);
    Replace(sHeadFile, "@variablsarg", sVariablsArg);
    Replace(sHeadFile, "@variablsinit", GetVariablesInit(oParseXml));
    Replace(sHeadFile, "@variablslist", GetVariablesList(oParseXml));
    Replace(sHeadFile, "@variablesetgetimplement", GetVariablesGetSetImplement(oParseXml));
   
    Replace(sCppFile, "@variablsarg", sVariablsArg);
    Replace(sCppFile, "@classname", m_sClassName);
    Replace(sCppFile, "@variablsinit0", GetVariablesInit0(oParseXml));
    Replace(sCppFile, "@variablsinitclassname", GetVariablesInitClassName(oParseXml));
    Replace(sCppFile, "@variablsinitarg", GetVariablesInitArg(oParseXml));
    Replace(sCppFile, "@variablscreateinit", GetVariablesCreateInit(oParseXml));
    cout << sCppFile.c_str() << endl;

    FileUtil::SaveFileWithChar((m_sClassName+".h").c_str(), sHeadFile.c_str(), sHeadFile.length());
    FileUtil::SaveFileWithChar((m_sClassName + ".cpp").c_str(), sCppFile.c_str(),  sCppFile.length());

    return true;
}

string CreateCppFile::Format(const char *csFormat, ...)
{
    char buffer[512];
    va_list ap;

    va_start(ap, csFormat);
    vsprintf_s(buffer, csFormat, ap);
    va_end(ap);

    return buffer;
}

void CreateCppFile::Replace(string &sSrcStr,const string sOldStr,const string sNewStr)const
{
    int iIndex = 0;
    while (iIndex < sSrcStr.length())
    {
        iIndex = sSrcStr.find(sOldStr,iIndex);
        if (iIndex != string::npos)
            sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
        else
            break;
        iIndex += sNewStr.length();
    }
}
// const int iID,
// const string sName,
// const int iHp,
// const int iMaxHp,
// const int iAttack,
// const int iDefance,
// const int iMoney,
// const int iLevel,
// const int iExp,
// const int iTotalExp
const string CreateCppFile::GetVariablesArg(const ParseXML &oParseXml)
{
    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData * pVariableData = oParseXml.GetVariableData(i);
        if (!sTemp.empty())
            sTemp.append(",");

        sTemp.append(Format(
            "const %s %s%s",
            pVariableData->type.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }

    return sTemp;
}
// /*!< 钱 */
// int iMoney;
// 
// /*!< 等级 */
// int iLevel;
// 
// /*!< 当前获得经验 */
// int iExp;
// 
// /*!< 下一级所需经验 */
// int iTotalExp;
const string CreateCppFile::GetVariablesList(const ParseXML &oParseXml)
{

    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData * pVariableData = oParseXml.GetVariableData(i);


        sTemp.append(Format(
            "   %s m_%s%s;\n",
            pVariableData->type.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}
// m_stPlayerData.iMoney = iMoney;
// m_stPlayerData.iLevel = iLevel;
// m_stPlayerData.iExp = iExp;
// m_stPlayerData.iTotalExp = iTotalExp;
const string CreateCppFile::GetVariablesInit(const ParseXML &oParseXml)
{
    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData * pVariableData = oParseXml.GetVariableData(i);


        sTemp.append(Format(
            "m_%s%s = %s%s;\n",
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}
// inline const type Get##name()const\
// {\
// 	return field;\
// }\
// inline void Set##name( const type abbr_type##name )\
// {\
// 	field = abbr_type##name;\
// }
const string CreateCppFile::GetVariablesGetSet(const ParseXML &oParseXml)
{
    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData * pVariableData = oParseXml.GetVariableData(i);

        sTemp.append(Format(
            "    inline const %s Get%s() const;\n\n"
            "    inline void Set%s(const %s %s%s);\n\n",
            pVariableData->type.c_str(),
            pVariableData->name.c_str(),
            pVariableData->name.c_str(),
            pVariableData->type.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}

// inline const type Get##name()const\
// {\
// 	return field;\
// }\
// inline void Set##name( const type abbr_type##name )\
// {\
// 	field = abbr_type##name;\
// }
const string CreateCppFile::GetVariablesGetSetImplement(const ParseXML &oParseXml)
{
    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        const ParseXML::StructureData &stStructureData = oParseXml.GetStructureData();
        sTemp.append(Format(
            "   inline const %s Get%s() const{return m_%s%s;}\n",
            pVariableData->type.c_str(),
            pVariableData->name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }    
    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        const ParseXML::StructureData &stStructureData = oParseXml.GetStructureData();
        sTemp.append(Format(
            "   inline void Set%s(const %s %s%s){m_%s%s = %s%s;}\n",
            pVariableData->name.c_str(),
            pVariableData->type.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;

}

const string CreateCppFile::GetVariablesInit0(const ParseXML &oParseXml)
{
    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        sTemp.append(Format(
            "   m_%s%s = 0;\n",
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}

const string CreateCppFile::GetVariablesInitClassName(const ParseXML &oParseXml)
{
    string sTemp;

    const ParseXML::StructureData &stStructureData = oParseXml.GetStructureData();
    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        sTemp.append(Format(
            "   m_%s%s = o%s.m_%s%s;\n",
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str(),
            stStructureData.name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}

const string CreateCppFile::GetVariablesInitArg(const ParseXML &oParseXml)
{

    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        const ParseXML::StructureData &stStructureData = oParseXml.GetStructureData();
        sTemp.append(Format(
            "   m_%s%s = %s%s;\n",
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str(),
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}

const string CreateCppFile::GetVariablesCreateInit(const ParseXML &oParseXml)
{

    string sTemp;

    for (int i = 0; i < oParseXml.GetVariableDataNum(); ++i)
    {
        const ParseXML::VariableData  *pVariableData = oParseXml.GetVariableData(i);
        const ParseXML::StructureData &stStructureData = oParseXml.GetStructureData();

        if (!sTemp.empty())
            sTemp.append(",\n");

        sTemp.append(Format(
            "   m_%s%s(0)",
            pVariableData->prefix.c_str(),
            pVariableData->name.c_str()));
    }
    return sTemp;
}
