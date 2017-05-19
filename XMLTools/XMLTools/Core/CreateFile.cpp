#include "CreateFile.h"
#include "FileUtil.h"
#include "StrUtil.h"
 
#include <iostream>
 
using namespace std;

/*!< 属性 */
static const string NODE_ATTR = "base";
static const string NODE_PARENT = "parent";
static const string NODE_COMPOSE = "compose";

/*!< 列表 */
static const string NODE_PROPERTY = "property";
static const string NODE_ARRAY_PROPERTY = "array_property";
static const string NODE_MACRO    = "macro";
static const string NODE_GLOBLE   = "globle";
static const string NODE_CLASS    = "class";
static const string NODE_ENUM     = "enum";
static const string NODE_STRUCT   = "struct";


/*!< xml属性 全节点固有属性 */
static const string ATTR_NAME = "name";

/*!< xml属性 NODE_ATTR节点属性 */
static const string ATTR_NODE    = "node";
static const string ATTR_ATTR    = "attr";
static const string ATTR_PARAM   = "param";

/*!< xml属性 NODE_COMPOSE节点属性 */
static const string ATTR_REF = "ref";
static const string ATTR_GAP = "gap";

CreateFile::CreateFile()
{
}
 
 
CreateFile::~CreateFile()
{
}

bool CreateFile::Create(const string sTemplateFile, const ParseXML::Data &stData, const map<string,string> &mapParent)
{
    XMLDocument xmlDocument;
    XMLError xmlError;

    xmlError = xmlDocument.LoadFile(sTemplateFile.c_str());
    if (xmlError != XML_SUCCESS)
    {
        printf("CreateFile::Create File load fail. File:%s", sTemplateFile.c_str());
        xmlDocument.PrintError();
        return false;
    }

    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

	while (cpXmlElement)
	{
		const char *csType = cpXmlElement->Attribute("type");

		if (csType == NULL)
		{
			printf("CreateFile::Create Type is NULL.");
			return false;
		}

		string sType = csType;

		if (sType == "class")
		{
			const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

			TranslateClass translateClass;
			if (!translateClass.Translate2(cpChildElement, stData,mapParent, m_mapBase))
			{
				printf("CreateFile::Create Translate fail");
				return false;
			}
		}
		else if(sType == "file")
		{
			if (!TranslateFile(cpXmlElement, m_mapFile))
			{
				printf("CreateFile::Create TranslateFile fail");
				return false;
			}
		}


		cpXmlElement = cpXmlElement->NextSiblingElement();
	}

// 	for (map<string, string>::const_iterator cmIt = m_mapFile.begin(); cmIt != m_mapFile.end(); ++cmIt)
// 	{
// 		FileUtil::SaveFileWithChar(cmIt->first, cmIt->second.c_str(), cmIt->second.length());
// 	}

//     if (!Create(cpXmlElement,stData))
//     {
//         printf("CreateFile::Create Create fail");
//         return false;
//     }

    return true;
}

const map<string, string> & CreateFile::GetBase()
{
    return m_mapBase;
}

const map<string, string> & CreateFile::GetFile()
{
    return m_mapFile;
}

