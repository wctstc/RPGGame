#include "CreateFile.h"
#include "FileUtil.h"
#include "StrUtil.h"
 
#include <iostream>
 
using namespace std;


/*!< 属性 */
static const string NODE_ATTR = "base";
static const string NODE_LIST = "list";
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

/*!< Param属性值 */
static const string PARAM_LOWER = "lower";
static const string PARAM_UPPER = "upper";

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
			 if (!TranslateAttr(cpXmlElement, stData.mapAttr, m_mapBase))
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

    vector<string> vecRef;
    StrUtil::Split(sRef, ",", vecRef);

    for (int i = 0; i < vecRef.size(); ++i)
    {
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
    }

	
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
        StrUtil::Replace(sTemp, (*cpVecMap)[i]);
		StrUtil::Replace(sTemp, m_mapBase);

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

bool CreateFile::Translate::Parse(const XMLElement *cpXmlElement, const ParseXML::Data &stData, const map<string, string> &mapParent, map<string, string> &mapBase)
{
    if (cpXmlElement == NULL)
        return false;
    
    const char *csNode = cpXmlElement->Name();

    if (csNode == NULL)
    {
        return false;
    }

    string sNode = csNode;

    if (sNode == NODE_ATTR)
    {
    }
    else if (sNode == NODE_LIST)
    {

    }
    else if (sNode == NODE_COMPOSE)
    {

    }
    else
    {
        return false;
    }
    return true;
}


bool CreateFile::Translate::TranslateAttr(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase)
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


    string sParam = cpXmlElement->Attribute(ATTR_PARAM.c_str());

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


    mapBase.insert(make_pair("#" + sName + "#", sValue));
    return true;
}

