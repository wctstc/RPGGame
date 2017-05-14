#include "CreateFile.h"
#include "FileUtil.h"
 
#include <iostream>
 
using namespace std;

/*!< 属性 */
static const string NODE_ATTR    = "base";
static const string NODE_COMPOSE = "compose";

/*!< 列表 */
static const string NODE_PROPERTY = "property";
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

bool CreateFile::Create(const string sTemplateFile, const ParseXML::Data &stData)
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
			if (!translateClass.Translate2(cpChildElement, stData, m_mapBase))
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

	for (map<string, string>::const_iterator cmIt = m_mapFile.begin(); cmIt != m_mapFile.end(); ++cmIt)
	{
		FileUtil::SaveFileWithChar(cmIt->first, cmIt->second.c_str(), cmIt->second.length());
	}

//     if (!Create(cpXmlElement,stData))
//     {
//         printf("CreateFile::Create Create fail");
//         return false;
//     }

    return true;
}

bool CreateFile::Create(const XMLElement *cpXmlElement, const ParseXML::Data &stData)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::Create XmlElement is null");
        return false;
    }

    while (cpXmlElement)
    {
        const char *csType = cpXmlElement->Attribute("type");
        if (csType == NULL)
        {
            printf("CreateFile::Create Type Attr is null. Node:%s, Line:%d", cpXmlElement->Name(), cpXmlElement->GetLineNum());
            return false;
        }

        string sType = csType;
        if (sType == "base")
        {
            if (!TranslateBase(cpXmlElement, stData.mapClassAttr, m_mapBase))
            {
                printf("CreateFile::Create TranslateBase fail.");
                return false;
            }
        }
        else if (sType == "list")
        {
            vector<map<string, string>> vecBaseList;

            if (!TranslateBaseList(cpXmlElement, stData.vecPropertyAttr, vecBaseList))
            {
                printf("CreateFile::Create TranslateBaseList fail.");
                return false;
            }

            const char *csName = cpXmlElement->Name();
            if (csName == NULL)
            {
                printf("CreateFile::Create Name is null");
                return false;
            }
            m_vecBaseList.insert(make_pair(csName, vecBaseList));
        }
        else if (sType == "compose")
        {
            if (!TranslateCompose(cpXmlElement, m_mapCompose))
            {
                printf("CreateFile::Create TranslateCompose fail.");
                return false;
            }
        }
        else if (sType == "enum")
        {
            vector<map<string, string>> vecEnum;
            for (unsigned int i = 0; i < stData.vecInner.size(); ++i)
            {
                map<string, string> mapEnum;
				const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
				if (cpChildElement == NULL)
				{
					printf("CreateFile::Create ChildElement is null");
					return false;
				}

                if (!TranslateEnum(cpChildElement, stData.vecInner[i], mapEnum))
                {
                    printf("CreateFile::Create TranslateCompose fail.");
                    return false;
                }
                vecEnum.push_back(mapEnum);
            }
            m_vecBaseList.insert(make_pair("enum_class", vecEnum)); 
        }
        else if (sType == "file")
        {
            if (!TranslateFile(cpXmlElement, m_mapFile))
            {
                printf("CreateFile::Create TranslateFile fail.");
                return false;
            }
        }

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }
    return true;
}


bool CreateFile::TranslateParam(string &sValue, const char * csParam)
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
        printf("CreateFile::TranslateParam Param is error. Param:%s", sParam.c_str());
        return false;
    }
    return true;
}

bool CreateFile::TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string,string> &mapBase)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBase XmlElement is null");
        return false;
    }

    const char *csName = cpXmlElement->Name();
    const char *csNode = cpXmlElement->Attribute("node");
    const char *csAttr = cpXmlElement->Attribute("attr");
    const char *csParam = cpXmlElement->Attribute("param");

    if (csName == NULL || csNode == NULL || csAttr == NULL)
        return false;
    string sName = csName;
    string sNode = csNode;
    string sAttr = csAttr;

    map<string, string>::const_iterator mIt = mapData.find(sAttr);
    if (mIt == mapData.end())
    {
        printf("CreateFile::TranslateBase class attr can't find. Name:%s  Attr:%s", sName.c_str(), sAttr.c_str());
        return false;
    }
    string sValue = mIt->second;
    if (!TranslateParam(sValue, cpXmlElement->Attribute("param")))
    {
        printf("CreateFile::TranslateBase TranslateParam fail.");
        return false;
    }

    mapBase.insert(make_pair("#" + sName + "#", sValue));
    return true;
}

bool CreateFile::TranslateBaseList(
    const XMLElement *cpXmlElement, 
    const vector<map<string, string>> vecData, 
    vector<map<string, string>> &vecBaseList)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBaseList XmlElement is null");
        return false;
    }

    for (unsigned int i = 0; i < vecData.size(); ++i)
    {
        const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
        map<string, string> mapBase;
        while (cpChildElement)
        {
            if (!TranslateBase(cpChildElement, vecData[i], mapBase))
            {
                printf("CreateFile::TranslateBaseList TranslateBase fail. i:%d", i);
                return false;
            }

            cpChildElement = cpChildElement->NextSiblingElement();
        }

        vecBaseList.push_back(mapBase);
    }
    return true;
}