bool CreateFile::TranslateFile(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Name();
    const char *csFile = cpXmlElement->Attribute("file");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csFile == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateFile Node or File or Text is null");
        return false;
    }

    string sName = csName;
    string sFile = csFile;
    string sText = csText;

    StrUtil::Replace(sText, m_mapBase);
    StrUtil::Replace(sFile, m_mapBase);

    mapBase.insert(make_pair(sFile, sText));

    return true;
}

 bool CreateFile::TranslateClass::Translate2(
     const XMLElement *cpXmlElement, 
     const ParseXML::Data &stData, 
     const map<string, string> &mapParent, 
     map<string, string> &mapBase)
 {
	 m_mapBase.clear();

     for (map<string, string>::const_iterator mapIt = mapParent.begin(); mapIt != mapParent.end(); ++mapIt)
     {
         m_mapParent.insert(make_pair("#parent#"+mapIt->first, mapIt->second));
     }

	 if (cpXmlElement == NULL)
	 {
		 printf("xml element is null\n");
		 return false;
	 }

	 while (cpXmlElement)
	 {
		 const char *csNode = cpXmlElement->Name();
		 if (csNode == NULL)
		 {
			 printf("node is null. Line:%d", cpXmlElement->GetLineNum());
			 return false;
		 }

		 string sNode = csNode;
		 if (sNode == NODE_ATTR)
		 {
			 if (!TranslateAttr(cpXmlElement, stData.mapClassAttr, m_mapBase))
			 {
				 printf("CreateFile::TranslateClass::Create TranslateBase fail.");
				 return false;
			 }
         }
         if (sNode == NODE_PARENT)
         {
             if (!TranslateParent(cpXmlElement, m_mapBase))
             {
                 printf("CreateFile::TranslateClass::Create TranslateBase fail.");
                 return false;
             }
         }
		 else if (sNode == NODE_COMPOSE)
		 {
			 if (!TranslateCompose2(cpXmlElement, m_mapBase))
			 {
				 printf("translate compose fail. Line:%d\n", cpXmlElement->GetLineNum());
				 return false;
			 }
		 }
		 else if (sNode == NODE_PROPERTY)
		 {
			 if (!TranslateList(cpXmlElement, stData.vecProperty, m_vecProperty))
			 {
				 printf("translate list fail.Line:%d Node:%s\n",
					 cpXmlElement->GetLineNum(), sNode.c_str());
				 return false;
			 }
         }
         else if (sNode == NODE_ARRAY_PROPERTY)
         {
             if (!TranslateList(cpXmlElement, stData.vecArrayProperty, m_vecArrayProperty))
             {
                 printf("translate list fail.Line:%d Node:%s\n",
                     cpXmlElement->GetLineNum(), sNode.c_str());
                 return false;
             }
         }
         else if (sNode == NODE_MACRO)
         {
             if (!TranslateList(cpXmlElement, stData.vecMacro, m_vecMacro))
             {
                 printf("translate list fail.Line:%d Node:%s\n",
                     cpXmlElement->GetLineNum(), sNode.c_str());
                 return false;
             }
         }
         else if (sNode == NODE_GLOBLE)
         {
             if (!TranslateList(cpXmlElement, stData.vecGloble, m_vecGlobe))
             {
                 printf("translate list fail.Line:%d Node:%s\n",
                     cpXmlElement->GetLineNum(), sNode.c_str());
                 return false;
             }
         }
		 else if (sNode == NODE_CLASS)
		 {
			 if (!TranslateList(cpXmlElement, stData.vecClass, m_vecClass))
			 {
				 printf("translate list fail.Line:%d Node:%s\n",
					 cpXmlElement->GetLineNum(), sNode.c_str());
				 return false;
			 }
		 }
		 else if (sNode == NODE_ENUM)
		 {
			 if (!TranslateList(cpXmlElement, stData.vecEnum, m_vecEnum))
			 {
				 printf("translate list fail.Line:%d Node:%s\n",
					 cpXmlElement->GetLineNum(), sNode.c_str());
				 return false;
			 }
		 }
		 else if (sNode == NODE_STRUCT)
		 {
			 if (!TranslateList(cpXmlElement, stData.vecStruct, m_vecStruct))
			 {
				 printf("translate list fail.Line:%d Node:%s\n",
					 cpXmlElement->GetLineNum(), sNode.c_str());
				 return false;
			 }
		 }

		 cpXmlElement = cpXmlElement->NextSiblingElement();
	 }

	 mapBase = m_mapBase;
	 return true;
 }

 bool CreateFile::TranslateClass::ConvertParam(string &sValue, const char * csParam)
{
    if (csParam == NULL)
        return true;

    string sParam = csParam;

    if (sParam == "lower")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'A' && sValue[i] <= 'Z')
                sValue[i] = sValue[i] - 'A' + 'a';
    }
    else if (sParam == "upper")
    {
        for (unsigned int i = 0; i < sValue.length(); ++i)
            if (sValue[i] >= 'a' && sValue[i] <= 'z')
                sValue[i] = sValue[i] - 'a' + 'A';
    }
    else
    {
        printf("param is error. Param:%s", sParam.c_str());
        return false;
    }
    return true;
}

bool CreateFile::TranslateClass::TranslateAttr(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase)
{
	if (cpXmlElement == NULL)
	{
		printf("xmlelement is null\n");
		return false;
	}

	const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
	const char *csAttr = cpXmlElement->Attribute(ATTR_ATTR.c_str());

	if (csName == NULL || csAttr == NULL)
		return false;

	string sName = csName;
	string sAttr = csAttr;

	map<string, string>::const_iterator mIt = mapData.find(sAttr);
	if (mIt == mapData.end())
	{
		printf("attr can't find. Line:%d Name:%s  Attr:%s\n", cpXmlElement->GetLineNum(), sName.c_str(), sAttr.c_str());
		return false;
	}

	string sValue = mIt->second;
	if (!ConvertParam(sValue, cpXmlElement->Attribute(ATTR_PARAM.c_str())))
	{
		printf("convert param fail. Line:%d\n", cpXmlElement->GetLineNum());
		return false;
	}

	mapBase.insert(make_pair("#" + sName + "#", sValue));
	return true;
}