bool CreateFile::Translate::TranslateList(const XMLElement *cpXmlElement, const vector<ParseXML::Data> vecData, vector<map<string, string>> &vecBaseList)
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
        if (!translateClass.Translate2(cpChildElement, vecData[i], map<string, string>(), mapBase))
        {
            printf("translate class fail. Line:%d\n", cpChildElement->GetLineNum());
            return false;
        }

        vecBaseList.push_back(mapBase);
    }
    return true;
}
bool CreateFile::Translate::TranslateCompose2(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csRef = cpXmlElement->Attribute(ATTR_REF.c_str());
    const char *csGap = cpXmlElement->Attribute(ATTR_GAP.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        printf("name or ref or gap or text is null, Line:%d\n", cpXmlElement->GetLineNum());
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
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

    vector<string> vecRef;
    StrUtil::Split(sRef, ",", vecRef);

    for (int i = 0; i < vecRef.size(); ++i)
    {
//         if (sRef == NODE_PROPERTY)
//             cpVecMap = &m_vecProperty;
//         if (sRef == NODE_ARRAY_PROPERTY)
//             cpVecMap = &m_vecArrayProperty;
//         else if (sRef == NODE_MACRO)
//             cpVecMap = &m_vecMacro;
//         else if (sRef == NODE_GLOBLE)
//             cpVecMap = &m_vecGlobe;
//         else if (sRef == NODE_CLASS)
//             cpVecMap = &m_vecClass;
//         else if (sRef == NODE_ENUM)
//             cpVecMap = &m_vecEnum;
//         else if (sRef == NODE_STRUCT)
//             cpVecMap = &m_vecStruct;
    }


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
        StrUtil::Replace(sTemp, (*cpVecMap)[i]);
       // StrUtil::Replace(sTemp, m_mapBase);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sTemp);
    }

    mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool Template::Parse(const XMLElement *cpXmlElement, const ParseXML::Data stData)
{
    while (cpXmlElement)
    {
        const char *csNode = cpXmlElement->Name();

        if (csNode == NULL)
            return false;

        string sName = csNode;

        if (sName == NODE_ATTR)
        {
            if (!ParseBase(cpXmlElement, stData))
                return false;
        }
        else if (sName == NODE_COMPOSE)
        {
            if (!ParseCompose(cpXmlElement, stData))
                return false;
        }
        else if (sName == NODE_LIST)
        {
            if (!ParseList(cpXmlElement, stData))
                return false;
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}

bool Template::Parse(const string sFileName, const ParseXML::Data &stData, const Template *cpParent)
{
    XMLDocument xmlDocument;
    XMLError xmlError;

    xmlError = xmlDocument.LoadFile(sFileName.c_str());
    if (xmlError != XML_SUCCESS)
    {
        printf("CreateFile::Create File load fail. File:%s", sFileName.c_str());
        xmlDocument.PrintError();
        return false;
    }

    const XMLElement *cpXmlElement = xmlDocument.FirstChildElement();

    while (cpXmlElement)
    {
        const char *csNode = cpXmlElement->Name();

        if (csNode == NULL)
        {
            printf("CreateFile::Create csNode is NULL.");
            return false;
        }

        string sNode = csNode;

        if (sNode == "class")
        {
            const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();

            Template oTemplate;
            if (!oTemplate.Parse(cpChildElement, stData))
            {
                printf("CreateFile::Create Translate fail");
                return false;
            }
        }
        else if (sNode == "file")
        {
            if (!TranslateFile(cpXmlElement, m_mapFile))
            {
                printf("CreateFile::Create TranslateFile fail");
                return false;
            }
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;

}

bool Template::ParseBase(const XMLElement *cpXmlElement, const ParseXML::Data stData)
{
    if (cpXmlElement == NULL)
        return false;

    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csAttr = cpXmlElement->Attribute(ATTR_ATTR.c_str());
    const char *csParam = cpXmlElement->Attribute(ATTR_PARAM.c_str());

    if (csName == NULL || csAttr == NULL)
        return false;

    const map<string, string>::const_iterator cIt = stData.mapAttr.find(csName);
    
    if (cIt == stData.mapAttr.end())
        return false;

    string sName = csName;
    string sValue = cIt->second;

    if (csParam)
    {
        string sParam = csParam;

        if (sParam == PARAM_LOWER)
        {
            for (unsigned int i = 0; i < sValue.length(); ++i)
                if (sValue[i] >= 'A' && sValue[i] <= 'Z')
                    sValue[i] = sValue[i] - 'A' + 'a';
        }
        else if (sParam == PARAM_UPPER)
        {
            for (unsigned int i = 0; i < sValue.length(); ++i)
                if (sValue[i] >= 'a' && sValue[i] <= 'z')
                    sValue[i] = sValue[i] - 'a' + 'A';
        }
        else
        {
            return false;
        }
    }

    m_stReplaceData.m_mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool Template::ParseCompose(const XMLElement *cpXmlElement, const ParseXML::Data stData)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());
    const char *csRef = cpXmlElement->Attribute(ATTR_REF.c_str());
    const char *csGap = cpXmlElement->Attribute(ATTR_GAP.c_str());
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

    //去除前后回车
    int iFirstEnter = sText.find_first_of('\n') + 1;
    int iLastEnter = sText.find_last_of('\n');

    if (iFirstEnter == string::npos || iLastEnter == string::npos || iFirstEnter >= iLastEnter)
    {
        return false;
    }

    sText = sText.substr(iFirstEnter, iLastEnter - iFirstEnter);

    //替换
    const map<string, vector<ReplaceData>>::const_iterator cmapIt = m_stReplaceData.m_mapList.find(csRef);

    if (cmapIt == m_stReplaceData.m_mapList.end())
        return false;
    
    
    const vector<ReplaceData> &vecReplaceData = cmapIt->second;
    string sSubValue;
    string sValue;

    for (vector<ReplaceData>::const_iterator cvecIt = vecReplaceData.begin(); cvecIt != vecReplaceData.end(); ++cvecIt)
    {
        sSubValue = sText;
        StrUtil::Replace(sSubValue, cvecIt->m_mapBase);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sSubValue);
    }

    m_stReplaceData.m_mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool Template::ParseList(const XMLElement *cpXmlElement, const ParseXML::Data stData)
{
    const char *csName = cpXmlElement->Attribute(ATTR_NAME.c_str());

    if (csName == NULL)
        return false;

    string sName = csName;

    vector<ReplaceData> &vecReplaceData = m_stReplaceData.m_mapList[sName];

    const map<string, vector<ParseXML::Data>>::const_iterator cmapIt = stData.mapChildren.find(sName);

    if (cmapIt != stData.mapChildren.end())
    {
        const vector<ParseXML::Data> &vecData = cmapIt->second;
        for (vector<ParseXML::Data>::const_iterator cvecIt = vecData.begin(); cvecIt != vecData.end(); ++cvecIt)
        {
            Template oTemplate;
            
            if (!oTemplate.Parse(cpXmlElement->FirstChildElement(), (*cvecIt)))
                return false;
            vecReplaceData.push_back(oTemplate.m_stReplaceData);
        }
    }

    return true;
}

bool Template::ParseFile(const XMLElement *cpXmlElement)
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

    StrUtil::Replace(sText, m_stReplaceData.m_mapBase);
    StrUtil::Replace(sFile, m_stReplaceData.m_mapBase);

    mapBase.insert(make_pair(sFile, sText));

    return true;
}