bool CreateFile::TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Name();
    const char *csRef = cpXmlElement->Attribute("ref");
    const char *csGap = cpXmlElement->Attribute("gap");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateCompose Node or Param or Gap or Text is null");
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

    sText = sText.substr(1, sText.length() - 2);

    map<string, vector<map<string, string>>>::const_iterator mIt = m_vecBaseList.find(sRef);
    if (mIt == m_vecBaseList.end())
    {
        printf("CreateFile::TranslateCompose Ref can't find. Ref:%s", sRef.c_str());
        return false;
    }

    string sValue;
    for (unsigned int i = 0; i < mIt->second.size(); ++i)
    {
        string sTemp = sText;
        Replace(sTemp, m_mapBase);
        Replace(sTemp, (mIt->second)[i]);
        Replace(sTemp, m_mapCompose);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sTemp);
    }

    mapBase.insert(make_pair("#" + sName + "#", sValue));

    return true;
}

bool CreateFile::TranslateEnum(const XMLElement *cpXmlElement, const ParseXML::Data &stData, map<string, string> &mapBase)
{
    TranslateClass translateClass;
    if (!translateClass.Translate(cpXmlElement, stData, mapBase))
    {
        printf("CreateFile::TranslateEnum Translate fail.");
        return false;
    }
    return true;
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

    Replace(sText, m_mapBase);
    Replace(sText, m_mapCompose);

    mapBase.insert(make_pair(sName, sText));

    return true;
}

string CreateFile::Format(const char *csFormat, ...)
{
    char buffer[512];
    va_list ap;
 
    va_start(ap, csFormat);
    vsprintf_s(buffer, csFormat, ap);
    va_end(ap);
 
    return buffer;
}
 
void CreateFile::Replace(string &sSrcStr,const string sOldStr,const string sNewStr)const
{
    for( int iIndex = 0; iIndex < sSrcStr.length(); iIndex += sNewStr.length())
    {
        iIndex = sSrcStr.find(sOldStr,iIndex);
        if (iIndex == string::npos)
            break;
        
        sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
    }
}

void CreateFile::Replace(string &sSrcStr, const map<string, string> &mapReplace) const
{
    map<string, string>::const_iterator cmIt;
    for (cmIt = mapReplace.begin(); cmIt != mapReplace.end(); ++cmIt)
    {
        Replace(sSrcStr, cmIt->first, cmIt->second);
    }
}


 bool CreateFile::TranslateClass::Translate(const XMLElement *cpXmlElement, const ParseXML::Data &stData, std::map<string, string> &mapBase)
{
    m_mapBase.clear();

    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateClass::Create XmlElement is null");
        return false;
    }

    while (cpXmlElement)
    {
        const char *csType = cpXmlElement->Attribute("type");
        if (csType == NULL)
        {
            printf("CreateFile::TranslateClass::Create Type Attr is null. Node:%s, Line:%d", cpXmlElement->Name(), cpXmlElement->GetLineNum());
            return false;
        }

        string sType = csType;
        if (sType == "base")
        {
            if (!TranslateBase(cpXmlElement, stData.mapClassAttr, m_mapBase))
            {
                printf("CreateFile::TranslateClass::Create TranslateBase fail.");
                return false;
            }
        }
        else if (sType == "list")
        {
            vector<map<string, string>> vecBaseList;

            if (!TranslateBaseList(cpXmlElement, stData.vecPropertyAttr, vecBaseList))
            {
                printf("CreateFile::TranslateClass::Create TranslateBaseList fail.");
                return false;
            }

            const char *csName = cpXmlElement->Name();
            if (csName == NULL)
            {
                printf("CreateFile::TranslateClass::Create Name is null");
                return false;
            }
            m_vecBaseList.insert(make_pair(csName, vecBaseList));
        }
        else if (sType == "compose")
        {
            if (!TranslateCompose(cpXmlElement, m_mapBase))
            {
                printf("CreateFile::TranslateClass::Create TranslateCompose fail.");
                return false;
            }
		}
		else if (sType == "enum")
		{
			vector<map<string, string>> vecEnum;
			for (unsigned int i = 0; i < stData.vecInner.size(); ++i)
			{
				map<string, string> mapEnum;
				const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
				if (cpChildElement == NULL)
				{
					printf("CreateFile::Create ChildElement is null");
					return false;
				}

				TranslateClass translateClass;
				if (!translateClass.Translate(cpChildElement, stData.vecInner[i], mapEnum))
				{
					printf("CreateFile::TranslateEnum Translate fail.");
					return false;
				}
				vecEnum.push_back(mapEnum);
			}
			m_vecBaseList.insert(make_pair("enum_class", vecEnum));
		}

        cpXmlElement = cpXmlElement->NextSiblingElement();
    }

    mapBase = m_mapBase;
    return true;
}

 bool CreateFile::TranslateClass::Translate2(const XMLElement *cpXmlElement, const ParseXML::Data &stData, map<string, string> &mapBase)
 {
	 m_mapBase.clear();

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

bool CreateFile::TranslateClass::TranslateBase(const XMLElement *cpXmlElement, const map<string, string> &mapData, map<string, string> &mapBase)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateClass::TranslateBase XmlElement is null");
        return false;
    }

    const char *csName = cpXmlElement->Name();
    const char *csNode = cpXmlElement->Attribute("node");
    const char *csAttr = cpXmlElement->Attribute("attr");
    const char *csParam = cpXmlElement->Attribute("param");

    if (csName == NULL || csNode == NULL || csAttr == NULL)
        return false;
    string sName = csName;
    string sNode = csNode;
    string sAttr = csAttr;

    map<string, string>::const_iterator mIt = mapData.find(sAttr);
    if (mIt == mapData.end())
    {
        printf("CreateFile::TranslateBase class attr can't find. Name:%s  Attr:%s", sName.c_str(), sAttr.c_str());
        return false;
    }
    string sValue = mIt->second;
    if (!ConvertParam(sValue, cpXmlElement->Attribute("param")))
    {
        printf("CreateFile::TranslateBase TranslateParam fail.");
        return false;
    }

    mapBase.insert(make_pair("#" + sName + "#", sValue));
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

