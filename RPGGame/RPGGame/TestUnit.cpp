#include "TestUnit.h"

#include <iostream>

using std::cout;
using std::endl;


#include "UIBase.h"

#include "StrUtil.h"
#include "Pointer.h"
#include "App.h"
#include "Frame.h"


TestUnit::TestUnit()
{
}


TestUnit::~TestUnit()
{
}

void TestUnit::Run()
{
    TEST(TestStrUtilSplit);
    TEST(TestPointer);
    TEST(TestFrame);




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
    Frame frame;

    FrameData stFrameData;
    stFrameData.eDirection = data::DIRECTION_HORIZONTAL;
    stFrameData.iHandlerID = 0;
    stFrameData.iID = 0;
    stFrameData.oPosition.iX = 0;
    stFrameData.oPosition.iY = 0;
    stFrameData.oSize.iWidth = 20;
    stFrameData.oSize.iHeigth = 20;
    stFrameData.sDescription = "adsfasfd\nadsfalasdfasdfsadfsasdfsadfsafsafsfsfsafsadfasdfdf\nksdjf";
    Option option;
    option.sDescription = "world";
    stFrameData.vOptions.push_back(option);


    frame.Init(stFrameData);
    frame.Show();
    return true;
}
