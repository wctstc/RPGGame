
#include "tinyxml2.h"

#include "ParseXML.h"
#include "FileUtil.h"
#include "CreateFile.h"


#include <iostream>
#include <map>
#include <string>


using namespace std;
using namespace tinyxml2;


void Replace(string &sSrcStr, const string sOldStr, const string sNewStr)
{
    int iIndex = 0;
    while (iIndex < sSrcStr.length())
    {
        iIndex = sSrcStr.find(sOldStr, iIndex);
        if (iIndex != string::npos)
            sSrcStr.replace(iIndex, sOldStr.length(), sNewStr);
        else
            break;
        iIndex += sNewStr.length();
    }
}

int main()
{
    XMLDocument xmlDocument;
    XMLError xmlError = xmlDocument.LoadFile("Class.xml");
    if (xmlError != XML_SUCCESS)
    {
        cout << xmlError << endl;
        return 0;
    }

    ParseXML parseXml;

    parseXml.Parse("Class.xml");

    const vector<ParseXML::Data>& vecData = parseXml.GetData();

    CreateFile createFile;
    for (unsigned int i = 0; i < vecData.size(); ++i)
    {
        if (!createFile.Create("template.xml", vecData[i]))
        {
            break;
        }
    }

    system("pause");
    return 0;
}