bool CreateFile::TranslateClass::TranslateBaseList(const XMLElement *cpXmlElement, const vector<map<string, string>> vecData, vector<map<string, string>> &vecBaseList)
{
    if (cpXmlElement == NULL)
    {
        printf("CreateFile::TranslateBaseList XmlElement is null");
        return false;
    }

    for (unsigned int i = 0; i < vecData.size(); ++i)
    {
        const XMLElement *cpChildElement = cpXmlElement->FirstChildElement();
        map<string, string> mapBase;
        while (cpChildElement)
        {
            if (!TranslateBase(cpChildElement, vecData[i], mapBase))
            {
                printf("CreateFile::TranslateBaseList TranslateBase fail. i:%d", i);
                return false;
            }

            cpChildElement = cpChildElement->NextSiblingElement();
        }

        vecBaseList.push_back(mapBase);
    }
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
		if (!translateClass.Translate2(cpChildElement, vecData[i], mapBase))
		{
			printf("translate class fail. Line:%d\n", cpChildElement->GetLineNum());
			return false;
		}

		vecBaseList.push_back(mapBase);
	}
	return true;
}

bool CreateFile::TranslateClass::TranslateCompose(const XMLElement *cpXmlElement, map<string, string> &mapBase)
{
    const char *csName = cpXmlElement->Name();
    const char *csRef = cpXmlElement->Attribute("ref");
    const char *csGap = cpXmlElement->Attribute("gap");
    const char *csText = cpXmlElement->GetText();

    if (csName == NULL || csRef == NULL || csGap == NULL || csText == NULL)
    {
        printf("CreateFile::TranslateCompose Node or Param or Gap or Text is null");
        return false;
    }

    string sName = csName;
    string sRef = csRef;
    string sGap = csGap;
    string sText = csText;

	int iFirstEnter = sText.find_first_of('\n')+1;
	int iLastEnter = sText.find_last_of('\n');
    sText = sText.substr(iFirstEnter, iLastEnter- iFirstEnter);

    map<string, vector<map<string, string>>>::const_iterator mIt = m_vecBaseList.find(sRef);
    if (mIt == m_vecBaseList.end())
    {
        printf("CreateFile::TranslateCompose Ref can't find. Ref:%s", sRef.c_str());
        return false;
    }

    string sValue;
    for (unsigned int i = 0; i < mIt->second.size(); ++i)
    {
        string sTemp = sText;
        Replace(sTemp, m_mapBase);
        Replace(sTemp, (mIt->second)[i]);

        if (!sValue.empty())
            sValue.append(sGap);

        sValue.append(sTemp);
    }

    mapBase.insert(make_pair("#" + sName + "#", sValue));

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

	if (sRef == NODE_PROPERTY)
		cpVecMap = &m_vecProperty;
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
		Replace(sTemp, m_mapBase);
		Replace(sTemp, (*cpVecMap)[i]);

		if (!sValue.empty())
			sValue.append(sGap);

		sValue.append(sTemp);
	}

	mapBase.insert(make_pair("#" + sName + "#", sValue));

	return true;
}

void CreateFile::TranslateClass::Replace(string &sSrcStr, const string sOldStr, const string sNewStr) const
{
    for ( int iIndex = 0; iIndex < sSrcStr.length(); iIndex += sNewStr.length())
    {
        iIndex = sSrcStr.find(sOldStr, iIndex);
        if (iIndex == string::npos)
            break;

        sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
    }
}

void CreateFile::TranslateClass::Replace(string &sSrcStr, const map<string, string> &mapReplace) const
{
    map<string, string>::const_iterator cmIt;
    for (cmIt = mapReplace.begin(); cmIt != mapReplace.end(); ++cmIt)
    {
        Replace(sSrcStr, cmIt->first, cmIt->second);
    }
}