bool CreateFile::TranslateClass::TranslateList(const XMLElement *cpXmlElement, const vector<ParseXML::Data> vecData, vector<map<string, string>> &vecBaseList)
{
	if (cpXmlElement == NULL)
	{
		printf("xmlelement is null\n");
		return false;
	}

	for (unsigned int i = 0; i < vecData.size(); ++i)
	{
		const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

		map<string, string> mapBase;
		TranslateClass translateClass;
		if (!translateClass.Translate2(cpChildElement, vecData[i], map<string,string>(),mapBase))
		{
			printf("translate class fail. Line:%d\n", cpChildElement->GetLineNum());
			return false;
		}

		vecBaseList.push_back(mapBase);
	}
	return true;
}
bool CreateFile::TranslateClass::TranslateCompose2(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
	const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
	const char *csRef  = cpXmlElement->Attribute(ATTR_REF.c_str());
	const char *csGap  = cpXmlElement->Attribute(ATTR_GAP.c_str());
	const char *csText = cpXmlElement->GetText();

	if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
	{
		printf("name or ref or gap or text is null, Line:%d\n", cpXmlElement->GetLineNum());
		return false;
	}

	string sName = csName;
	string sRef  = csRef;
	string sGap  = csGap;
	string sText = csText;

	//去除前后回车
	int iFirstEnter = sText.find_first_of('\n') + 1;
	int iLastEnter = sText.find_last_of('\n');

	if (iFirstEnter == string::npos || iLastEnter == string::npos || iFirstEnter >= iLastEnter)
	{
		printf("text should has two enter at least. Line:%d\n", cpXmlElement->GetLineNum());
		return false;
	}

	sText = sText.substr(iFirstEnter, iLastEnter - iFirstEnter);

	//替换
	const vector<map<string, string>> *cpVecMap = NULL;

    if (sRef == NODE_PROPERTY)
        cpVecMap = &m_vecProperty;
    if (sRef == NODE_ARRAY_PROPERTY)
        cpVecMap = &m_vecArrayProperty;
    else if (sRef == NODE_MACRO)
        cpVecMap = &m_vecMacro;
    else if (sRef == NODE_GLOBLE)
        cpVecMap = &m_vecGlobe;
    else if (sRef == NODE_CLASS)
		cpVecMap = &m_vecClass;
	else if (sRef == NODE_ENUM)
		cpVecMap = &m_vecEnum;
	else if (sRef == NODE_STRUCT)
		cpVecMap = &m_vecStruct;

	
	if (cpVecMap == NULL)
	{
		printf("ref is not list or class or enum or strcut.Line:%d Ref:%s\n",
			cpXmlElement->GetLineNum(), sRef.c_str());
		return false;
	}

	string sValue;
	for (unsigned int i = 0; i < cpVecMap->size(); ++i)
	{
		string sTemp = sText;
		StrUtil::Replace(sTemp, m_mapBase);
        StrUtil::Replace(sTemp, (*cpVecMap)[i]);

		if (!sValue.empty())
			sValue.append(sGap);

		sValue.append(sTemp);
	}

	mapBase.insert(make_pair("#" + sName + "#", sValue));

	return true;
}

bool CreateFile::TranslateClass::TranslateParent(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csText == NULL)
    {
        printf("name or text is null, Line:%d\n", cpXmlElement->GetLineNum());
        return false;
    }

    string sName = csName;
    string sText = csText;

    //去除前后回车
    int iFirstEnter = sText.find_first_of('\n') + 1;
    int iLastEnter = sText.find_last_of('\n');

    if (iFirstEnter == string::npos || iLastEnter == string::npos || iFirstEnter >= iLastEnter)
    {
        printf("text should has two enter at least. Line:%d\n", cpXmlElement->GetLineNum());
        return false;
    }

    sText = sText.substr(iFirstEnter, iLastEnter - iFirstEnter);

    //替换
    if (m_mapParent.empty())
    {
        mapBase.insert(make_pair("#" + sName + "#", ""));
    }
    else
    {
        StrUtil::Replace(sText, m_mapParent);
        StrUtil::Replace(sText, m_mapBase);

        mapBase.insert(make_pair("#" + sName + "#", sText));
    }

    return true;
}
