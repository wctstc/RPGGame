#include "TestUnit.h"

#include <iostream>

using std::cout;
using std::endl;


#include "UIBase.h"

#include "StrUtil.h"
#include "Pointer.h"
#include "App.h"
#include "FrameWithOption.h"
#include "PropertyFrame.h"
#include "Log.h"
#include "MapActionLoader.h"
#include "MonsterLoader.h"
#include "DropLoader.h"
#include "DataConfig.h"


TestUnit::TestUnit()
{
}


TestUnit::~TestUnit()
{
}

void TestUnit::Run()
{
    //TEST(TestStrUtilSplit);
    //TEST(TestStrUtilFormat);
    //TEST(TestPointer);
    //TEST(TestFrame);
    //TEST(TestPropertyFrame);
    //TEST(TestProtobuf);
    //TEST(TestLog);
    //TEST(TestMapConfig);
    TEST(TestMacro);



    system("pause");
    clear();
}

bool TestUnit::TestStrUtilSplit()
{
    string cbuffer = "aassfdfsaldfkjsfsaljksfhgkhglksfhfksdafksadhfsflkassfsnffksdasfndasfsfklfnasf";
    string ssepetor = "sf";
    vector<string> sbuffer;
    StrUtil::Split(cbuffer, ssepetor, sbuffer);
    for (vector<string>::iterator it = sbuffer.begin(); it != sbuffer.end(); ++it)
    {
        cout << (*it).c_str() << endl;
    }
    return true;
}

bool TestUnit::TestStrUtilFormat()
{
    cout << StrUtil::Format("abc%d,%d,%s",10,23,"asdf").c_str() << endl;
    return true;
}

bool TestUnit::TestPointer()
{

    {
        CPointer<App> oPointer = new App();

        if (oPointer->Init())
            cout << "init succeed" << endl;

        CPointer<App>::LogCount();
        CPointer<App> oPointer1;
        CPointer<App>::LogCount();
        CPointer<App> oPointer2 = oPointer;
        CPointer<App>::LogCount();
        CPointer<App> oPointer3 = oPointer1;
        CPointer<App>::LogCount();

        CPointer<App> oPointer4;
        CPointer<App>::LogCount();
        oPointer4 = oPointer;
        CPointer<App>::LogCount();

        CPointer<App> oPointer5;
        CPointer<App>::LogCount();
        oPointer5 = new App();
        CPointer<App>::LogCount();

        CPointer<App> oPointer6;
        CPointer<App>::LogCount();
        oPointer6 = oPointer;
        CPointer<App>::LogCount();
        oPointer6 = oPointer6;
        CPointer<App>::LogCount();


        App* pApp = NULL;
        CPointer<App>::LogCount();
        pApp = oPointer1;
        CPointer<App>::LogCount();
        pApp = oPointer;
        CPointer<App>::LogCount();
    }
    CPointer<App>::LogCount();

    return true;
}

bool TestUnit::TestFrame()
{
    FrameWithOption frame;

    data::FrameData stFrameData;
    stFrameData.eDirection = data::DIRECTION_VERTICAL;
    stFrameData.iHandlerID = 0;
    stFrameData.iID = 0;
    stFrameData.oPosition.iX = 0;
    stFrameData.oPosition.iY = 0;
    stFrameData.oSize.iWidth = 20;
    stFrameData.oSize.iHeigth = 10;
    stFrameData.sDescription = "adsfasfd\nadsfalasdfasdfsadfsasdfsadfsafsafsfsfsafsadfasdfdf\nksdjf";
    data::Option option;
    option.sDescription = "world";
    stFrameData.vOptions.push_back(option);
    option.sDescription = "hello!";
    stFrameData.vOptions.push_back(option);


    frame.Init(stFrameData);
    frame.Show();
    int iIndex = frame.GetSelectIndex();
    return true;
}

bool TestUnit::TestPropertyFrame()
{
    PropertyFrame &oPropertyFrame = PropertyFrame::GetInstance();

    oPropertyFrame.Init();
    oPropertyFrame.Show();

    return true;
}

#include "Struct.h"
#include "dataconfig_item.pb.h"
bool TestUnit::TestProtobuf()
{
    dataconfig::ITEM item;
    item.set_type(2);

    const google::protobuf::Descriptor *pDes = item.GetDescriptor();

    return true;
}

bool TestUnit::TestLog()
{

    GLog(Log::LOG_DEBUG, "Test Test");

    Log m_Log("Test",Log::LOG_DEBUG);

    m_Log.MLog(Log::LOG_DEBUG, "Test Test");

    return true;
}

bool TestUnit::TestMapConfig()
{
    MapActionLoader &mapLoader = MapActionLoader::GetInstance();
    mapLoader.Init("proto/data/dataconfig_map.data");

    MonsterLoader &monsterLoader = MonsterLoader::GetInstance();
    monsterLoader.Init("proto/data/dataconfig_monster.data");

    DropLoader &dropLoader = DropLoader::GetInstance();
    dropLoader.Init("proto/data/dataconfig_drop.data");


    return true;
}

bool TestUnit::TestMacro()
{
    cout << MACRO_2_STRING(D(2)) << endl;

    return true;
}
